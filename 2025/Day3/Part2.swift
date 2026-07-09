// The Swift Programming Language
// https://docs.swift.org/swift-book


/*
Attempt 1:
    I tried to extend on the permutations idea. However, as is so frequent in mathematics 
    I came up agains the rules of the universe. Permutations of 12 values are so computationally
    large that I was unable to make it past the test input. Upon reviewing the rules of the challenge
    and doing some research of the problem. I found that the 'Joltage' batteries are preserving order.
    This lead me to my second attempt. Which is to take a list and remove 3 values from the list, making
    it 12 long and checking it for size. If the value is larger than the prev, keep, else discard.

    Eventually some research on the nature of the problem lead to a better understanding of how to solve 
    this. A greedy algorithm was used, called a leftmost greedy window search algorith, or to that effect. 
    This algorithm uses a window of values which is searched within for a maximal value. 

*/

import Foundation

@main
struct Day3 {
    static func main() async {
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
        for input in IntArrayOfInputs {
            let joltage = joltageCalculate(from: input, length: 12)
            maxValues.append(convertArrayToInt(joltage))
        }

        print("Total: \(sumValues(in: maxValues))")
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

func isSame(_ window: ArraySlice<Int>) -> Bool {
    let first = window.first!

    for x in window {
        if x != first {
            return false
        }
    }

    return true
}

func findHighest(_ window: ArraySlice<Int>) -> Int {
    var highestIndex = 0
    var current = window.first!

    for (index, value) in window.enumerated() {
        if value > current {
            current = value
            highestIndex = index
        }
    }

    let ret_index = highestIndex + window.startIndex
    return ret_index
}

func joltageCalculate(from input: [Int], length L: Int) -> [Int] {

    // pre-tests
    guard L > 0 && L <= input.count else { return [] }

    // Variables 
    let input_length = input.count
    
    var start = 0
    var output_array: [Int] = []

    for x in 0..<L {
        let end = input_length - (L - x)
        var index = 0

        let window = input[start...end]

        if !(isSame(window)) {
            index = findHighest(window)
        } else {
            index = window.startIndex
        }

        output_array.append(window[index])

        start = index + 1
    }

    return output_array
}

func convertArrayToInt(_ input: [Int]) -> Int {
    // pre-test
    guard !input.isEmpty else { return 0 }

    // Constants
    let base = 10

    // Variables
    var multiplier = 1
    var value = 0

    for int in input.reversed() {
        value += int * multiplier
        multiplier = multiplier * base
    }

    return value
}

func sumValues(in input: [Int]) -> Int {
    input.reduce(0, +)
}