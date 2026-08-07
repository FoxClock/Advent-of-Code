// The Swift Programming Language
// https://docs.swift.org/swift-book

import Foundation

// =====================
// Enums
// =====================
enum Mode {
    case test
    case run

    var fileName: String {
        switch self {
        case .run: "input.txt"
        case .test: "test_input.txt"
        }
    }

    static func from(_ input: [String]) -> Mode {
        if input.contains("debug") || input.contains("--debug") {
            return .test
        } else {
            return .run
        }
    }
}

enum Operator {
    case multiply
    case add

    var arithOperator: (_ x: [Int]) -> Int {
        switch self {
        case .add:
            { $0.reduce(0, +) }
        case .multiply:
            { $0.reduce(1, *) }
        }
    }

    static func from(strArithmeticSymbol: String) -> Operator {
        switch strArithmeticSymbol {
        case "+": return .add
        case "*": return .multiply
        default:
            print("Unable to determine operator.")
            exit(EXIT_FAILURE)
        }
    }
}

// =====================
// MARK: Main Function
// =====================
@main
struct Day6 {
    static func main() {
        let mode: Mode = Mode.from(CommandLine.arguments)
        let fileContents = openFile(mode.fileName)

        // Split up the contents and split off the arithmetic symbols
        var stringArray: [[String]] = splitString(fileContents)


        guard !(stringArray.isEmpty) else {
            print("Empty file, cannot extract arithmetic symbols.")
            return
        }

        let symbols: [String] = stringArray.removeLast()

        // reshape the arrays so that they are lined up ready for
        // processing with their associated symbol
        let reshapedArrays = reshapeArray(stringArray)

        if mode == .test {
            testPrint(fileContents, stringArray)
            print("--------------------------")
            print(reshapedArrays)
        }

        // convert array back into 2d array
        for array in reshapedArrays {
            let individualNumbersArray = splitArrayToDigits(array)
            print(individualNumbersArray)
        }

        // Convert the reshaped arrays to integers
        let convertedArrays = reshapedArrays.map({
            $0.compactMap({ Int($0) })
        })

        var total = 0
        for (array, arithOperator) in zip(convertedArrays, symbols) {
            let op = Operator.from(strArithmeticSymbol: arithOperator)
            let result = op.arithOperator(array)
            total += result
        }

        print("Sum Total: \(total)")
    }
}

// =====================
// MARK: Auxiliary  Functions
// =====================
func openFile(_ fileName: String) -> String {

    if fileName.isEmpty {
        print("Unable to open file.")
        return ""
    }

    let url: URL = URL(fileURLWithPath: fileName)

    do {
        let contents = try String(contentsOf: url, encoding: .utf8)
        return contents
    } catch {
        print("Unable to open file.")
        return ""
    }
}

func splitString(_ input: String) -> [[String]] {
    let initialSplit = input.split(whereSeparator: { $0.isNewline })
    let secondSplit = initialSplit.map(
        { $0.split(separator: " ") }
    )
    let finalArray = secondSplit.map(
        {
            $0.compactMap(
                { String($0) }
            )
        }
    )

    return finalArray
}

func reshapeArray(_ stringArrays: [[String]]) -> [[String]] {
    var outputArrays: [[String]] = []

    let yShape = stringArrays.count
    guard let xShape = stringArrays.first?.count else {
        print("The first array has no elements. Check inputs.")
        return outputArrays
    }

    for x in 0..<xShape {
        var outputArray: [String] = []
        for y in 0..<yShape {
            let value = stringArrays[y][x]
            outputArray.append(value)
        }
        outputArrays.append(outputArray)
    }

    return outputArrays
}

func splitArrayToDigits(_ inputArray: [String]) -> [[String]] {
    /* split each inputted string into individual digits. All arrays 
    are of equal length, with blank spaces replaced with ""
    */
    var outputArray: [[String]] = []
    guard let longestNumber = inputArray.map({$0.count}).max() else {
        print("Array has not elements")
        return outputArray
    }

    for number in inputArray {
        var digitArray = [String](repeating: "", count: longestNumber)
        for (index, character) in number.enumerated() {
            digitArray[index] = String(character)
        }
        outputArray.append(digitArray)
    }

    return outputArray
}

// =====================
// MARK: Test Input
// =====================
func testPrint(_ fileInput: String, _ StringArray: [[String]]) {
    print("Test File input: \n--------------------------------------")
    print(fileInput)
    print("\nString Array:\n---------------------------------------")
    for item in StringArray {
        print("Item: \(item) - \(type(of: item))")
    }
}
