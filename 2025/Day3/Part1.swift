// The Swift Programming Language
// https://docs.swift.org/swift-book

import Foundation

@main
struct Day3 {
    static func main() {
        /* Constants */
        // Set debug or run mode
        let mode: Mode = Mode.from(CommandLine.arguments)
        let fileContents: String
        
        // Variables
        var maxValues: [Int] = [Int]()

        // Read file contents as string
        do {
            fileContents = try readFile(mode.filename)
        } catch {
            print("Cannot read: \(mode.filename). Exiting...")
            exit(EXIT_FAILURE)
        }

        // Split inputs by line
        let splitInputs = fileContents.split(separator: "\n")
            .compactMap({String($0)})

        // Convert each line from string to integer
        let IntArrayOfInputs = splitInputs.map({convertLineToInt($0)})

        // Debug print array of numbers
        if mode == .test { print(IntArrayOfInputs) }

        // Compute the permutations
        let joltageCombinations = IntArrayOfInputs.map({joltagePermutations(from: $0, length: 2)})

        // Get max from the combinations
        for (combination) in joltageCombinations {
            if let max = combination.max() {
                maxValues.append(max)
            }
        }
        
        print("Total: \(sumMaxValues(in: maxValues))")
    }
}


enum Mode {
    case test
    case run

    var filename: String {
        switch self {
            case .test: return "test_input.txt"
            case .run: return "input.txt"
        }
    }

    static func from(_ args: [String]) -> Mode {
        if args.contains("debug") || args.contains("--debug") {
            return .test
        } else {
            return .run
        }
    }
}


func readFile(_ input: String) throws -> String {
    let url = URL(fileURLWithPath: input)
    return try String(contentsOf: url, encoding: .utf8)
}

func convertLineToInt(_ input: String) -> [Int] {
    
    let result: [Int]


    result = input.compactMap { value in
        value.wholeNumberValue
    }

    return result

}

func joltagePermutations(from input: [Int], length L: Int) -> [Int] {

    // pre-tests
    guard L > 0 && L <= input.count else { return [] }
    if L == 1 { return input }

    // Variables
    var result: [Int] = [Int]()

    /*
        Subtle Bug:
            Array(input[i + 1]...) is causing a program hang. 
            Compiler interprets this as Array( input[i + 1] ... Int.max)
            or effectivly: Array(8...9_223_372_036_854_775_807)
            hence my problem ....
    */

    // Iterate over input creating permutations   
    for i in 0..<(input.count - L + 1){
        let head: Int = input[i]
        let tail: [Int] = Array(input[(i + 1)...]) 
        let tailCombinations = tail.map({[head, $0]})
        
        for combination in tailCombinations {
            var multiplier = 1
            var resultValue: Int = 0
            
            for item in Array(combination).reversed() {
                resultValue += item * multiplier
                multiplier = multiplier * 10    
            }

            result.append(resultValue)
        }
    }

    return result
}

func sumMaxValues(in input: [Int]) -> Int {
    input.reduce(0, +)
}