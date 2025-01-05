#include <stdio.h>
#include <stdlib.h>

///
/// Author: Hayden Foxwell
/// Purpose: Solve challenge 1, Advent of code. Count the number of times 
///          a value increases from the previous. 
/// Date:   08/12/21

#define LINE_LENGTH 10

int main()
{
    // Create file pointer and open file
    FILE *fptr = fopen("input.txt", "r");

    // Check if pointer is valid
    if (fptr == NULL)
    {
        printf("Error opening files");
        getchar();
        fclose(fptr);
        exit(1);
    }

    // While input is not EOF read lines
    // print each line to the console <- Debug
    char line[LINE_LENGTH];
    int count = 0, prev = 0, current;

    while ((fgets(line, LINE_LENGTH, fptr)) != NULL)
    {
        current = atoi(line);

        if (prev == 0)
        {
            prev = current;
        }
        else 
        {
            count += 1 * (prev < current);
            printf("Prev: %d, Curr: %d", prev, current);
            if (current > prev)
            {
                printf("\t(Increased) \n");
            }
            else 
            {
                printf("\t(Decreased) \n");
            }
            prev = current;
        }
    
    }
    printf("The count is %d \n", count);
    
    fclose(fptr);
    return 0;
}