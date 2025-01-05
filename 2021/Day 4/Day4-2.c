#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// PURPOSE: To find the winning board in a series of boards and
//          moves in a American bingo game. 
// AUTHOR:  Hayden Foxwell
// DATE:    24/12/21

// Defines
#define GRIDSIZE 5
#define BUFFER 1024

// Structs
struct board                                                        // Stores information on boards
{
    int8_t board[GRIDSIZE][GRIDSIZE];                               // The board with numbers
    int8_t daubedNumbers[GRIDSIZE][GRIDSIZE];                       // determines if a number is daubed
    int board_won;                                                  // index to indicate if a board has won
}board;

// Global variables
int number_of_boards = 0;                                           // Number of boards stored                  
int number_of_moves = 0;                                            // Number of moves stored

// Function declarations
char* readline();                                                   // Reads user input from stdin
FILE* openFile(char* filename);                                     // Opens a file and returns file pointer
int readMoves(FILE file, int* moves);                               // Reads a number from the file
void get_moves(FILE *filePointer, int *movesArray);                 // gets the moves from a file
int charToInt(char input);                                          // Converts a char to an integer
void get_boards(FILE *fptr, struct board *boardArray, int length);  // Reads boards from file
int get_winning_board(int moves, struct board filledBoards[]);      // Determines a winning board finding row, column or diagnonal
int calculate_board_sum(int boardIndex, int daubedValue, struct board boards[]);

// Diagnostic functions
void print_moves(int movesLength, int moves[]);
void print_boards(int boardsLength, struct board boards[]);
void print_winning_board(int winner, int boardLength, struct board boards[]);





// Main Function
int main()
{
    // Variables
    int moves[BUFFER];                      // Int array for moves
    struct board boards[BUFFER/2];          // array of board structs

    // get user input for file name
    printf("Please enter file name: \n");
    char *filename = "testinput.txt";

    // open file
    FILE* fptr = openFile(filename);

    // Get file contents
    // - Get csv move input
    readMoves(*fptr, moves);
    fclose(fptr);

    // Reopen file for read
    fptr = openFile(filename);

    // - Get boards
    get_boards(fptr, boards, BUFFER);
    fclose(fptr);

    // Determine the wining board
    int winner = -1, move = 0, boardPos = 0;
    
    while (move < number_of_moves)
    {   
        winner = get_winning_board(moves[move], boards);
        if (winner != -1)
        {
            if (boards[winner].board_won == 0)
            {
                boards[winner].board_won = move;
            }
        }
        winner = -1;
        move++;
    }

    // sum the value of all remaining numbers
    int sum = calculate_board_sum(winner, 0, boards);

    // Print the winning values + diagnositcs
    printf("The sum is: %d. The move is: %d. The total is: %d\n", sum, moves[move-1], sum * moves[move-1]);

    return 0;
}

// #######################
// Auxilary functions
// =======================
// In order of execution
// #######################

// ######################
// Geting file name and opening file
// ######################

// Get user input from stdin
char* readline()
{
    // Define string buffer
    char *line = malloc(BUFFER);
    // Read from stdin
    fgets(line, BUFFER, stdin);
    // Remove trailing '/n'
    line[strlen(line) - 1] = '\0';

    // Return string
    return line;
} 

// open file handle
FILE* openFile(char* filename)
{   
    // Open file at file name (relative to the exe)
    FILE *fptr = fopen(filename, "r");

    // Check if pointer is valid
    if (!fptr)
    {
        printf("Error: Cannot open file!\n");
        exit(1);
    }
    return fptr;
}

// ######################
// Reads moves from start of file
// Puts them in an array
// ######################

// Read from file
// Modifies a passed array to contain the moves
int readMoves(FILE file, int moves[])
{
    // constants
    const char delimiter = ',', endOfMoves = '\n';      // Constants for delimiter and end of moves
    
    // Variables
    char integers[10] = {0};                            // temporary array to store numbers from moves
    int counter = 0, moveCounter = 0, endFlag = 0;      // Counters for array positions, flag to end while loop
    char character;                                     // variable for char which is read from file

    // Loop through file until newline is found.
    while (endFlag != 1)
    {
        // Loop through number until delimter is found
        while ((character = getc(&file)) != delimiter)
        {
            // if end of file is found. set flag
            if (character == endOfMoves)
            {
                endFlag = 1;
                break;
            }
            // add number to integer array
            else
            {
                integers[counter] = character;
                counter++;
            }
        }
        counter = 0;
        moves[moveCounter] = atoi(integers);            // Assign move to moves array
        memset(integers, 0, 10);                        // Reset array to prevent false values
        moveCounter++;                                  // Increment move counter
    }
    // Sets end of moves flag
    moves[moveCounter] = -1;

    // set global variable
    number_of_moves = moveCounter;

    // Return success state
    return 1;
}

// Convert from char to int
int charToInt(char input)
{
    // By subtracting 0 references to integer value
    int value = (int)input - '0';
    return value;
}

// ######################
// For each board in the file
// put board into board structure
// ######################

