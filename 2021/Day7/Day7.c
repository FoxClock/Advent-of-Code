// AUTHOR:	Hayden Foxwell
// DATE:	07-01-2022
// PURPOSE:	Day 7 - find the index in the array in which all elements can
//                  move to with the least amount of effort. 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

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
int find_min(struct Vector1D *positions);

/*****************************/
// Main Function             */
/*****************************/
int main() 
{
    // Consts

    // Variables
    int min;
    struct Vector1D *positions;

    // open file
    FILE *fptr = openFile(INPUT_FILE);

    // Read file
    positions = CSVToInt(fptr);
    
    min = find_min(positions);
   

    printf("Result:\t%i\n", min);

    free(positions);

    return 0;
}

/*****************************/
//      Auxilary Functions   */
/*****************************/

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
    if (DEBUG) ("MAX:\t%i\n", max);
    if (DEBUG) ("ArrayLen:\t%zu\n", positions->len);


    for (int x = 0; x <= max; x++)
    {
        
        for (int y = 0; y < positions->len; y++)
        {
            if (DEBUG) printf("[%i] %i\n", y, positions->data[y]);
            result_array[y] = abs(positions->data[y] - x);
        }

        int sum = calculateArraySum(positions->len, result_array);
        printf("Sum[%i]:\t%i\n", x, sum);
        if (min > sum)
        {
            min = sum;
        }

        if (DEBUG) break;
    }

    return min;
}