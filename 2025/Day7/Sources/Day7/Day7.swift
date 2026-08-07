// The Swift Programming Language
// https://docs.swift.org/swift-book

import Foundation

// =====================
// MARK: Enums
// =====================
enum Mode {

    case test
    case run

    var filename: String {
        switch self {
        case .test: "test_input.txt"
        case .run: "input.txt"
        }
    }

    static func from(_ arguments: [String]) -> Mode {
        if arguments.contains("debug") || arguments.contains("--debug") {
            return .test
        } else {
            return .run
        }
    }
}

@main
struct Day7 {
    static func main() {
        // Setup debug mode
        let mode = Mode.from(CommandLine.arguments)
        let fileContents = openFile(mode.filename)

        if mode == .test {
            let testOutputFile = "test_output.json"
            guard let testStruct: TestStructure = buildTestStates(testOutputFile) else {
                print("Error loading test structure.")
                return
            }
            displayTestIteration(fileContents, iteration: 0, from: testStruct)
        }

        print("\n---------------------")

        var splitArray = fileContents.split(whereSeparator: { $0.isNewline })
        for var line in splitArray {
            var sIndex: String.Index? = nil
            var lineLength = line.count
            if line.contains("S") {
                sIndex = line.firstIndex(of: "S")
                continue
            }

            if let sIndex = sIndex {
                line.replaceSubrange(sIndex...sIndex, with: "|")
            }
            print(line)
        }
    }
}

// =====================
// Auxiliary Functions
// =====================

func openFile(_ filename: String) -> String {

    guard !(filename.isEmpty) else {
        print("File cannot be opened.")
        return ""
    }

    let url = URL(filePath: filename)

    do {
        let fileContents = try String(contentsOf: url, encoding: .utf8)
        return fileContents
    } catch {
        print("File cannot be opened.")
        return ""
    }
}

// =====================
// Testing functions
// =====================
struct TestStructure: Codable {
    var output: [String]
}

enum Colour {
    case red
    case green
    case none

    var colourCode: String {
        switch self {
        case .red: "[31m"
        case .green: "[32m"
        case .none: "[0m"
        }
    }

    func cPrint(_ input: Any) {
        print(
            "\u{001B}\(self.colourCode)", "\(input)", "\u{001B}[0m",
            separator: "",
            terminator: "")
    }
}

func buildTestStates<T: Decodable>(_ filePath: String) -> T? {
    var testStruct: T? = nil

    guard !(filePath.isEmpty) else {
        print("Unable to open test file. File Name is empty.")
        return testStruct
    }

    let decoder = JSONDecoder()
    let url = URL(filePath: filePath)

    do {
        let data = try Data(contentsOf: url)
        testStruct = try decoder.decode(T.self, from: data)
    } catch {
        print("Unable to open test file. Error decoding struct.")
        print("Error: \(error)")
        return testStruct
    }

    return testStruct
}

func displayTestIteration(_ input: String, iteration: Int, from testStruct: TestStructure) {
    let testCount = testStruct.output.count

    guard iteration >= 0, !(input.isEmpty) else {
        print("Iteration must be positive and input must not be empty.")
        return
    }

    var colourCode: Colour
    let currentIteration: String
    if iteration < testCount - 1 {
        currentIteration = testStruct.output[iteration]
        if input == currentIteration {
            colourCode = .none
            colourCode.cPrint(input)
            return
        }
    } else {
        currentIteration = testStruct.output.last!      // Will explode wth empty array
    }
    for characters in zip(input, currentIteration) {
        if characters.0 == characters.1 {
            colourCode = .none
        } else {
            colourCode = .red
        }
        colourCode.cPrint(characters.0)
    }
}
