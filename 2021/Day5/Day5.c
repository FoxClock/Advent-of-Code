#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// AUTHOR:	Hayden Foxwell
// DATE:	24-12-2021
// PURPOSE:	Day 5 - Determine where overlapping lines occur
//          in a field of given inputs.

// Defines
#define LINE_BUFFER 512
#define LINE_NUMS 512

// Structs
struct line {
    int startx;
    int starty;
    int endx;
    int endy;
} line;

// Globals
int number_of_lines;

// Functions
char* readLine();
FILE* openFile(char filename[]);
void populate_lines(FILE *fptr, struct line lines[]);
int charToInt(char input);

// -Debug functions
void print_input(FILE *fptr);

// ++++++++++++++++++++++++
// MAIN FUNCTION
// ++++++++++++++++++++++++
int main(void)
{
    // constants
    const int FIlENameLength = 10;
    const int maxArrayBounds = 1000;
    
    // variables
    int sum = 0;
    FILE *fptr;
    char *filename = "input.txt";                   // Get file name use (readLine()) for user input
    struct line lines[LINE_NUMS];                       // Array of structs for storing lines
    int fieldArray[maxArrayBounds][maxArrayBounds] = {0}; // array that represents the board

    // open file
    fptr = openFile(filename);

    // Diagnostic
    // print contents of file
    //print_input(fptr);

    // Close and reopen file
    fclose(fptr);
    fptr = openFile(filename);

    // Get a line
    populate_lines(fptr, lines);

    // Close file
    fclose(fptr);

    // for each line where x1 = x2 OR y1 = y2
    for (int line = 0; line < number_of_lines; ++line)
    {
        int x1 = lines[line].startx,
            x2 = lines[line].endx,
            y1 = lines[line].starty,
            y2 = lines[line].endy;

        if (x1 == x2 || y1 == y2)
        {
            // Swap values so for loops work
            if (x1 > x2)
            {
                int temp = x1;
                x1 = x2;
                x2 = temp;
            }
            else if ( y1 > y2)
            {
                int temp = y1;
                y1 = y2;
                y2 = temp;
            }

            // For the values increment the field
            for (int x = x1; x <= x2; x++)
            {
                for (int y = y1; y <= y2; y++)
                {
                    fieldArray[x][y] += 1;
                }
            }
        }
    }
    
    // Print the field
    for (int x = 0; x < maxArrayBounds; x++)
    {   
        printf("|");
        for (int y = 0; y < maxArrayBounds; y++)
        {
            printf("%i", fieldArray[x][y]);
            if (fieldArray[x][y] > 1) sum += 1;
        }
        printf("|\n");
    }


    // Print Answer
    printf("Answer: %d", sum);

    // pause os for input
    getchar();
}

// ++++++++++++++++++++++++
// Auxuilary functions
// ++++++++++++++++++++++++

// Reads user input from the stdin
// char* readLine()
// {
//     char *line = malloc(LINE_BUFFER);
//     fgets(line, LINE_BUFFER, stdin);
//     line[strlen(line)] = '\0';
//     return line;
// }

// Opens file and validates that its open
FILE* openFile(char filename[])
{
    FILE *Filepointer = fopen(filename, "r");

    if (!Filepointer)
    {
        fprintf(stderr, "Cannot open file %s", filename);
        exit(1);
    }

    return Filepointer;
}

// take file pointer and read the line
// populate each struct with the start x,y and end x,y
void populate_lines(FILE *fptr, struct line lines[])
{
    // Constants
    const char *separator = " -> ";
    const char delimitor = ',';
    
    // Variables
    int line_number = 0, value = 0;
    char *input = malloc(LINE_BUFFER);
    char number[10];

    while (fgets(input, LINE_BUFFER, fptr) != NULL) 
    {
        //implementing strtok
        int count = 0, numcount = 0, valCount = 0;
        while (input[count] != '\n')
        {
            if (!isdigit(input[count]))
            {
                input[count] = '\0';
            }
            count++;
        }

        count = 0;
        
        while (valCount < 4)
        {
            if (isdigit(input[count]))
            {
                number[numcount] = input[count];
                numcount++;
            }
            else
            {
                if (isdigit(number[0]))
                {
                    value = atoi(number);
                    memset(number, 0, 10);
                    numcount = 0;
                }
                else
                {
                    memset(number, 0, 10);
                    numcount = 0;
                    value = -1;
                }

                if (value != -1)
                {
                    switch (valCount)
                    {
                    case 0:
                        lines[line_number].startx = value;
                        valCount++;
                        break;
                    
                    case 1:
                        lines[line_number].starty = value;
                        valCount++;
                        break;

                    case 2:
                        lines[line_number].endx = value;
                        valCount++;
                        break;

                    case 3:
                        lines[line_number].endy = value;
                        valCount++;
                        break;
                    
                    default:
                        fprintf(stderr, "Too many co-ordinate inputs!: %s", input);
                        break;
                    }
                }

            }
            count++;
        }

        line_number++;
    }
    // Set global variable to number of structs
    number_of_lines = line_number;
}

// Convert a character to an integer
int charToInt(char input)
{
    // Variables
    int output;
    
    output = input - '0';

    return output;
}

// ++++++++++++++++++++++++
// Debug Functions
// ++++++++++++++++++++++++
void print_input(FILE *fptr)
{
    char* line = malloc(LINE_BUFFER);
    while (fgets(line,LINE_BUFFER,fptr) != NULL)
    {
        printf("%s",line);
    }
    
    free(line);
}