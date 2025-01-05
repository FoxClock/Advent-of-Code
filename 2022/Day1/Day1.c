// AUTHOR:	Hayden Foxwell
// DATE:	08-12-2022
// PURPOSE:	Day 1 -

// Imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Common/common.h"


// Defines
#if (0)
    #define INPUT_FILE "testInput.txt"
#else
    #define INPUT_FILE "input.txt"
#endif

// buffer size
#define BUFFSIZE 10 * sizeof(char)


/* Function definitions */
void add_to_cal_list(int value, int *list);


/* Main function */

int main() {

    // Variables
    char *number = malloc(BUFFSIZE);
    int total = 0, max = 0;

    // Open file
    FILE *file = open_file(INPUT_FILE, "r");
    
    // Read a line from the file
    while (fgets(number, sizeof(number), file) != NULL) {
        int value = atoi(number);

        if (value && number != NULL) {
            total = total + value;
            value =  0; 
        } else {
            // Handle the newline for an elf
            printf("Total Cals for elf: %i\n", total);

            // Calculate maximum of totals
            if (total > max) {
                max = total;
            }

            total = 0;
        }

    }

    // Print the maximum value
    printf("Maximum value: \t%i\n", max);

    // Free memory
    free(number);
    fclose(file);
    return 1;
}