// Read a board from the file
// Loads it into the board aray
void get_boards(FILE *fptr, struct board boardArray[], int length)
{
    // Constants
    const int board_x = GRIDSIZE, board_y = GRIDSIZE;
    const char endOfLine = '\n', delimiter = ' ';
    const int lineChars = GRIDSIZE;

    // Variables
    int xcount = 0, ycount = 0;
    char integer[BUFFER];
    char c;
    
    // Reads moves line so it may be discarded
    // Set all values to 0
    fgets(integer, BUFFER, fptr);
    fgets(integer, BUFFER, fptr);
    memset(integer, 0, BUFFER);

    // Read line, skip the line with only \n
    // read each line and discard spaces 
    // insert line into board row

    while (fgets(integer, BUFFER, fptr))
    {
        // if first element is newline get new line
        if (integer[0] == endOfLine)
        {
            ycount = 0;
            number_of_boards++;
            continue;
        }

        int counter = 0, intcount = 0;
        char nums[lineChars];
        memset(nums, 0, lineChars);

        while (intcount < 14)
        {
            while (!isspace(integer[intcount]))
            {
                nums[counter] = integer[intcount];
                counter++;
                intcount++;
            }
            // add end to nums for ATOI() function
            // Read value into board array position
            nums[counter] = '\0';
            if (nums[0] != '\0')
            {
                boardArray[number_of_boards].board[ycount][xcount] = atoi(nums);
                xcount++;
            }
            // Reset nums to all 0s
            memset(nums, 0, lineChars);

            // Reset counter and increment other values
            counter = 0;
            intcount++;
        }
        xcount = 0;
        ycount++;
    }
}

// Determines the winning board
// Modifies the daubed value of the boards in place
// returns the index of the winning board. 
int get_winning_board(int moves, struct board filledBoards[])
{
    for (int j = 0; j < number_of_boards; j++)
    {
        // Checks each element in a board
        for (int x = 0; x < GRIDSIZE; x++)
        {
            for (int y = 0; y < GRIDSIZE; y++)
            {
                if (moves == filledBoards[j].board[x][y])
                {
                    filledBoards[j].daubedNumbers[x][y] = 1;
                }
            }
        }

        // after each board is completed check if win state
        // Checks for wins in the x direction
        int wincounter = 0;
        for (int x = 0; x < GRIDSIZE; x++)
        {
            wincounter = 0;
            for (int y = 0; y < GRIDSIZE; y++)
            {
                if (filledBoards[j].daubedNumbers[x][y] == 1)
                {
                    wincounter++;
                }
            }
            if (wincounter == GRIDSIZE)
            {
                return j;
            }
        }

        // after each board is completed check if win state
        // checks for wins in the y direction
        for (int x = 0; x < GRIDSIZE; x++)
        {
            wincounter = 0;
            for (int y = 0; y < GRIDSIZE; y++)
            {
                if (filledBoards[j].daubedNumbers[y][x] == 1)
                {
                    wincounter++;
                }
            }
            if (wincounter == GRIDSIZE)
            {
                return j;
            }
        }

        // Checks for wins in the diagonal
        for (int x = GRIDSIZE - 1; x >= 0; x--)
        {
            wincounter = 0;
            for (int y = 0; y < GRIDSIZE; y++)
            {
                if (filledBoards[j].daubedNumbers[y][x] == 1)
                {
                    wincounter++;
                }
            }
            if (wincounter == GRIDSIZE)
            {
                return j;
            }
        }

        // Checks for wins in the diagonal
        for (int y = GRIDSIZE - 1; y >= 0; y--)
        {
            wincounter = 0;
            for (int x = 0; x < GRIDSIZE; x++)
            {
                if (filledBoards[j].daubedNumbers[y][x] == 1)
                {
                    wincounter++;
                }
            }
            if (wincounter == GRIDSIZE)
            {
                return j;
            }
        }

    }
    return -1;
}

// Calculate the sum of all values in the board
// the numbers calcualted are indicated by the chose daubed value
// either 1/0
int calculate_board_sum(int boardIndex, int daubedValue, struct board boards[])
{
    int sum = 0;
    // For each position in a baord, total the value at a chosen daubed value
    for (int x = 0; x < GRIDSIZE; x++)
    {
        for (int y = 0; y < GRIDSIZE; y++)
        {
            if (boards[boardIndex].daubedNumbers[y][x] == daubedValue)
            {
                sum += boards[boardIndex].board[y][x];
            }
        }
    }

    // Return sum value
    return sum;
}

// ==========================
// Diagnostics: diagnostic functions
// ==========================
void print_moves(int movesLength, int moves[]){
    // +++++++++++++++++++++++++++
    // DIAGNOSTIC: Print Moves
    // +++++++++++++++++++++++++++
    int count = 0;
    while (moves[count] != -1)
    {
        printf("Move:\t%d\n", moves[count]);
        count++;
    }
    printf("Length of moves:\t%d\n",number_of_boards);
    // +++++++++++++++++++++++++++
}

void print_boards(int boardsLength, struct board boards[])
{
    // +++++++++++++++++++++++++++++=
    // DIAGNOSITC: Prints the boards from the stucts
    // +++++++++++++++++++++++++++++=
    for (int z = 0; z < number_of_boards; z++)
    {
        printf("Board: %d\n", z);
        for (int y =0; y < GRIDSIZE; y++)
        {
            for (int x = 0; x < GRIDSIZE; x++)
            {
                printf("%d ", boards[z].board[y][x]);
            }
            printf("\n");
        }
    }
    printf("Number of boards: %d\n", number_of_boards);
    // ++++++++++++++++++++++++++++++=
}

void print_winning_board(int winner, int boardLength, struct board boards[])
{
    // +++++++++++++++++++++++++++++++=
    // DIAGNOSTIC: Print out winning board
    // +++++++++++++++++++++++++++++++=    
    printf("Winning board: %d\n", winner);
    for (int y =0; y < GRIDSIZE; y++)
    {
        printf("|");
        for (int x = 0; x < GRIDSIZE; x++)
        {
            if (boards[winner].daubedNumbers[y][x] == 0)
            {
                printf("%d ", boards[winner].board[y][x]);
            }
            else
            {
                printf(" ");
            }
        }
        printf("|\n");
    }
    // +++++++++++++++++++++++++++++++=
}