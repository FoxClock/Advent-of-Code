/* Header file containing all functions in the common library */

// Includes
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Defines

// Structs
/* Linked list structure */

// Struct to represent a node
struct node
{
    int data;
    struct node *next;
} node;

// Struct to represent a list
struct linked_list
{
    struct node *start;
} linked_list;

/* ========================== */

// Function Definitions
FILE* open_file(char* filepath, char* mode);
char  *get_string_contents(FILE *input_file);
size_t reallocate_array(int **starting_array, size_t inital_size, size_t amount);
void printVals(int array[], size_t length);
void bubbleSort(int array[], int size);
int split_string(char *input_array, char *out, size_t leng, char sep);

/* Linked list functions */
void init_list(struct linked_list new_list);
void push(struct linked_list *list, int data);
void delete(struct linked_list *list, size_t index);
int count_list(struct linked_list *list);
void pop(struct linked_list *list);
int free_list(struct linked_list *list);
/* ================================================== */