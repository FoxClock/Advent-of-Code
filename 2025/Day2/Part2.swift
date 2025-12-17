/*
* Author:     Hayden Foxwell
* Date:       17/12/2025
*/

import Foundation

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

func main() {
    let fileContents: String
    let mode = Mode.from(CommandLine.arguments)
    let filename = mode.fileName

    do {
        fileContents = try readFile(from: filename)
    } catch {
        print("Cannot read file: \(filename)")
        exit(EXIT_FAILURE)
    }

    // Split file contents into separate items
    let splitCollection = fileContents.split(separator: ",")
            .map({String($0)})

    let ranges = splitCollection.compactMap( {rangeConvert(from: $0)} )

    let pallendromeNumberCount = ranges.reduce(0, { partialResult, range in partialResult + findRepeaterNumbers(in: range) })
    print(pallendromeNumberCount)
}

func readFile(from filePath: String) throws -> String {
    let url = URL(fileURLWithPath: filePath)
    return try String(contentsOf: url, encoding: .utf8).trimmingCharacters(in: .whitespacesAndNewlines)
}

// function which converts each id pair into swift ranges
func rangeConvert(from input: String) -> Range<Int> {
    let low: Int
    let high: Int
    
    let splitCharacter = "-"

    let values = input.split(separator: splitCharacter)

    let convertedValues = values.compactMap({Int($0)})

    low = convertedValues.first ?? 0
    high = convertedValues.last ?? 0

    return Range<Int>(low...high)
}


// This function finds pallendrome numbers
// however, this is not what is needed for the 
// challenge.
func findPallendrome(in input: Range<Int>) -> Int {

    var total = 0

    for value in input {
        var reverse = 0
        var temp = abs(value)
        while temp != 0 {
            reverse = (reverse * 10) + (temp % 10)
            temp = temp / 10
        }

        if reverse == abs(value) {
           total += reverse 
        }
    }

    return total 
}


func findRepeaterNumbers(in input: Range<Int>) -> Int {

    var total = 0

    for value in input {
        let strRepr = String(value) 
        
        if !passRules(strRepr) {
            continue
        }

        let strHalfPos = strRepr.count / 2
        let strFirstIndex = strRepr.startIndex
        let midIndex = strRepr.index(strFirstIndex, offsetBy: strHalfPos)
        let endIndex = strRepr.endIndex

        let firstHalf = String(strRepr[strFirstIndex..<midIndex])
        let secondHalf = String(strRepr[midIndex..<endIndex])

        if firstHalf == secondHalf {
            total += value
        }
    }

    return total
}

func passRules(_ input: String) -> Bool {
    
    if String(input.first!) == "0" {
        return false
    }

    return true
}

func splitString(_ input: String) -> Bool {
    
    if input.count <= 1 {
        return true
    }

    let strStartIndex = input.startIndex
    let strMidIndex = input.index(strStartIndex, offsetBy: input.count / 2)
    
    let leftString = String(input[strStartIndex..<strMidIndex])
    let rightString = String(input[strMidIndex..<input.endIndex])

    if leftString == rightString {
        return true
    } else {
        return (splitString(leftString) || splitString(rightString))
    }
}


main()
