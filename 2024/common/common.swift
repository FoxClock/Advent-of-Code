/// Author:     Hayden Foxwell
/// Date:        20/11/25
/// Common file which provides common functionality for AOC 2024

/* Imports */
import Foundation

/// Sets the debug status by examining the arguments passed
/// to the file when run
/// - Parameter arguments: Array of argument strings
/// - Returns: Bool - whether debug is set
public func setDebug(arguments: Array<String>.SubSequence) -> Bool {
    // Test each item in the arguments array against debug
    let value = arguments.map {$0.contains("debug")}
    // Sum all true integers (True = 1 : False = 0)
    let sum = value.reduce(0) {(result, next) in 
        return result + (next ? 1 : 0)
    }
    // If debug is in the array, sum will be positive 
    return sum > 0 ? true : false
}

/// Creates a URL from the input file (string) which is provided
/// - Parameter inputFile: String, representing file name
/// - Returns: URL to the file
func createURL(from inputFile: String) -> URL {
    let currentDirectory = FileManager.default.currentDirectoryPath
    return URL(filePath: currentDirectory).appending(component: inputFile)
}