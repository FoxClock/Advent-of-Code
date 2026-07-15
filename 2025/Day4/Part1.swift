// The Swift Programming Language
// https://docs.swift.org/swift-book

/* RULES:
    An @ symbol can only be accessed if:
        - if there are fewer than 4 '@' symbols in adjacent cells

    If an @ symbol is accessable, then replace it with "x"

    Count the number of accessable rolls.
*/
import Foundation
// ==============================
// MARK: Enums
// ==============================
// File Operation enum
// ==============================
enum Mode {
    case test
    case run

    var filename: String {
        switch self {
        case .test: return "test_input.txt"
        case .run: return "input.txt"
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

// ==============================
// Cardinal Directions enum
// ==============================
enum Direction: CaseIterable {
    case north
    case northEast
    case east
    case southEast
    case south
    case southWest
    case west
    case northWest

    var offsets: (x: Int, y: Int) {
        switch self {
        case .north: (x: 0, y: -1)
        case .northEast: (x: 1, y: -1)
        case .east: (x: 1, y: 0)
        case .southEast: (x: 1, y: 1)
        case .south: (x: 0, y: 1)
        case .southWest: (x: -1, y: 1)
        case .west: (x: -1, y: 0)
        case .northWest: (x: -1, y: -1)
        }
    }
}

// =====================
// MARK: Main
// =====================
@main
struct Day4 {
    struct Config {
            let paper: Character
            let acessable: Character
            let blank: Character
            let requiredSpaces: Int
        }
    

    static func main() {
        let testFileContents = openFile("test_output.txt")
        let testFileArray = processArray(from: testFileContents)

        let mode = Mode.from(CommandLine.arguments)
        let currentConfig = Config(
                paper: "@",
                acessable: "x", 
                blank: ".", 
                requiredSpaces: 4
            )
        let fileContents = openFile(mode.filename)

        let (width, lines) = getDataShape(from: fileContents)

        var characterArray = processArray(from: fileContents)
        

        characterArray = findFreeSpaces(width: width, lines: lines,  array: characterArray, config: currentConfig)

        // Print out data shape
        if mode == .test {
            print("Width: \(width), Height: \(lines)")

            for y in 0..<lines {
                for x in 0..<width {
                    let index = arrayIndex(x, y, width: width)
                    if testFileArray[index] == characterArray[index] {
                        print(characterArray[index], terminator: "")
                    } else {
                        print("\u{001B}[31m\(characterArray[index])\u{001B}[0m", terminator: "")
                    }
                }
                print()
            }
            
            if testFileArray.elementsEqual(characterArray) {
                print("Test Passed")
            } else {
                print("\u{001B}[31mTest Failed\u{001B}[0m")
            }
        }

        let freeSpacesCount = characterArray.count(where: {$0 == currentConfig.acessable})
        print("Free Spaces: \(freeSpacesCount)")


    }
}

// ==============================
// MARK: Auxilary functions
// ==============================
func openFile(_ fileName: String) -> String {
    var output = ""

    guard !(fileName.isEmpty) else {
        print("Filename Empty. No file to read.")
        return output
    }

    let stringUrl = URL(filePath: fileName)

    do {
        output = try String(contentsOf: stringUrl, encoding: .utf8)
    } catch let error {
        print("Error processing string")
        print("Error: \(error.localizedDescription)")
    }

    return output
}

func getDataShape(from fileContents: String) -> (width: Int, height: Int) {
    var width = 0
    var height = 0

    for (counter, character) in fileContents.enumerated() {
        if character.isNewline {
            width = counter
            break
        }
    }

    height = fileContents.count / width

    return (width: width, height: height)
}

func processArray(from fileContents: String) -> [Character] {
    var outputArray: [Character] = []

    for character in fileContents {
        if !(character.isNewline) {
            outputArray.append(character)
        }
    }

    return outputArray
}

func arrayIndex(_ x: Int, _ y: Int, width: Int) -> Int {
    return (x + (y * width))
}

func findFreeSpaces(width: Int, lines: Int, array: [Character], config: Day4.Config) -> [Character] {
    var outputArray: [Character] = array

    // find free items and replace with 'x'
    let lineRange = 0..<lines
    let widthRange = 0..<width
    for y in lineRange {
        for x in widthRange {
            let index = arrayIndex(x, y, width: width)
            var freeDirections: Set<Direction> = Set<Direction>()

            if array[index] == config.blank {
                continue
            }

            for direction in Direction.allCases {
                let xOffset = x + direction.offsets.x
                let yOffset = y + direction.offsets.y
                let offsetIndex = arrayIndex(x + direction.offsets.x, y + direction.offsets.y, width: width)

                guard widthRange.contains(xOffset) else {
                    freeDirections.insert(direction)
                    continue
                }

                guard lineRange.contains(yOffset) else {
                    freeDirections.insert(direction)
                    continue
                }       
                
                if array[offsetIndex] == config.blank {
                    freeDirections.insert(direction)
                }
                
            }

            if freeDirections.count > config.requiredSpaces {
                outputArray[index] = config.acessable
            }

        }
    }
    
    return outputArray
}
