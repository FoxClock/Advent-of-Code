/* File information */
// Author;      Hayden Foxwell
// Date:        04/01/2022
/* Purpose: -  Provide some common functions which are commonly used in the
                Advent of code
*/
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "common.h"
// Defines

// Global Variables


// Opens file and validates that its open
FILE* openFile(char filename[])
{
    FILE *file_pointer = fopen(filename, "r");

    if (!file_pointer)
    {
        perror("Cannot open file!");
        exit(1);
    }

    return file_pointer;
}

// Convert a character to an integer
int charToInt(char input)
{
    // Variables
    int output;
    
    output = input - '0';

    return output;
}

// Sum of 1D array
int calculateArraySum(int x_size, int array[x_size])
{
    // Variables
    int sum = 0;

    // for each element in the array calculate the sum 
    for (int x = 0; x < x_size; ++x)
    {
        sum += array[x];
    } 
    return sum;
}

// Calculate the sum of a 2d array
int calculate2DArraySum(int x_size, int y_size, int array[x_size][y_size])
{
    // Variables
    int sum = 0;

    // for each element in the array calculate the sum 
    for (int x = 0; x < x_size; ++x)
    {
        for (int y = 0; y < y_size; ++y)
        {
            sum += array[x][y];
        }
    } 
    return sum;
}

/// @brief Reads a value from a char buffer at a integer position. buffer must be comma separated
/// Returns NULL if error occurs. 
/// @param line char buffer
/// @param num  position within buffer
/// @return     String buffer containing token
const char* get_field(char* line, size_t num)
{
	const char* tok;
	for (tok = strtok(line, ",");
			tok && *tok;
			tok = strtok(NULL, ",\n"))
	{
		if (!--num)
			return tok;
	}
	return NULL;
}

/// @brief Gets the length of the line. Returns negative if error occurs
/// @param file_pointer 
/// @return length of line
int GetLenOfLine(FILE* file_pointer)
{
    // Variables
    char *tempLine;
    size_t length = 0;

    // get length
    if ((length = getline(&tempLine, &length, file_pointer) != -1)) length = -1;

    free(tempLine);
    return (int) length;
}

struct tokenList * create_token_list(FILE *input_file, char delimiter)
{
    // Variables
    char *row = NULL, *c_token, *save_ptr;
    int length = 0; 
    size_t read_length = 0;

    // Create token list
    struct tokenList *CSV_list = malloc(sizeof(tokenList));

    // setup linked list
    initList(CSV_list);

    // While file is not EOF keep reading lines
    while ((length = getline(&row, &read_length, input_file)) != -1)
    {
        c_token = strtok_r(row, &delimiter, &save_ptr);

        // Keep reading until no tokens in line. 
        while (c_token != NULL)
        {
            push(CSV_list, c_token);
            c_token = strtok_r(NULL, &delimiter, &save_ptr);
        }
    }

    return CSV_list;
}

struct Vector1D* CSVToInt(FILE *file_pointer)
{
    // Constants
    char SEPARATOR = ',';


    // Create token list from file contents
     struct tokenList *tokenList = create_token_list(file_pointer, SEPARATOR);
    
    /* Create array list structure */
    struct Vector1D *int_list = malloc(sizeof(struct Vector1D)); // Allocate memory

    // count list to determine array length
    // define output array size
    int_list->len = countList(tokenList);
    int_list->data = malloc(int_list->len * sizeof(int));
    memset(int_list->data, 0, int_list->len);

    // add each item into the array
    // done backwards due to nature of list
    struct token *index = tokenList->start;
    for (int i = int_list->len - 1; i >= 0; --i)
    {
        int_list->data[i] = atoi(index->token);
        index = index->next;
    }

    free(index);
    freeList(tokenList);
    return int_list;
}

/* Create character vector using csv reader function */
struct CharVector2D *CSVToCharVect( FILE *input_file, char delimiter)
{
    // Constants
    char SEPARATOR = ',';

    // Variables
    char *row = NULL;
    struct CharVector2D *charlist = malloc(sizeof(struct CharVector2D)); // Allocate memory
    struct tokenList *token_list = create_token_list(input_file, delimiter);    // Create token list from file
    struct token *index = token_list->start;

