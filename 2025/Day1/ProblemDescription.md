# Problem

I need to count the number of times that a dial is pointing to zero. 
Initally, I was counting the number of times the dial ended a rotation
on 0.
However, this time i need to count the number of times the dial ends or 
passes over the 0 position. 

## previous challenge

The previous challenge used the following code to find the postions: 
```swift
let result = (currentValue + (rotation) % totalDialPositions + totalDialPositions) % totalDialPositions
```
This code should allow for rotations of the dial which are larger than the total number of dial postions available -- by many times. 

**For example**
```swift
let rotation = 120
let totalDialPostions = 100
let currentValue = 50 // Starting value

let part1 = (120) % 100     //20
let part2 = 50 + 20 + 100   //170
let part3 = 170 % 100       //70
```

## The next challenge 
As illustrated in the above section. THe current process does not account for the dial passing over 
the zero postion. 

**First idea**
1. Take the inital position and the rotation and add them together.
2. Take the absolute (referenced from 0) rotations and divide it by the totalDialPositions
3. The number of rotations 


```swift
let rotation = 120
let totalDialPositions = 100
let currentValue = 50

let absoluteRotations = 120 + 50    //170
let fullRotations = 170 / totalDialPostions // 1
// Function continues as before
```
Return a tuple containing the new rotation value, 
This will neccesitate a refactor of the code. 

### Autopsy of idea
This did not work, and underexpressed the number of results. This is because this will work for very 
large numbers of rotations, rather than if a small rotation is made but 