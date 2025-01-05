/* MARK: Imports */
import Foundation

/* MARK: Defines */

/* MARK: Structs */
struct valueLists {
    var left_list: [Int] = []
    var right_list: [Int] = []
}

/* MARK: Main function */
func main() {
    // Constants
    let test: Bool = false
    let input_file: String = test ? "test_input.txt" : "input.txt"
    let fileURL = createURL(input_file)
    let newlineSeparator = "\n"

    // Variables
    var values: valueLists
    var fileContents: String?
    var linesFromFile: [String.SubSequence]
    var listOfDifferences: [Int]

    do {
        fileContents = try String(contentsOf: fileURL, encoding: .utf8)

    } catch let err{
        print("Failure to read file - \(err.localizedDescription)")
        exit(EXIT_FAILURE)
    }

    // Unwrap filecontents 
    if let contents = fileContents {
        linesFromFile = contents.split(separator: newlineSeparator)
    } else {
        print("Unable to unwrap file contents")
        exit(EXIT_FAILURE)
    }

    // Get two lists of values
    do {
        values = try populateValueLists(inputValues: linesFromFile)
    } catch {
        print("Could not parse file into lists")
        exit(EXIT_FAILURE)
    }

    // Find the difference between subsequent smallest values
    listOfDifferences = subtractSmallestPairs(valueList: values)

    // Print out sum of differences
    let sum = listOfDifferences.reduce(0, +)
    print("Answer: \(sum)")
}

/* MARK: Auxilary functions */
func createURL(_ file_to_open: String) -> URL {
    // Constants
    let currentDirectoryPath = FileManager.default.currentDirectoryPath

    // Create file URL from CWD and file name
    var fileURL = URL(filePath: currentDirectoryPath)
    fileURL = fileURL.appending(path: file_to_open)

    return fileURL
}

func populateValueLists(inputValues: [String.SubSequence]) throws -> valueLists {
    // Errors
    enum populateListError: Error {
        case leftValueError, rightValueError
    }
    
    // Constants
    let stringSeparator = "   "

    // Variables
    var list = valueLists()
    

    // Iterate through all lines in file
    for line in inputValues {
        var strValue: String
        var split_substring: [String.SubSequence]

        // Split subsequence by whitespace
        split_substring = line.split(separator: stringSeparator)
        
        // Convert the left value to integer
        strValue = String(split_substring.removeFirst())
        guard let leftValue = Int(strValue) else {
            throw populateListError.leftValueError
        }

        // Convert the right value to integer
        strValue = String(split_substring.removeFirst())
        guard let rightValue: Int = Int(strValue) else {
            throw populateListError.rightValueError
        }

        // Assign to the struct
        list.left_list.append(leftValue)
        list.right_list.append(rightValue)
    }

    return list
}

func subtractSmallestPairs(valueList: valueLists) -> [Int] {
    // Variables
    var leftList = valueList.left_list
    var rightList = valueList.right_list
    var leftSmallest: Int
    var rightSmallest: Int
    var results = [Int]()

    for _ in 0..<valueList.left_list.count {
        leftSmallest = leftList.min()!
        rightSmallest = rightList.min()!

        // Remove values from list
        leftList.remove(at: leftList.firstIndex(of: leftSmallest)!)
        rightList.remove(at: rightList.firstIndex(of: rightSmallest)!)

        // Subtract left from right
        let difference = abs(leftSmallest - rightSmallest)

        results.append(difference)
    }

    return results
}

/* MARK: Main Entry point */
main()
