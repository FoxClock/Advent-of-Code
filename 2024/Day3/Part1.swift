import Foundation
import RegexBuilder

func main() -> Void {
    let testing = false
    let fileName = testing ? "test_input.txt" : "input.txt"
    let fileURL = createURL(inputFile: fileName)
   
   // Define regex for "MUL(digits,digits)"
    let mulPattern: Regex<Regex<(Substring, Regex<OneOrMore<Substring>.RegexOutput>.RegexOutput, Regex<OneOrMore<Substring>.RegexOutput>.RegexOutput)>.RegexOutput> = Regex {
        "mul"
        "("
        Capture { OneOrMore(.digit) }
        ","
        Capture { OneOrMore(.digit) }
        ")"
    }

    // Variables
    var stringContents: String
    var answer: Int = 0

    // Get string contents
    do {
        stringContents = try String(contentsOf: fileURL, encoding: .utf8)
    } catch let err {
        print("Unable to decode String: \(err.localizedDescription)")
        exit(EXIT_FAILURE)
    }

    // Get the values from the string
    let extractedValues = getMatches(mulPattern, from: stringContents)

    // Multiply the two values together and add them to the answer
    answer = extractedValues.reduce(0) { partialResult, value  in
        partialResult + (value.first * value.second)
    }

    print("Answer: \(answer)")

}

// MARK: Auxiliary functions 
func createURL(inputFile: String) -> URL {
    let currentDirectoryPath = FileManager.default.currentDirectoryPath
    let fileURL = URL(fileURLWithPath: currentDirectoryPath).appendingPathComponent(inputFile)

    return fileURL
}

func getMatches(
    _ pattern : Regex<Regex<(Substring, Regex<OneOrMore<Substring>.RegexOutput>.RegexOutput, Regex<OneOrMore<Substring>.RegexOutput>.RegexOutput)>.RegexOutput>,
    from input: String
) ->  [(first: Int, second: Int)] {
    // Constants
    // Get all matches from the string
    let matches: [Regex<Regex<Regex<(Substring, Regex<OneOrMore<Substring>.RegexOutput>.RegexOutput, Regex<OneOrMore<Substring>.RegexOutput>.RegexOutput)>.RegexOutput>.RegexOutput>.Match] =  input.matches(of: pattern)
    // Get first and second value from the match
    let values = matches.map { match in 
            // Constants
            // Get first and second value ( as regex match )
            let firstValue = String( match.output.1 )
            let secondValue = String( match.output.2)

            // Cast and unwrap the values
            guard let firstInt = Int(firstValue),let secondInt = Int(secondValue) else {
                return (first: 0, second: 0)
            }

            return (first: firstInt, second: secondInt)
    }

   return values
}

// MARK: Main entrypoint
main()
