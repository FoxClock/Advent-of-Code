import Foundation

func main() ->  Void {
    // Constants
    let testing = true
    let fileName = testing ? "test_input.txt" : "input.txt"
    let fileURL = createURL(fileName: fileName)

    var puzzleInput: String
    
    do {
        puzzleInput = try String(contentsOf: fileURL)
    } catch {
        print("Unable to open file.")
        exit(EXIT_FAILURE)
    }

    let stringThing = puzzleInput.split(separator: "\n")
    var array: [String] = stringThing.map { thing in
        String(thing)
    }

    for line in array.enumerated() {
        for character in line.element.enumerated() {
            checkAdjacent(input: array, xPos: line.offset, yPos: character.offset)
        }
    }
}

/* MARK: Auxilary functions */
func createURL(fileName: String) -> URL {
    let fileManager = FileManager.default
    
    let fileURL = URL(fileURLWithPath: fileManager.currentDirectoryPath).appendingPathComponent(fileName)

    return fileURL
}

func checkAdjacent(input: [String], xPos: Int, yPos: Int) {
    let line = input[xPos]
    let currentCharacter = line[line.index(line.startIndex, offsetBy: yPos)]
    
    var lettersAround : (
        left: Character,
        right: Character,
        top: Character,
        bottom: Character
    )

    switch currentCharacter {
    case "X": 
        
    default:
        
    }

}

/* MARK: Main entrypoint */
main()