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

        var freeSpacesCount = 0
        var countedAccessableRolls = 0

        repeat {
            characterArray = findFreeSpaces(
                width: width, lines: lines, array: characterArray, config: currentConfig)
            
            countedAccessableRolls = characterArray.count(where: {$0 == currentConfig.acessable})

            // Update freespace count 
            freeSpacesCount += countedAccessableRolls

            // Remove free items
            characterArray.replace("x", with: ".")

        } while countedAccessableRolls > 0


        // Print out data shape
        if mode == .test {
            printDiagnostics(width, lines, characterArray)
        }

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

func findFreeSpaces(width: Int, lines: Int, array: [Character], config: Day4.Config) -> [Character]
{
    var outputArray: [Character] = array

    let lineRange = 0..<lines  // Range from 0 to the length of the line
    let widthRange = 0..<width  // Range from 0 to the width of the grid

    // find free items and replace with 'x'
    for y in lineRange {
        for x in widthRange {
            // Compute the current index
            let index = arrayIndex(x, y, width: width)
            var freeDirections: Set<Direction> = Set<Direction>()

            if array[index] == config.blank {
                continue
            }

            // Check each direction (n,ne,e,se,s,sw,w,nw) and assertain if it
            // falls within the grid or contains a free space
            for direction in Direction.allCases {
                let xDelta = x + direction.offsets.x  // x delta from current index
                let yDelta = y + direction.offsets.y  // y delta from current index

                // if the x delta from the current index falls outside
                // the array, it is considered free
                guard widthRange.contains(xDelta) else {
                    freeDirections.insert(direction)
                    continue
                }

                // if the y delta from the current index falls outside
                // the array, it is considered free
                guard lineRange.contains(yDelta) else {
                    freeDirections.insert(direction)
                    continue
                }

                // Compute offset index for the item surrounding the 'paper roll'
                // Check if the direction is free
                let offsetIndex = arrayIndex(xDelta, yDelta, width: width)
                if array[offsetIndex] == config.blank {
                    freeDirections.insert(direction)
                }

            }

            // If the freeDirections set contains enough free spaces
            // replace current target character, with an accessable symbol
            if freeDirections.count > config.requiredSpaces {
                outputArray[index] = config.acessable
            }

        }
    }

    return outputArray
}
// =====================
// Testing output
// =====================
func printDiagnostics(_ width: Int, _ lines: Int, _ characterArray: [Character]) {
    let testFileContents = openFile("test_output2.txt")
    let testFileArray = processArray(from: testFileContents)
    
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