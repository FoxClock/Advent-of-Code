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
    let test: Bool = false
    let input_file: String = test ? "test_input.txt" : "input.txt"
    let fileURL = createURL(input_file)

    // Variables
    var data: String
    var reportList: [String]
    var reportValueList: [Int] = []
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
        reportValueList = createReport(singleLine: report)

        ReactorStatusList.append(determineReactorStatus(reportValueList))
    }

    // DEBUG: Print list
    for status in ReactorStatusList.enumerated() {
        print("\(status.offset) -- \(status.element)")
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
    // Enum
    // Power state of the reactor
    enum powerState {
        case constant
        case increasing
        case decreasing
    }
    
    // Constants
    let errorMargin = (smallest: 1 , largest: 3)

    // Variables
    // Assume reactor safe to begin with
    var status = reactorStatus.safe
    var firstValue = report.first!

    // Set reactor power state
    // This trend must remain the same over the report
    let reactorPowerState = firstValue - report[1] > 0 ? powerState.increasing : powerState.decreasing
    
    // Iterate over all values in the report checking if value is greater than constant
    // First value is saved as comparator
    for stateIndex in 1..<report.count {
        let variance = firstValue - report[stateIndex]
        
        let newPowerState = variance > 0 ? powerState.increasing : powerState.decreasing

        // Set status based on boundaries
        // If any boundary is out of range OR Powerstate changed mark unsafe
        if (abs(variance) < errorMargin.smallest || abs(variance) > errorMargin.largest) ||
         reactorPowerState != newPowerState {
            status = reactorStatus.unsafe
        }

        // increment first value to current value
        firstValue = report[stateIndex]
    }
    return status
}

/* MARK: Main entrypoint */
main()