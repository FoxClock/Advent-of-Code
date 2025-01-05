/* ===========================*/
/* === Includes === */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*============================*/
/* === Defines === */
#if (0) 
    #define INPUT_FILE "input.txt"
#else
    #define INPUT_FILE "sample_input.txt"
#endif

#define BUFFER 256


/*============================*/

/*============================*/
/*=== Globals === */
typedef struct number
{
    char* text;
    int value;
}number;

number numbers[] = {
    [0]={"one", 1},
    [1]={"two", 2},
    [2]={"three", 3},
    [3]={"four", .value=4},
    [4]={"five", .value=5},
    [5]={"six", .value=6},
    [6]={.text="seven", 7},
    [7]={.text="eight", 8},
    [8]={.text="nine", 9},
};

FILE* open_file(char* filepath, char* mode) {
    FILE *file;

    // Check that filepath is not empty
    if (!filepath) {
        printf("Error, No input file Specified.\n");
    }

    // Open file from filepath
    file = fopen(filepath, mode);

    if (!file) {
        printf("Error, could not open File: %s \n", filepath);
        exit(1);
    }

    return file;
}

int main() {

    //Variables
    char* line = malloc(BUFFER);

    // Open file
    FILE* opened_file = open_file(INPUT_FILE, "r");

    // Iterate through lines in the file
    while (fgets(line, BUFFER, opened_file) != NULL) {
        
        int counter = 0;
        // Check if current character is number
        while (!isspecial(line[counter])) {
            if (isnumber(line[counter]))
            {
                printf("Number: %c", line[counter]);
            }
            counter++;
        }
    }

    // Report success
    return 0;
}
