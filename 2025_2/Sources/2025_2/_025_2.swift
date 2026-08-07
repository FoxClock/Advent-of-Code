// The Swift Programming Language
// https://docs.swift.org/swift-book

import Foundation

// =====================
// Enum
// =====================

enum PuzzleConfiguration {
    case test(_ day: String)
    case run(_ day: String)

    var day: String {
        switch self {
        case .run(let day), .test(let day):
            return day
        }
    }

    var fileName: String {
        guard !(self.day.isEmpty) else {
            return ""
        }

        switch self {
        case .run: return "\(self.day)_input"
        case .test: return "\(self.day)_test_input"
        }
    }

    static func from(_ arguments: [String]) -> PuzzleConfiguration? {
        let debugArguments = [
            "-d",
            "--debug",
            "debug",
        ]

        let userArguments = arguments.dropFirst()
        guard !(userArguments.isEmpty) else {
            print("No arguments provided")
            return nil
        }

        guard let day = userArguments.first else {
            print("Unable to determine day. Not enough arguments provided")
            return nil
        }

        if debugArguments.contains(where: { debug in userArguments.contains(debug)}) {
            return .test(day)
        }

        return .run(day)
    }
}

// =====================
// Day protocol
// =====================

protocol PuzzleDay {
    init(rawInput: String)
    func partOne() -> String
    func partTwo() -> String
}

// =====================
// MARK: main function
// =====================

@main
struct _025_2 {
    static func main() {
        let arguments = CommandLine.arguments
        let days: [String: PuzzleDay.Type] = [
            "1": DayOne.self,
            "2": DayOne.self,
        ]

        guard arguments.count >= 2, !(arguments.isEmpty) else {
            print("Incorrect arguments for running file.")
            print("usage: \n\tDay to run: <Integer> \n\tDebug Mode (optional): --debug | -d")
            return
        }

        guard let puzzleConfig = PuzzleConfiguration.from(arguments) else {
            print("Unable to configure program correctly. Exiting...")
            return
        }

        guard let pdType = days[puzzleConfig.day] else {
            print("Can't find day: \(puzzleConfig.day)")
            return
        }
        let puzzle: PuzzleDay = pdType.init(rawInput: openFile(puzzleConfig.fileName))

        let result1 = puzzle.partOne()
        let result2 = puzzle.partTwo()

        print("Mode: \(puzzleConfig) \nPart 1: \(result1) \nPart 2: \(result2)")
    }
}
