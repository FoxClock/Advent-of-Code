/*
* Author:       Hayden Foxwell
* Date:         26/07/2026
* Purpose:
*       Provide common functions used for the advent of code.
*/

// Imports
import Foundation

// =====================
// MARK: Enums
// =====================
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

/* Open file
* Opens a file in the bundle, then returns the contents of the file in
* string format.
* If unable to open the file, or a reading error occurs, an empty string will be returned
* along with a
*/
public func openFile(_ fileName: String) -> String {
    var fileContents: String = ""

    guard let url: URL = Bundle.module.url(forResource: fileName, withExtension: ".txt"),
        !(fileName.isEmpty)
    else {
        print("Unable to open file. Invalid file name.")
        return fileContents
    }

    do {
        fileContents = try String(contentsOf: url, encoding: .utf8)
        return fileContents
    } catch {
        print("Unable to decode file: \(error)")
        return fileContents
    }
}

/* Split input string by. newline
* Takes a string and returns an array of strings. Each index in the array
* is a 'line' in the file.
* This functions preserves empty lines and will return them as an empty array.
*/
public func splitInput(_ input: String, delimiter: String = "\n") -> [String.SubSequence] {
    input.split(separator: delimiter, omittingEmptySubsequences: false)
}
