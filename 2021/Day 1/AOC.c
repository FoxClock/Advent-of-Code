#include <stdio.h>
#include <stdlib.h>

//
// Author: Hayden Foxwell
// Purpose: Take mesurement values and sum groups of 3 together.
//          Count the number of times these 3 group sums increase in value
//
//  Date: 08/12/21


#define BUFFER 10
#define SUM_SIZE 4

// Function declarations
int sums(int *array);

int main() 
{
    // Get input file
    FILE *fptr = fopen("input.txt", "r");

    // Array storage for the read-in line. 
    char line[BUFFER];
    int vals1[SUM_SIZE];

    // Variables for file loop.
    int counter = 0, sum = 0;
    int prev = 0, current;
    int count = 0; 

    fgets(line, BUFFER, fptr);
    vals1[0] = atoi(line);
    fgets(line, BUFFER, fptr);
    vals1[1] = atoi(line);
    fgets(line, BUFFER, fptr);
    vals1[2] = atoi(line);

    // Read values from file, until EOF
    while (fgets(line, BUFFER, fptr))
    {   
        vals1[SUM_SIZE - 1] = atoi(line);

        prev = vals1[0] + vals1[1] + vals1[2];
        current = vals1[1] + vals1[2] + vals1[3];
        count += 1 * (prev < current);

        vals1[0] = vals1[1];
        vals1[1] = vals1[2];
        vals1[2] = vals1[3];
    }
    printf("Count: %d \n", count);
    fclose(fptr);
}

// FUNCTION: sums an array of integers, returns the sum
int sums(int *array)
{
    int total = 0;

    for (int i = 0; i < SUM_SIZE; i++)
    {
        total += array[i];
    }

    return total;
}