import Foundation

func  main() -> Void {
    let testing = true
    let fileName = testing ? "test_input.txt" : "input.txt"
    let fileURL = createURL(from: fileName)

    // variables
    var stringContents: String
    var rulesDict: [Int : Int] = [:]

    // Extract contents from string
    do {
        stringContents = try String(contentsOf: fileURL, encoding: .utf8)
    } catch let err {
        print("Could not parse string data: \(err)")
        exit(EXIT_FAILURE)
    }

    // Create Rules 
    let splitString = stringContents.split(separator: "\n")
    let rulesSubstring = splitString.filter { Substring in
        Substring.contains("|")
    }
    .reduce("") { inital, SubString in
        inital + SubString + "\n"
    }

    // Create Reports
    let reports = splitString.filter { Substring in
        !Substring.contains("|")
    }
    .map { Substring in
        Substring.split(separator: ",")
        .compactMap { Substring in
            Int(Substring)
        }
    }

    // Extract rules
    rulesDict = initaliseRules(from: rulesSubstring)

    // Print
    print("Rules:\n \(rulesDict)")
    print("Reports:\n \(reports)")
}

// MARK: Auxilary Functions
func createURL(from inputFile: String) -> URL {
    let currentDirectory = FileManager.default.currentDirectoryPath
    return URL(filePath: currentDirectory).appending(component: inputFile)
}

func parseRule(_ line: String) -> (Int, Int)? {
    // Constants
    let separator = "|"
    
    // Variables 
    var splitString: [String.SubSequence] = []
    var firstValue: Int?
    var secondValue: Int?

    // Parse data from string //
    // Split string by pipe symbol
    splitString = line.split(separator: separator)

    // parse values from string
    firstValue = Int(splitString[0])
    secondValue = Int(splitString[1])

    // Coalese the values into ints or return nil as failure
    if let firstValue = firstValue, let secondValue = secondValue {
        return (firstValue, secondValue)
    } else {
        return nil
    }
}

func initaliseRules(from inputString: String) -> [Int : Int] {
    // Constants
    let sep = "\n"

    // Variables
    var lines: [String]
    var extractedRules: [(Int, Int)] = []
    var rulesDict: [Int : Int] = [:]

    // Separate input into separate lines
    // Cast each line to string
    lines = inputString.split(separator: sep).map{ line in 
        String(line)
    }

    // Extract rule from each line
    extractedRules = lines.compactMap { line in 
        parseRule(line)
    }

    // Convert to rules dictionary
    for rule in extractedRules {
        rulesDict[rule.0] = rule.1
    }


    return rulesDict
}

main()