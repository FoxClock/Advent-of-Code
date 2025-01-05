// AUTHOR:	Hayden Foxwell
// DATE:	24-12-2021
// PURPOSE:	Day 5 - Determine where overlapping lines occur
//          in a field of given inputs.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// Defines
#define LINE_BUFFER 512
#define LINE_NUMS 512
#define MAX_ARRAY_BOUNDS 1000

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
void populateField(int bitfield[MAX_ARRAY_BOUNDS][MAX_ARRAY_BOUNDS], struct line lines[]);
void drawLine(int x0, int x1, int y0, int y1, int bitfield[MAX_ARRAY_BOUNDS][MAX_ARRAY_BOUNDS]);
void plotLineHigh(int x0, int x1, int y0, int y1, int bitfield[MAX_ARRAY_BOUNDS][MAX_ARRAY_BOUNDS]);
void plotlineLow(int x0, int x1, int y0, int y1, int bitfield[MAX_ARRAY_BOUNDS][MAX_ARRAY_BOUNDS]);


// -Debug functions
void print_input(FILE *fptr);

// ++++++++++++++++++++++++
// MAIN FUNCTION
// ++++++++++++++++++++++++
int main(void)
{
    // constants
    const int FIlENameLength = 10;
    
    // variables
    int sum = 0;
    FILE *fptr;
    char *filename = "input.txt";                               // Get file name use (readLine()) for user input
    struct line lines[LINE_NUMS];                               // Array of structs for storing lines
    int fieldArray[MAX_ARRAY_BOUNDS][MAX_ARRAY_BOUNDS] = {0};   // array that represents the board

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
    populateField(fieldArray, lines);
    
    // Print the field
    for (int x = 0; x < MAX_ARRAY_BOUNDS; x++)
    {   
        printf("|");
        for (int y = 0; y < MAX_ARRAY_BOUNDS; y++)
        {
            printf("%i", fieldArray[y][x]);
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

/* Reads user input from the stdin
// char* readLine()
// {
//     char *line = malloc(LINE_BUFFER);
//     fgets(line, LINE_BUFFER, stdin);
//     line[strlen(line)] = '\0';
//     return line;
// } */

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

// Takes the structs and extracts the coordinates of the lines
// sends it to the drawLine to be plotted onthe bitfield (done in place)
void populateField(int bitfield[MAX_ARRAY_BOUNDS][MAX_ARRAY_BOUNDS], struct line lines[])
{   
    // For each of the stucts extract the coordinates
    for (int line = 0; line < number_of_lines; ++line)
    {
        int x1 = lines[line].startx,
            x2 = lines[line].endx,
            y1 = lines[line].starty,
            y2 = lines[line].endy;

        // Plot the line of the bitfield
        drawLine(x1, x2, y1, y2, bitfield);
    }
}

// Implements Bresenham's line algorithm to modify the bitfield in place
void drawLine(int x0, int x1, int y0, int y1, int bitfield[MAX_ARRAY_BOUNDS][MAX_ARRAY_BOUNDS])
{
    if (abs(y1 - y0) < abs(x1 - x0))
    {
        if (x0 > x1)
        {
            plotlineLow(x1, x0, y1, y0, bitfield);
        }
        else
        {
        
            plotlineLow(x0, x1, y0, y1, bitfield);
        }
    }
    else
    {
        if (y0 > y1)
        {
            plotLineHigh(x1, x0, y1, y0, bitfield);
        }
        else
        {
            plotLineHigh(x0, x1, y0, y1, bitfield);
        }
    }
}

void plotLineHigh(int x0, int x1, int y0, int y1, int bitfield[MAX_ARRAY_BOUNDS][MAX_ARRAY_BOUNDS])
{
    //TODO: Implement Bresenham's line algorithm for low values
    // Variables
    int dx = x1  - x0,
        dy = y1 - y0,
        xi = 1,
        D,
        x;

    if (dx < 0)
    {
        xi = -1;
        dx = -dx;
    }
    D = (2 * dx) - dy;
    x = x0;

    for (int y = y0; y <= y1; y++)
    {
        bitfield[x][y] += 1;
        if (D > 0)
        {
            x = x + xi;
            D = D + (2 * (dx - dy));
        }
        else
        {
            D = D * (2 * dx);
        }
    }
    
}

void plotlineLow(int x0, int x1, int y0, int y1, int bitfield[MAX_ARRAY_BOUNDS][MAX_ARRAY_BOUNDS])
{
    //TODO: Implement Bresenham's line algorithm for high values
    // Variables
    int dx = x1  - x0,
        dy = y1 - y0,
        yi = 1,
        D,
        y;

    if (dy < 0)
    {
        yi = -1;
        dy = -dy;
    }
    D = (2 * dy) - dx;
    y = y0;

    for (int x = x0; x <= x1; x++)
    {
        bitfield[x][y] += 1;
        if (D > 0)
        {
            x = y + yi;
            D = D + (2 * (dy - dx));
        }
        else
        {
            D = D * (2 * dy);
        }
    }
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