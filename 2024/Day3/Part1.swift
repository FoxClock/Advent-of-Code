/* MARK: Imports */
import Foundation

/* MARK: Main Function */
func main() {
    // Constants
    let test: Bool = true
    let input_file: String = test ? "test_input.txt" : "input.txt"
    let fileURL = createURL(input_file)

    // Variables
    var input: String

    // create string
    do {
        input = try String(contentsOf: fileURL, encoding: .utf8)
    } catch let err {
        print("Failed to read file: \(err)")
        exit(EXIT_FAILURE)
    }

    let mul_filter = input.    
}

/* MARK: Auxiliary Functions */
func createURL(_ file_to_open: String) -> URL {
    // Constants
    let currentDirectoryPath = FileManager.default.currentDirectoryPath

    // Create file URL from CWD and file name
    var fileURL = URL(filePath: currentDirectoryPath)
    fileURL = fileURL.appending(path: file_to_open)

    return fileURL
}

func findOccurances(_ input: String) -> [(index: Int, firstArgument: Int, secondArgument: Int)] {
    // Constants
    let regexPattern = #"mul\((-?\d+),\s*(-?\d+)\)"#        // Regular expression pattern
    let regex: Regex<AnyRegexOutput>                                // Placeholder for regex object
    
    // Attempt to create a regular expression
    do {
        regex = try Regex(regexPattern)
    } catch let err {
        print("Could not create regex expression: \(err)")
    }

    // Find all matches in the string
    regex.enumerateMatches
}

/* MARK: Main entrypoint */
main()