// AUTHOR:	Hayden Foxwell
// DATE:	14-12-2022
// PURPOSE:	Day 2 -

// Imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../Common/common.h"


// Defines
#if (0)
    #define INPUT_FILE "testInput.txt"
#else
    #define INPUT_FILE "input.txt"
#endif

// Buffers
#define FILE_BUFFER 1024
#define LINE_BUFFER 10

/* Function definitions */
int play_val(char play);
int game_val(char player1, char player2);
void plays(char line[], char output[], size_t line_length, size_t output_length);
// ==================== //


/* Main Function */
int main(void)
{
    // Variables
    FILE *fptr = open_file(INPUT_FILE, "r");             // input file
    char *line = malloc(LINE_BUFFER * sizeof(char));    // line from text file
    char *moves = malloc(2 * sizeof(char));             // Two moves from line
    int *games = malloc(1 * sizeof(int));               // Each games total score
    int move_value = 0, game_result_value = 0;          // A move, a game result
    int sum = 0;                                        // Sum total of all games
    
    // Print file contents
    int count = 0;
    while (fgets(line, LINE_BUFFER, fptr))
    {
        // Extract player's choices
        plays(line, moves, LINE_BUFFER, 2 * sizeof(char));

        printf("Play 1:'%c' \t Play2:'%c' \n", moves[0], moves[1]);
        
        // Compare game for result
        game_result_value = game_val(moves[0], moves[1]);

        // Calculate our rps score
        // (rock - 1, paper - 2, scissors -3)
        move_value = play_val(moves[1]);

        // sum results and store in list
        games = realloc(games, ((size_t)count + 1) * sizeof(games[0]));
        int game_sum = game_result_value + move_value;
        *(games + count) = game_sum;
        
        count++;
    }

    // total from list
    for (int i = 0; i < count; i++)
    {
       sum = sum + *(games + i);
    }
    
    // print total
    printf("Total sum: %i\n", sum);;;;;

    // Free memory
    free(games);
    free(moves);
    free(line);
    return 0;
}

void plays(char line[], char output[], size_t line_length, size_t output_length)
{
    // Variables
    int count = 0, play = 0;        // Counter for line & play for play output
    while (count < (int)line_length)
    {
        // If current character is a space then skip character
        if (isspace(line[count]))
        {
            // if newline character, end function
            if (line[count] == '\n')
            {
                return;
            }
            // If space character, skip character
            count++;
            continue;
        }
        // if character is ascii character, then add to output array
        if (isascii(line[count]))
        {
            if (play < (int)output_length)
            {
                output[play] = line[count];
                play++;
            }
        }
        // Increment character in line.
        count++;
    }
}

int play_val(char play)
{
    // Variables
    int value = 0;

    switch (play)
    {
        case 'X':   // Rock
            value = 1; 
            break;

        case 'Y':   // Paper
            value = 2;
            break;

        case 'Z':   // Scissors
            value = 3;
            break;
        
        default:
            value = -1;
            break;
    }

    // return calculated score
    return value;
}

int game_val(char player1, char player2)
{
    // Variables
    int win = 6, tie = 3, loss = 0;

    // Game Loss
    if (player1 == 'A' && player2 == 'Z') return loss;
    if (player1 == 'B' && player2 == 'X') return loss;
    if (player1 == 'C' && player2 == 'Y') return loss;

    // Game tie
    if (player1 == 'A' && player2 == 'X') return tie;
    if (player1 == 'B' && player2 == 'Y') return tie;
    if (player1 == 'C' && player2 == 'Z') return tie;

    // Game win
    if (player1 == 'A' && player2 == 'Y') return win;
    if (player1 == 'B' && player2 == 'Z') return win;
    if (player1 == 'C' && player2 == 'X') return win;

    // If no matches are found print error and return -1
    printf("WARNING Game not graded: P1(%c) -- P2(%c)\n", player1, player2);
    return -1;
}