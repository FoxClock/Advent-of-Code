// AUTHOR:	Hayden Foxwell
// DATE:	08-12-2022
// PURPOSE:	Day 1 -
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
#define ARRSIZE 400


/* Function definitions */
void bubbleSort(int array[], int size);


/* Main function */
int main() {

    // Variables
    char *number = malloc(BUFFSIZE);
    size_t arr_size = ARRSIZE * sizeof(int);
    int total = 0, count = 0;
    int *cal_list = malloc(arr_size);

    // Allocate heap memory for cal_list
    cal_list = memset(cal_list, 0, arr_size);


    // Open file
    FILE *file = open_file(INPUT_FILE, "r");
    
    // Read a line from the file
    while (fgets(number, sizeof(number), file) != NULL) {

        if (number) {
            int value = atoi(number);
            if (value)
            {
                total = total + value;
                value =  0; 
            } else {
                cal_list[count] = total;
                total = 0; count++;
            }
        }

    }

    cal_list[count + 1] = total;
    total = 0;

    for (int i = 0; i < count; ++i) {
        printf("Total-%i:\t%i\n", i, cal_list[i]);
    }

    // Sort the array first
    size_t cal_len = ARRSIZE;              // This is the size of the array
    printf("Cal_len:\t%zu\n", cal_len);
    bubbleSort(cal_list, cal_len);
    
    // Sum first 3 items
    total = 0;
    for (int x = 0; x < 3; ++x)
    {
        printf("%i\t%i\n", x, cal_list[x]);
        total = total + cal_list[x];
    }
    
    // Print total
    printf("total: %i\n", total);

    // Free memory
    free(number);
    fclose(file);
    return 1;
}