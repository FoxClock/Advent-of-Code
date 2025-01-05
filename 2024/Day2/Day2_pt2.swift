/* MARK: imports */
import Foundation

/* Enums */
enum reactorStatus {
    case safe
    case unsafe
}

/* MARK: Structs / Classes */


/* MARK: Main Function */
func main() {
    // Constants
    let test: Bool = true
    let input_file: String = test ? "test_input.txt" : "input.txt"
    let fileURL = createURL(input_file)

    // Variables
    var data: String
    var reportList: [String]
    var ReactorStatusList: [reactorStatus] = []

    // read file contents
    do {
        data = try String(contentsOf: fileURL, encoding: .utf8)
    } catch let err {
        print("Unable to read file: \(err.localizedDescription)")
        exit(EXIT_FAILURE)
    }

    // Split data into reports
    reportList = parseReports(data: data)

    // Parse each report into integer list
    for report in reportList {
        // Create a reactor report
        let reportValueList = createReport(singleLine: report)
        let currentReactorStatus = determineReactorStatusWithDampener(reportValueList)
        ReactorStatusList.append(currentReactorStatus)
    }

    func colourise(_ inputString: String, status: reactorStatus) -> String {
        let red = "\u{001B}[31m"
        let green = "\u{001B}[32m"
        let reset = "\u{001B}[0m"
        
        switch status {
            case .safe:
                return "\(green)\(inputString)\(reset)"
            case .unsafe:
                return "\(red)\(inputString)\(reset)"
        }
    }

    // DEBUG: Print list
    for status in ReactorStatusList.enumerated() {
        let offset = String(format: "%-4d", status.offset)  // Left-align offset
        let reportItem = String(format: "%@", reportList[status.offset].padding(toLength: 30, withPad: " ", startingAt: 0))  // Left-align report item
        let element = String(format: "%10@", "\(status.element)")  // Right-align element

        let formattedString = "\(offset) -- \(reportItem) -- \(element)"
        print(colourise(formattedString, status: status.element))

    }

    print(
        "Safe reports: \(ReactorStatusList.filter { $0 == reactorStatus.safe}.count)"
    )
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

func createReport(singleLine: String) -> [Int] {
    // Constants
    // Split string by spaces
    let values = singleLine.split(separator: " ")

    // Variables
    var reportValues: [Int?]

    // Cast each to integer
    reportValues = values.map { Substring in
        Int(Substring)
    }

    // Unwrap optional values and return list
    return reportValues.compactMap { $0 }
}

func parseReports(data: String) -> [String] {
    // Constants
    // Split string into individual lines
    let reports = data.split(separator: "\n")

    // Cast each line to a string and return
    return reports.map { Substring in
        String(Substring)
    }
}

func determineReactorStatus(_ report: [Int]) -> reactorStatus {    
    // Constants
    let positiveErrorMargin: Set<Int> = [1,2,3]
    let negativeErrorMargin: Set<Int> = [-1,-2,-3]
    
    // Iterate over values adding them together 
    // Produces an array of variances
    let reactorVariances = Set((0..<report.count - 1).map { report[$0 + 1] - report[$0] })
    
    // Check that all reactor variances are within margins
    if reactorVariances.isSubset(of: positiveErrorMargin) || reactorVariances.isSubset(of: negativeErrorMargin) {
        return .safe
    } else {
        return .unsafe
    }
}

func determineReactorStatusWithDampener(_ report: [Int]) -> reactorStatus {
    // If already safe, return safe
    if determineReactorStatus(report) == .safe {
        return .safe
    }
    
    // Try removing each level
    for index in 0..<report.count {
        // Create a new list without the current index
        var modifiedReport = report
        modifiedReport.remove(at: index)
        
        // Check if modified report is safe
        if determineReactorStatus(modifiedReport) == .safe {
            return .safe
        }
    }
    
    // If no removal makes it safe, return unsafe
    return .unsafe
}

/* MARK: Main entrypoint */
main()