    /* Memory allocation checks */
    if (charlist == NULL) {perror("Allocating charlist failed"); exit(EXIT_FAILURE); }
    if (token_list == NULL) {perror("Allocating token list failed"); exit(EXIT_FAILURE); }
    if (index == NULL) {perror("Allocating index failed"); exit(EXIT_FAILURE); }

    // Assign length and allocate memory for data
    charlist->len = (size_t)countList(token_list);
    charlist->data = malloc(charlist->len * sizeof(char *));

    // Check if memory allocation for data failed
    if (charlist->data == NULL) {perror("memory allocation error");exit(EXIT_FAILURE);}

    // Allocate sub lists of data
    for (int i = 0; i < charlist->len; i++)
    {
        /* TODO: fix the magic number here. */
        charlist->data[i] = malloc(128 * sizeof(char));
        
        // Check if memory allocation of data failed
        if (charlist->data[i] == NULL) {perror("Memory allocation of sub array failed"); exit(EXIT_FAILURE);}
    }
    
    for (int i  = charlist->len  -1; i >= 0; --i)
    {
        strcpy(charlist->data[i], index->token);
        index = index->next;
    }

    freeList(token_list);
    return charlist;
}

/**************************/
/*      Draw lines        */
/**************************/
/// TODO: Implement the draw lines functions

/**************************/
//  Linked List functions */
/**************************/

// initialise list start to null.
void initList(struct tokenList *lists) {
	 lists->start = NULL;
}

// Push item onto the list
void push(struct tokenList *lists, char data[LINE_BUFFER]) {
	 struct token *p;
	 p = malloc(sizeof(struct token));
	 memcpy(p->token, data, LINE_BUFFER);
	 p->next = lists->start;
	 lists->start = p;
}

// print items from the list
void printList(struct tokenList *lists) {
	 struct token *p = lists->start;
	 while (p != NULL) {
	 	   printf("%s ", p->token);
		   p = p->next;
	}
}

int countList(struct tokenList *lists) {
	 // Variables
	 int count = 0;
	 struct token *index = lists->start;
	 while (index != NULL) {
	 	   count +=1;
		   index = index->next;
	}
	return count;
}

void freeList(struct tokenList *lists) {
	 while (lists->start != NULL) {
	 	   struct token *p = lists->start;
		   lists->start = lists->start->next;
		   free(p);
	}
}


// ++++++++++++++++++++++++
// Sorting Function
// ++++++++++++++++++++++++
void bubbleSort(int array[], int size) {
    for (int i = 0; i < size - 1; i++) {
        // Last i elements are already in place, so we only need to iterate up to size - 1 - i
        for (int j = 0; j < size - 1 - i; j++) {
            // Swap adjacent elements if they are in the wrong order
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

// ++++++++++++++++++++++++
// Maximum and minimum functions
// ++++++++++++++++++++++++

// Returns index of maximum value
int max_index(size_t arrayLen, int array[arrayLen])
{
    /* Finds the maximum value in an array of integers */
    // Variables
    int max = array[0], index = 0;

    for (int x = 1; x < arrayLen; x++)
    {
        if (max < array[x])
        {
            max = array[x];
            index = x;
        }
    }

    return index;
}

// Returns index of minimum value
int min_index(size_t arrayLen, int array[arrayLen])
{
    /* Finds the minimum value in an array of integers */
    // Variables
    int min = array[0], index = 0;

    for (int x = 1; x < arrayLen; x++)
    {
        if (min > array[x])
        {
            min = array[x];
            index = x;
        }
    }

    return index;
}

// ++++++++++++++++++++++++ 
/* Drawing functions */
// ++++++++++++++++++++++++



void initializeGLUT(int argc, char **argv, DrawFunc draw, KeyboardFunc keyboard)
{
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1024, 512);

    // Calculate center position
    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
    int windowWidth = 1024;
    int windowHeight = 512;
    int windowPosX = (screenWidth - windowWidth) / 2;
    int windowPosY = (screenHeight - windowHeight) / 2;

    // Create window
    glutInitWindowPosition(windowPosX, windowPosY);
    if (glutCreateWindow("GLUT Window") == 0) {
        fprintf(stderr, "Error: Could not create GLUT window\n");
        exit(EXIT_FAILURE);
    }

    // Initialize OpenGL
    glClearColor(0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(0, windowWidth, windowHeight, 0);

    // Set display function
    glutDisplayFunc(draw);
    glutKeyboardFunc(keyboard);
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