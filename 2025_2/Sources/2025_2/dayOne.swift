struct DayOne: PuzzleDay {
    
    var puzzleInput: [String]

    init(rawInput: String) {
        self.puzzleInput = splitInput(rawInput).map( {String($0)} )
    }

    func partOne() -> String {
        let dialPostion = 50
        var answer: String = ""
    
        let alignedValues = scaleValues(puzzleInput)
        let rotations = applyRotations(start: dialPostion, rotations: alignedValues)
        let zeroCount = rotations.count(where: {$0 == 0})

        answer =  "Answer: \(zeroCount)"

        return answer
    }

    func partTwo() -> String {
        let dialPostion = 50
        var answer: String = ""
    
        let alignedValues = scaleValues(puzzleInput)
        let rotations = applyRotations2(start: dialPostion, rotations: alignedValues)
        let zeroCount = rotations.count(where: {$0 == 0})

        answer =  "Answer: \(zeroCount)"

        return answer
    }
}

// =====================
// Common Function(s)
// =====================
func scaleValues(_ input: [String]) -> [Int] {
    let output: [Int]

    output = input.compactMap { inputValue in
        if inputValue.contains("R") {
            let newVal = inputValue.dropFirst()
            return Int(newVal)
        } else {
            let newVal = inputValue.dropFirst()
            return (-1 * (Int(newVal) ?? 0))
        }
    }

    return output
}
// #####################

// =====================
// Part one Functions
// =====================
func rotateDial(currentValue: Int, rotation: Int, dialSize: Int = 99) -> Int {
    let totalDialPositions = dialSize + 1

    return (currentValue + (rotation) % totalDialPositions + totalDialPositions) % totalDialPositions
}

func applyRotations(start: Int, rotations: [Int]) -> [Int] {

    // Reduce the outline 
    rotations.reduce(into: [start]) {acc, rotation in
        let next = rotateDial(currentValue: acc.last ?? 0, rotation: rotation)
        acc.append(next)
    }
}
// #####################

// =====================
// Part two Functions
// =====================
func rotateDial2(currentValue: Int, rotation: Int, dialSize: Int = 99) -> (Int, Int) {
    let totalDialPositions = dialSize + 1
    let absoluteRotations = currentValue + rotation
    let fullRotations = absoluteRotations / totalDialPositions
    let finalRotation = (currentValue + (rotation) % totalDialPositions + totalDialPositions) % totalDialPositions

    if finalRotation == 0 {
        return (finalRotation, 0)
    } else {
        return (finalRotation, fullRotations)
    }
}

func applyRotations2(start: Int, rotations: [Int]) -> [Int] {

    // Reduce the outline 
    rotations.reduce(into: [start]) {acc, rotation in
        let result = rotateDial2(currentValue: acc.last ?? 0, rotation: rotation)
        let (nextValue, zeroCount) = result
        for _ in 0..<zeroCount {acc.append(0)}
        acc.append(nextValue)
    }
}
// #####################