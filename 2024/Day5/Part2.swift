import Foundation

func main() {
    // Constants
    let debug: Bool = setDebug(arguments: CommandLine.arguments.dropFirst())
    let fileName = debug ? "test_input.txt" : "input.txt"
    let fileURL = createURL(from: fileName)

    // variables
    var stringContents: String
    var rules: [Int: [Int]]

    // Extract contents from string
    do {
        stringContents = try String(contentsOf: fileURL, encoding: .utf8)
    } catch let err {
        print("Could not parse string data: \(err)")
        exit(EXIT_FAILURE)
    }

    // Split string by newlines
    let split_input = stringContents.split(separator: "\n")

    // Create Rules
    let ruleString = createRules(from: split_input)

    // Extract rules
    rules = initialiseRules(from: ruleString)

    // Create Reports
    let reports = createReports(from: split_input)

    // Iterate over updates (reports) return valid reports
    let valid_reports = reports.compactMap { report in
        validate_report(report, using: rules)
    }

    // Sum the middle values together
    let sumOfMiddleValues = valid_reports.map(
        { report in report[report.endIndex / 2] })
        .reduce(0, +)

    // Print
    print("Rules:\n \(rules)")
    print("Reports:\n \(reports)")
    print("Valid Reports:\n \(valid_reports)")
    print("Sum of middle values: \(sumOfMiddleValues)")
}

/* ========================== */
// MARK: Auxiliary Functions
/* ========================== */
func setDebug(arguments: Array<String>.SubSequence) -> Bool {
    let value = arguments.map { $0.contains("debug") }
    let sum = value.reduce(0) { (result, next) in
        return result + (next ? 1 : 0)
    }

    return sum > 0 ? true : false
}

// Create the url for the file
func createURL(from inputFile: String) -> URL {
    let currentDirectory = FileManager.default.currentDirectoryPath
    return URL(filePath: currentDirectory).appending(component: inputFile)
}

// Creates rules string
func createRules(from inputString: [String.SubSequence]) -> String {
    inputString.filter { Substring in
        Substring.contains("|")
    }
    .reduce("") { initial, SubString in
        initial + SubString + "\n"
    }
}

func createReports(from inputString: [String.SubSequence]) -> [[Int]] {
    inputString.filter { Substring in
        !Substring.contains("|")
    }
    .map { Substring in
        Substring.split(separator: ",")
            .compactMap { Substring in
                Int(Substring)
            }
    }
}

func parseRule(_ line: String) -> (Int, Int)? {
    // Constants
    let separator = "|"

    // Variables
    var splitString: [String.SubSequence] = []

    // Parse data from string //
    // Split string by pipe symbol
    splitString = line.split(separator: separator)

    // parse values from string
    guard let firstValue = Int(splitString.removeFirst()),
        let secondValue = Int(splitString.removeFirst())
    else { return nil }

    return (firstValue, secondValue)
}

func initialiseRules(from inputString: String) -> [Int: [Int]] {
    // Constants
    let sep = "\n"
    let lines: [String]
    let extractedRules: [(Int, Int)]

    // Variables
    var rulesDict: [Int: [Int]] = [:]

    // Separate input into separate lines
    // Cast each line to string
    lines = inputString.split(separator: sep).map { line in
        String(line)
    }

    // Extract rule from each line
    extractedRules = lines.compactMap { line in
        parseRule(line)
    }

    // Take each rule, if rule already exists, add the next
    // value to the rule array. Otherwise, create the rule
    let _ = extractedRules.map { rule in
        if var existingRule = rulesDict[rule.0] {
            existingRule.append(rule.1)
            rulesDict[rule.0] = existingRule
        } else {
            rulesDict[rule.0] = [rule.1]
        }
    }

    return rulesDict
}

/// Take a single report, search through the array
/// Take a value from the report. Check all rules to verify that, that
/// value is printed before all associated values in its associated rule.
/// - Parameters:
///   - report: the list of integers representing page updates
///   - rules: Integer, array pairs. The int represents a value and the array is all the other values it must print before
/// - Returns: the report if it passes, otherwise, nil
func validate_report(_ report: [Int], using rules: [Int: [Int]]) -> [Int]? {

    for rule in rules {
        // If the rule does not apply, skip
        if !report.contains(rule.key) {
            continue
        }
        // Set key index
        guard let keyIndex = report.firstIndex(of: rule.key) else {
            print("Rule \(rule.key) does not apply to list")
            continue
        }

        let valueIndices = rule.value.compactMap { report.firstIndex(of: $0) }

        guard let firstRuleIndex = valueIndices.min() else {
            continue
        }

        if keyIndex > firstRuleIndex {
            return report
        }
    }

    return nil
}

/// Used to take a report and use the rules to repair the report.
/// That is, to reorder the elements so that they comply with the rules.
/// - Parameters:
///   - report: An array of values, currently non compliant
///   - rules: An Dictionary of arrays, representing a value and its associated rules.
/// - Returns: An array of values, now compliant with rules.
func repairReport(_ report: [Int], using rules: [Int: [Int]]) -> [Int] {

    var currentReport: [Int] = report
    var changeMade: Bool = true

    // Continue to review rules until no changes made
    while changeMade {
        

    }

    return currentReport
}

main()
