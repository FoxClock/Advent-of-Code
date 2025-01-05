// AUTHOR:	Hayden Foxwell
// DATE:	07-01-2022
// AUTHOR:	Hayden Foxwell
// DATE:	07-01-2022
// PURPOSE:	Day 7 - find the index in the array in which all elements can
//                  move to with the least amount of effort. Each fuel for a
//                  'Crab submarine' now increases linearly as they move.
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "../Common/common.h"

// Defines
#if 0
    #define INPUT_FILE "testinput.txt"
#else
    #define INPUT_FILE "input.txt"
#endif

#define BUFFER 1024
#define DEBUG 0

// Structures

// Globals

// Functions
int calculate_crab_fuel(int value);
int find_min(struct Vector1D *positions);

/*****************************/
// Main Function             */
/*****************************/
int main() 
{

    // Consts

    // Variables
    int min;                        // Minimum value
    struct Vector1D *positions;     // 1D Vector

    // open file
    FILE *fptr = openFile(INPUT_FILE);

    // Read file
    positions = CSVToInt(fptr);
    
    // Get the minimum value of all positions
    min = find_min(positions);
   
    // Print out the result
    printf("Result:\t%i\n", min);

    // Return the memory used for the vector
    free(positions);

    return 0;
}

/*****************************/
//      Auxilary Functions   */
/*****************************/

/// @brief Calculate the triangle number for a particular value. 
/// @param value    Int, the index for the triangle value. 
/// @return Int, the triangle value for the corresponding value. 
int calculate_crab_fuel(int value)
{
    return (value * (value + 1)) / 2;
}

int find_min(struct Vector1D *positions)
{
    // Prefunction checks
    if (!positions)
    {
        printf("No ArrayList passed to function!\n");
        exit(1);
    }

    /* Constants */

    /* Variables */
    int array_length = positions->len;
    int min = INT32_MAX;
    int max = positions->data[max_index(positions->len, positions->data)];
    int result_array[BUFFER] = {0};
    
    
    // Debug prints
    if (DEBUG) printf("MAX:\t%i\n", max);
    if (DEBUG) printf("ArrayLen:\t%zu\n", positions->len);


    for (int x = 0; x <= max; x++)
    {
        for (int y = 0; y < positions->len; y++)
        {
            if (DEBUG) printf("[%i] %i\t|\t%i\n", y, positions->data[y], positions->data[y] - x);
            result_array[y] = calculate_crab_fuel(abs(positions->data[y] - x));
        }

        // Calculate the sum of the array of results
        int sum = calculateArraySum(positions->len, result_array);
        
        if (DEBUG) ("Sum[%i]:\t%i\n", x, sum);
        
        // If the sum is smaller than the current minimum, then over-
        // write minimum.
        if (min > sum)
        {
            min = sum;
        }
    }

    return min;
}