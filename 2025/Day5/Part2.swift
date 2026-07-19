// The Swift Programming Language
// https://docs.swift.org/swift-book

/*
* Author:       Hayden Foxwell
* Date:           18/07/26
* Purpose:
*       To solve a challenge in the Advent of code where a file is presented with
*       a list of ranges. These ranges represent the 'Fresh' items which are in the
*       storage. The second list is available items. Any items which do not fall in the
*       provided ranges are considered to have "gone off".
*/

import Foundation

// ========================
// Enums
// ========================
enum Mode {
    case test
    case run

    var filename: String {
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

@main
struct Day5 {
    static func main() {
        let mode: Mode = Mode.from(CommandLine.arguments)
        let fileContents = openFile(from: mode.filename)
        let (ranges, _) = splitFile(fileContents)
        let closedRanges = convertRanges(ranges)

        // Sort ranges in ascending order
        let sortedRanges = closedRanges.sorted(by: { $0.lowerBound < $1.lowerBound })

        let coalecedRanges = coaleseRanges(ranges: sortedRanges)

        if mode == .test {
            let testOutputRanges = convertRanges(["3-5", "10-20"])
            debugOutput(ranges: coalecedRanges, outputRanges: testOutputRanges)
        }

        var total = 0
        for range in coalecedRanges {
            total += range.count
        }
        
        print("Total Fresh: \(total)")
    }
}

// ========================
// MARK: Auxilary Functions
// ========================
func openFile(from input: String) -> String {
    let url: URL = URL(filePath: input)

    do {
        let fileContents = try String(contentsOf: url, encoding: .utf8)
        return fileContents
    } catch {
        print("Unable to open file.")
        return ""
    }
}

func splitFile(_ input: String) -> (ranges: [String], values: [String]) {
    var ranges: [String] = []
    var values: [String] = []

    let splitInput: [String.SubSequence] = input.split(
        separator: "\n", omittingEmptySubsequences: false)
    let splitIndex = splitInput.firstIndex(of: "")

    guard let splitIndex else {
        print("Could not split file.")
        return ([], [])
    }

    // Get the range of values for both the valid ranges and associated values
    // Cast these to string, discarding nulls
    ranges = splitInput[0..<splitIndex].compactMap({ String($0) })
    values = splitInput[(splitIndex + 1)...].compactMap({ String($0) })

    return (ranges, values)
}

func convertRanges(_ inputRanges: [String]) -> [ClosedRange<Int>] {
    var ranges: [ClosedRange<Int>] = []

    for range in inputRanges {
        let split = range.split(separator: "-")
        let values = split.compactMap({ Int($0) })

        if values.isEmpty || values.count < 2 {
            continue
        } else {
            ranges.append(values[0]...values[1])
        }
    }

    return ranges
}

func checkItemIsFresh(item: Int, in ranges: [ClosedRange<Int>]) -> Int? {
    for range in ranges {
        if range.contains(item) {
            return item
        }
    }

    return nil
}

func coaleseRanges(ranges: [ClosedRange<Int>]) -> [ClosedRange<Int>] {
    var tempRanges = ranges

    var currentIndex = 1
    while currentIndex < tempRanges.count {
        let prevRange = tempRanges[currentIndex - 1]
        let currentRange = tempRanges[currentIndex]

        if prevRange.contains(currentRange) {
            tempRanges.remove(at: currentIndex)
            continue
        }

        if prevRange.contains(currentRange.lowerBound) {
            tempRanges[currentIndex] = prevRange.lowerBound...max(prevRange.upperBound, currentRange.upperBound)
            tempRanges.remove(at: currentIndex - 1)
        } else {
            currentIndex += 1
        }
    }

    return tempRanges
}

// ========================
// MARK: Test Harness
// ========================

func debugOutput(ranges: [ClosedRange<Int>], outputRanges: [ClosedRange<Int>]) {
    print("Ranges:")
    for range in zip(ranges, outputRanges) {
       if range.0 != range.1 {
        print("\t\u{001B}[31m\(range.0)\u{001B}[0m")
       } else {
        print("\t \(range.0)")
       }
    }
}
