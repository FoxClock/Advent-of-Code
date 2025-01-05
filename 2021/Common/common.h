#pragma once

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <GLUT/glut.h>

// Define macro constants
#define LARGE_BUFFER (1024 * 8)
#define LINE_BUFFER 128
#define FILE_NAME_LEN 16

/* ================ */
// Constants

// Variables
//char *line = NULL;

/* ================ */
/* ================ */
// Structures

/// Single text token
typedef struct token {
    char token[LINE_BUFFER];
    struct token *next;
} token;

/// List of text tokens
typedef struct tokenList {
    struct token *start;
} tokenList;

struct Vector1D {
    int *data;
    size_t len;
};

typedef struct CharVector2D {
    char **data;
    size_t len;
} CharVector2D;

/* ================ */

/* Define Functions for common use */

// Opens file for reading
FILE* openFile(char filename[]);

// Converts a char to an int
int charToInt(char input);

// Sums a 1D array, returns the sum
int calculateArraySum(int x_size, int array[x_size]);

// Sums a 2D array, returns the sum
int calculate2DArraySum(int x_size, int y_size, int array[x_size][y_size]);

// Get value from csv file
const char* get_field(char* line, size_t num);

// Get int array from csv file.
struct Vector1D* CSVToInt(FILE *file_pointer);

// Create character array from file
struct CharVector2D *CSVToCharVect( FILE *input_file, char delimiter);

/***************************/
// Drawing functions
/***************************/
typedef void (*DrawFunc)();
typedef void (*KeyboardFunc)(unsigned char key, int x, int y);

void initializeGLUT(int argc, char **argv, DrawFunc draw, KeyboardFunc keyboard);

/**************************/
// Linked list functions  */
/**************************/

// Initialise list
void initList(struct tokenList *lists);

// push item onto the list
void push(struct tokenList *lists, char data[LINE_BUFFER]);

// print items from the list
void printList(struct tokenList *lists);

// Count all items in list
int countList(struct tokenList *lists);

// Mem free entire list;
void freeList(struct tokenList *lists);

// Bubble sort
void bubbleSort(int array[], int size);

// Find maximum index
int max_index(size_t arrayLen, int array[arrayLen]);

// find minimum index
int min_index(size_t arrayLen, int array[arrayLen]);
