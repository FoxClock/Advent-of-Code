// AUTHOR:	Hayden Foxwell
// DATE:	24-04-2024
// PURPOSE:	Day 8 - Recreate a 7 segment display

/* Imports */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "../Common/common.h"
/* === */

/* Defines */
#if 0
    #define INPUT_FILE "testInput.txt"
#else
    #define INPUT_FILE "input.txt"
#endif

#define BUFFER 1024
#define DEBUG 0
/* === */

/* VALUES */
// Constants

// Variables

/* === */

/* Functions */

/* === */

/* Main function */
int main()
{
    // Variables
    int counter = 0;
    FILE* file = NULL;

    // Read file
    file = openFile(INPUT_FILE);
    CharVector2D *char_vector = CSVToCharVect(file, ' ');

    // Iterate to the end of each line (each line is 14 items long)    
    for (int i = 14 ; i < char_vector->len;  i+= 15 )
    {
        // Start at the end and move backwards a token 4 times
        // there are 4 values at the end of a line (denoted by a | separator)
        for (int j = i ; j > ( i - 4 );  j--)
        {
            // While values are alpha (increment a counter)
            int count = 0;
            while (isalpha(char_vector->data[j][count]))
            {
                count++;
            }

            // unique values are either 2, 4, 7 or 3 characters long,
            // so count only strings which are this long. 
            if (count == 2 || count == 4 || count == 7 || count == 3) 
            { 
                counter++; 
                printf("Line[%i]:\t%s\n", i, &char_vector->data[i][0]);
            }
        }
    }

    // Print out the final count of unique values
    printf("Counter value:\t%i\n", counter);

    // free all dedicated memory in this scope.
    free(char_vector);
    fclose(file);
    return 0;
}

/* Auxilary functions */

/* === */
