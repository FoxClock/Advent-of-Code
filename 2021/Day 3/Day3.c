#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// PURPOSE: To find the most common bit in each column of binary data
// AUTHOR: Hayden foxwell
// DATE:    10/12/21

// Defines
#define READ_LENGTH 20

// Function declarations
int getBit(char input);
FILE* getfile(char *fileName);
int gammaBit(int ones, int zeros);
int convertBinary(int s[], int length);

// Main function
int main() 
{
    // Variables
    char fileBuffer[INT16_MAX];
    char line[READ_LENGTH];

    // Define file input
    char* file = "input.txt";
    FILE *fptr = getfile(file);

    //===================
    // read file contents
    //===================
    int current_pos = 0;
    while ((fgets(line, READ_LENGTH, fptr)))
    {
        int count = 0;
        size_t length = strlen(line);

        while (count < length && !(strcmp(&line[count], "\n") == 0))
        {
            fileBuffer[current_pos] = line[count];
            current_pos++;
            count++;
        }
    }

    printf("%s \n", fileBuffer);
    
    // ===================
    // Get Most Common bit
    // ===================

    // Variables to track columns and buffer length
    size_t fileBuffer_length = strlen(fileBuffer);
    size_t line_length = strlen(line);
    int read_pos = 0, column = 0;
    
    // Set variable length array, initalise memory with 0s
    int column_sum_ones[line_length];
    memset(column_sum_ones, 0, line_length * sizeof(int));
    
    int column_sum_zeros[line_length];
    memset(column_sum_zeros, 0, line_length * sizeof(int));
    
    
    while (read_pos < fileBuffer_length)
    {
        // revolving value for position in column_sum
        column = read_pos % strlen(line);
        
        char bit = fileBuffer[read_pos];
        int value;
        value = getBit(bit);

        column_sum_ones[column] += (value);         // If value is 1, then add tht to total.
        column_sum_zeros[column] += !(value);       // if Value is 0, invert and add to total.

        read_pos++;
        
    }

    // Calculate gamma bits
    // Epsilon bits are the inverse of the gamma bits so 
    // this can be calculated later
    int byteArray[line_length];
    memset(byteArray, 0, line_length * sizeof(int));

    for (int x = 0; x < line_length; x++)
    {
        int bit = gammaBit(column_sum_ones[x], column_sum_zeros[x]);
        byteArray[x] =  bit;
        printf("Column %d: %d \n", x, bit);
    }


    // Get gamma vale
    // Then invert the array and calculate the epsilon value
    int gammaValue, epsilonValue;
    gammaValue = (convertBinary(byteArray, line_length));
    
    // Performs xor inversion of the array
    for (int i = 0; i < line_length; i++)
    {
        byteArray[i] = byteArray[i] ^ 1;
    }

    epsilonValue = (convertBinary(byteArray, line_length));
    // multiply values together
    int answer = (gammaValue * epsilonValue);
    printf("The answer is: %d\n", answer);

    // Close file
    fclose(fptr);
}

// Opens a file of given file name/path
FILE* getfile(char *fileName)
{
    // open file
    FILE *fptr = fopen(fileName, "r");

    if (!fptr)
    {
        printf("Error reading file!");
        getchar();
        exit(1);
    }

    return fptr;
}

// Returns the gamma bit for given columns
int gammaBit(int ones, int zeros)
{
    int column_bit;
        if (ones > zeros)
        {
            column_bit = 1;
        }
        else
        {
            column_bit = 0;
        }
    return column_bit;
}

// Converts char to int value.
int getBit(char input)
{
    int output;

    output = input - '0';

    return output;
}

// Convert binary array into decimal
int convertBinary(int s[], int length)
{
    int n = 0;
    int i;

    for (i = 0; i < length; ++i) {
        n <<= 1;
        n += s[i];
    }

    return n;
}