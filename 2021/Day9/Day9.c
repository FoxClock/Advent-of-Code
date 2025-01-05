// AUTHOR:	Hayden Foxwell
// DATE:	05-05-2024
// PURPOSE:	Day 9 -

/* Imports */
#include <stdlib.h>
#include "../Common/common.h"

// ==========================

/* Defines */
#define TEST_FILE "testInput.txt"
#define INPUT_FILE "input.txt"
#define DEBUG 1
#define DEBUG_PRINT(message, value) //{printf("DEBUG: %s:\t%i\n", message, value);}

#define OUT_BOUND_HEIGHT -1
# define MIN_HEIGHT 0

// ===========================

/* Global values */

// ============================

/* Function definitions */
size_t get_file_length(FILE * input_file);
int find_floor_width(FILE *input_file);
int* get_integer_array(FILE *input_file, size_t length);
int * generate_array_of_lowpoints(int length, int width, int value_array[]);
int sum_of_danger_levels(size_t size, int height_array[size]);

// ============================

/* Main function */
int main(int argc, char const *argv[])
{
    /* Variables */
    FILE *file_pointer = NULL;
    char *input_file;
    int* danger_array;
    int width = 0, sum_of_danger = 0;

    // Determine if test or real data should be used
    if (argc < 2) { perror("Missing argument: FILE [ test / *]"); exit(EXIT_FAILURE); }
    if (strcmp("test", argv[1]) == 0)
    { input_file = TEST_FILE; }
    else
    { input_file = INPUT_FILE; }

    // Open file 
    file_pointer = openFile(input_file);
    if ( !file_pointer ) { perror("File was not opened!\n"); exit(EXIT_FAILURE); }

    // Get length of file
    size_t length = get_file_length(file_pointer);

    // Get the width of the floor
    width = find_floor_width(file_pointer);

    // Convert characters into integers and assign them to an array
    int* value_array = get_integer_array(file_pointer, length);

    // Get array of danger values
    danger_array = generate_array_of_lowpoints(length, width, value_array);

    // Sum the array
    sum_of_danger = sum_of_danger_levels(BUFSIZ, danger_array);

    printf("Danger points:\t %i \n", sum_of_danger);

    free(danger_array);
    free(value_array);
    fclose(file_pointer);
    return 0;
}

// ######################
/* Auxilary functions */
// ######################
size_t get_file_length(FILE * input_file)
{
    // Variables
    char character;
    size_t count = 0;

    // Reset file pointer to start of file 
    rewind(input_file);

    // Get character
    character = fgetc(input_file);
    while (character != EOF)
    {
        if (character == '\n') 
        {
            character = fgetc(input_file);
            continue;
        } else {
            character = fgetc(input_file);
            count++;
        }
        DEBUG_PRINT("COUNT:", count);
    }

    // Return number of characters
    return count;
}

// FInd the width of the floor
int find_floor_width(FILE *input_file)
{
    // Variables
    int width = 0; 

    // rewind pointer
    rewind(input_file);

    // iterate over file until newline found
    char character = fgetc(input_file);
    while (character != '\n')
    {
        width++;
        character = fgetc(input_file);
    }

    return width;
}

int *get_integer_array(FILE *input_file, size_t length)
{
    // Variables 
    int count = 0;

    // Create array of length
    int* values = malloc(sizeof(int) * length);
    memset(values, 0, length);      // Initialise all values to 0

    // Rewind file pointer
    rewind(input_file);

    char character = fgetc(input_file);
    while (character != EOF)
    {
        // Discard newlines
        if (character == '\n' ) 
        { 
            character = fgetc(input_file);
            continue; 
        }

        // Print out value
       // printf("Value:\t%c\n", character);
        values[count] = charToInt(character);

        // Get next character
        character = fgetc(input_file);
        // increment counter
        count++;
    }

    return values;
}

int *generate_array_of_lowpoints(int length, int width, int value_array[]) 
{
    /* Constants */
     const int up = 0, left = 1, right = 2, down = 3;

    /* Variables */
    // four locations around a point in the floor
    // [0] is up, [1] is left, [2] is right, [3] is down.
    int grid_compare[4] = {OUT_BOUND_HEIGHT};
    int *height_array = malloc(BUFSIZ * sizeof(int));
    int low_point_count = 0;
    // initialise row and column to 0
    // calculate the number of rows and store in num_rows
    int column = 0, row = 0, num_rows = length / width;

    // Memory set height array to error value
    memset(height_array, OUT_BOUND_HEIGHT, BUFSIZ * sizeof(int));

    /* 
    * Iterate over the number of rows in the file
    * assigning the pole values to either the respective
    * value, or an error value of -1
    */
    while (row < num_rows)
    {
        int low = 0;
        int value = value_array[width * row + column];
    
        // Top row cannot have above values
        // Top should already be initalized to OUT_BOUND_HEIGHT
        if (row > 0)
        {
            grid_compare[up] = value_array[width * (row - 1) + column];
        } 
    
        // if bottom row down cannot have values 
        if (row == (num_rows - 1) )
        {
            grid_compare[down] = OUT_BOUND_HEIGHT;
        } else {
            grid_compare[down] = value_array[width * (row + 1) + column];
        }

        // if Column is 0 then no left value
        if (column > 0)
        {
            grid_compare[left] = value_array[width * row + (column - 1)];
        } else {
            grid_compare[left] = OUT_BOUND_HEIGHT;
        }

        // if the column is just under the width
        // set the right to the error value
        if (column < (width))
        {
            grid_compare[right] = value_array[width * row + (column + 1)];
        } else {
            grid_compare[right] = OUT_BOUND_HEIGHT;
        }

        // If the value is less than its neighbours
        // add one to the low point count
        int check_count = 0, greater_than_count = 0;
       for (int step = 0; step < 4; step ++) 
       {
            if (grid_compare[step] != OUT_BOUND_HEIGHT)
            {
                check_count ++;
                if (grid_compare[step] > value) 
                {
                    greater_than_count ++;
                }
            } else {
                continue;
            }
       }

       if (greater_than_count == check_count)
       {
        height_array[low_point_count] = value;
        low_point_count ++;
        low = 1;
       }

        // Print out values in original shape
        if (DEBUG == 1) {
            if (low) 
            {
                printf("\033[31;4m%i\033[0m", value); 
            } else {
                printf("%i", value);
            }
        }
       
       // If columns reaches width then reset columns 
       // and add a row
        if ( !(column < width -1) ) 
        {
            row ++; 
            column = 0; 
            printf("%c", '\n'); 
        } else {
            column ++;
        }
    }

    // Return array of values
    return height_array;
}

int sum_of_danger_levels(size_t size, int height_array[size])
{
    // Variables
    int sum = 0;

    // danger level is 1 + value
    // increase all heights by value of 1
    // and sum them
    for (int pointer = 0; pointer < size; pointer++)
    {
        sum = sum + (height_array[pointer] + 1);
    }

    // Return sum
    return sum;
}
