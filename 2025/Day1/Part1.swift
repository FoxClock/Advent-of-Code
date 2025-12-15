// The Swift Programming Language
// https://docs.swift.org/swift-book

import Foundation
@main
struct Day1 {
    static func main() {

        // Constants
        let mode: Mode
        let input: String
        let DialPostion: Int = 50

        // Set debug or run mode
        mode = Mode.from(CommandLine.arguments)

        // read file contents
        do { 
            input = try readFile(mode.fileName)
        } catch {
            print("Cannot read file contents: \(error)")
            exit(EXIT_FAILURE)
        }

        // Divide string into individual lines, convert to string not subsequence
        let splitInput = input.split(separator: "\n")
            .map({String($0)})

        // Make values positive or negative
        let alignedValues = scaleValues(splitInput)

        if mode == .test {
            print("Alignted Values: \(alignedValues)")
        }

        // get all rotations
        let rotationPositions = applyRotations(start: DialPostion, rotations: alignedValues)

        let zeroCount = rotationPositions.count(where: {$0 == 0})

        print(rotationPositions)
        print("Final result: \(zeroCount)")

   }
}

enum Mode {
    case test
    case run

    var fileName: String {
        switch self {
            case .test: return "test_input.txt"
            case .run: return "input.txt"
        }
    }

    static func from(_ args: [String]) -> Mode {
        if args.contains("debug") {
            return .test
        } else {
            return .run
        }
    }
}

func readFile(_ inputFile: String) throws -> String {
    let url = URL(fileURLWithPath: inputFile)
    return try String(contentsOf: url, encoding: .utf8)
}


func scaleValues(_ input: [String]) -> [Int] {
    let output: [Int]

    output = input.compactMap { inputValue in
        if inputValue.contains("R") {
            let newVal = inputValue.dropFirst()
            return Int(newVal)
        } else {
            let newVal = inputValue.dropFirst()
            return (-1 * (Int(newVal) ?? 0))
        }
    }

    return output
}

func rotateDial(currentValue: Int, rotation: Int, dialSize: Int = 99) -> Int {
    let newRotation = currentValue + (rotation)
    
    if newRotation > dialSize {
        return (newRotation - dialSize) - 1
    }

    if newRotation < 0 {
        return (newRotation + dialSize) + 1
    }

    return newRotation
}

func applyRotations(start: Int, rotations: [Int]) -> [Int] {

    // Reduce the outline 
    rotations.reduce(into: [start]) {acc, rotation in
        print("Acc: \(acc)")
        print("Rot: \(rotation)")
        let next = rotateDial(currentValue: acc.last ?? 0, rotation: rotation)
        acc.append(next)
    }
}// The Swift Programming Language
// https://docs.swift.org/swift-book

import Foundation
@main
struct Day1 {
    static func main() {

        // Constants
        let mode: Mode
        let input: String
        let DialPostion: Int = 50

        // Set debug or run mode
        mode = Mode.from(CommandLine.arguments)

        // read file contents
        do { 
            input = try readFile(mode.fileName)
        } catch {
            print("Cannot read file contents: \(error)")
            exit(EXIT_FAILURE)
        }

        // Divide string into individual lines, convert to string not subsequence
        let splitInput = input.split(separator: "\n")
            .map({String($0)})

        // Make values positive or negative
        let alignedValues = scaleValues(splitInput)

        if mode == .test {
            print("Alignted Values: \(alignedValues)")
        }

        // get all rotations
        let rotationPositions = applyRotations(start: DialPostion, rotations: alignedValues)

        if mode == .test {print("Rots: \(rotationPositions)")}

        let zeroCount = rotationPositions.count(where: {$0 == 0})

        //print(rotationPositions)
        print("Final result: \(zeroCount)")

   }
}

enum Mode {
    case test
    case run

    var fileName: String {
        switch self {
            case .test: return "test_input.txt"
            case .run: return "input.txt"
        }
    }

    static func from(_ args: [String]) -> Mode {
        if args.contains("debug") {
            return .test
        } else {
            return .run
        }
    }
}

func readFile(_ inputFile: String) throws -> String {
    let url = URL(fileURLWithPath: inputFile)
    return try String(contentsOf: url, encoding: .utf8)
}


func scaleValues(_ input: [String]) -> [Int] {
    let output: [Int]

    output = input.compactMap { inputValue in
        if inputValue.contains("R") {
            let newVal = inputValue.dropFirst()
            return Int(newVal)
        } else {
            let newVal = inputValue.dropFirst()
            return (-1 * (Int(newVal) ?? 0))
        }
    }

    return output
}

func rotateDial(currentValue: Int, rotation: Int, dialSize: Int = 99) -> Int {
    let totalDialPositions = dialSize + 1

    return (currentValue + (rotation) % totalDialPositions + totalDialPositions) % totalDialPositions
}

func applyRotations(start: Int, rotations: [Int]) -> [Int] {

    // Reduce the outline 
    rotations.reduce(into: [start]) {acc, rotation in
        let next = rotateDial(currentValue: acc.last ?? 0, rotation: rotation)
        acc.append(next)
    }
}