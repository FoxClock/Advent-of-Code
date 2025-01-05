#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// AUTHOR: Hayden Foxwell
// PURPOSE: Calculate the difference between two co-ordinates on 2d plane
// DATE:    09/12/21
//

// Defines
#define BUFFER 20

// Function declarations
char* getDirection(char *input);
int getValue(char *input);


// Main function
int main()
{
    // Variables
    char *line;
    int horizontal = 0, vertical = 0;
    
    // Open file
    char *pos = "input.txt";

    FILE *fptr = fopen(pos, "r");

    if (fptr == NULL)
    {
        printf("Error unable to read file!");
        getchar();
        return -1;
    }

    // =====================
    // Get input from file
    while ((fgets(line, BUFFER, fptr)))
    {
        // extract direction
        char *direction = getDirection(line);
        // extract value
        int value = getValue(line);

        printf("Direction: %s, Value: %d \n", direction, value);
    
        // either add depth or horizontal position
        if (strcmp(direction, "forward") == 0)
        {
            horizontal += value;
        }
        else if (strcmp(direction, "up") == 0)
        {
            vertical -= value;
        }
        else
        {
            vertical += value;
        }
    }
    // =====================
    
    // Display result
    printf("Horizontal Pos: %d, Vert pos: %d \n", horizontal, vertical);
    printf("Apparent answer; %d \n", horizontal * vertical);
}


// Extracts the direction from the input
// Returns the string (forward | up | down)
char *getDirection(char *input)
{
    char *sub = malloc(BUFFER);
    int length, c = 0;

    length = strlen(input);
    
    while (c < length && !isspace(input[c])) {
        sub[c] = input[c];
        c++;
    }
    sub[c] = '\0';

    return sub;
}

// Returns the integer value from line input
int getValue(char *input)
{
    size_t length;
    int offset = 1;
    char buffer[2];

    length = strlen(input);
    offset = length - 2;

    memcpy(buffer, &input[offset], 1);

    return atoi(buffer);
}