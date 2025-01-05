/*
    Author:     Hayden Foxwell
    Date:       08/12/22
    Purpose:
        Contains common functions for the Advent of code challenges.
*/

// Includes
#include "common.h"

// Defines

/* Functions */

///
/// Opens a file and returns a file pointer
FILE* open_file(char* filepath, char* mode) {
    FILE *file;

    // Check that filepath is not empty
    if (!filepath) {
        printf("Error, No input file Specified.\n");
    }

    // Open file from filepath
    file = fopen(filepath, mode);

    if (!file) {
        printf("Error, could not open File: %s \n", filepath);
        exit(1);
    }

    return file;
}

/*
    Takes in a file pointer, then returns a string of all the items

    Parameters:
        FILE *input_file: file pointer to the input file.

    Returns:
        char *file_contents: heap array to containing the contents of the file.
*/
char  *get_string_contents(FILE *input_file) {
    // Find size of file
    fseek(input_file, 0L, SEEK_END);
    int sz = ftell(input_file);
    rewind(input_file);

    // allocate string buffer of size
    char *file_contents = malloc(sz * sizeof(char));

    // Read file into array
    fread(file_contents, sz, 1, input_file);

    return file_contents;
}

/* Reallocate an array to a particular size */

/*
    Reallocates the size of an array
    inputs:
        int **starting_array: double pointer to the starting array, allows for in-place change 
        so original passed address is reassigned

        size_t inital_size: Inital size of the array

        size_t amount: the amount to resize by, this needs to be specified in terms of the data 
            to resize with, ie; size_of(int)

    returns:
    size_t new size of array
*/
size_t reallocate_array(int **starting_array, size_t inital_size, size_t amount) {
    
    // Calculate size to make array
    size_t new_size = inital_size + amount;

    // Reallocate the array to the new size
    *starting_array = (int*) realloc(*starting_array, new_size);

    printf("new size = %zu\n", sizeof(starting_array));
    return new_size;
}


// Print the contents of an array
void printVals(int array[], size_t length)
{
    for (size_t j = 0; j < length; ++j)
    {
        printf("Item %zu:\t%i\n", j, array[j]);
    }
}

// Bubble sort values
// Sorts the integer values in an array
void bubbleSort(int array[], int size) {
  // loop to access each array element
  for (int step = 0; step < size - 1; ++step) {
      
    // loop to compare array elements
    for (int i = 0; i < size - step - 1; ++i) {
      
      // compare two adjacent elements
      // change > to < to sort in descending order
      if (array[i] < array[i + 1]) {
        
        // swapping occurs if elements
        // are not in the intended order
        int temp = array[i];
        array[i] = array[i + 1];
        array[i + 1] = temp;
      }
    }
  }
}

/*
    Returns an char *array up to a separator or to a null terminator.

    Inputs:
        char *input_array:  Input array to be split
        char * ouput:       output the 
        size_t length:      Length of the input array
        char sep:           character to separate from
*/

int split_string(char *input_array, char *out, size_t leng, char sep)
{
    // Variables
    size_t arr_size = 0;
    int count = 0;

    // Make copy of the input array
    char input_copy[leng];
    strcpy(input_copy, input_array);

    //iterate through input array
    while (count < leng)
    {
        if (input_copy[count] == '\0'               // If null terminator
        || input_copy[count] == sep                 // If separator value
        || input_copy[count] == '\n')               // If newline character
        {
            // Get size of inital array
            arr_size = (size_t)count;

            // Insert null character at separator position
            input_copy[count] = '\0';

            // Stop the loop
            break;
        }
        // Increment count
        count++;
    }

    // Copy the text into the output array
    // Verify that the string copied successfully
    int n = strlcpy(out, input_copy, leng);
    if (n < (int)arr_size)
    {
        printf("Error copying string!\n");
        exit(1);
    }

    // Return the length of the output array
    return (int)arr_size;
}



/* =================================================== */
/* ------------------- Linked List ------------------- */
/* --- Functions for handling linked list elements --- */


/* Initialises a list object */
void init_list(struct linked_list new_list)
{
    new_list.start = NULL;
}

/* Push an item to the top of the list */
void push(struct linked_list *list, int data)
{
    // Check if list is specified
    if (!list)
    {
        printf("No parent list specified for node\n");
        return;
    }

    // Create new node and allocate memory on heap
    struct node *n;
    n = malloc(sizeof(struct node));
    
    /* Set values */
    n->data = data;             // Allocate data into data variable
    n->next = list->start;      // set next pointer to the start pointer position
    list->start = n;            // Set the list struct start pos to the current node

    // finish function and return
    return;
}

/* Remove an item from within the list */
void delete(struct linked_list *list, size_t index)
{
    // Variables
    int count = 0;
    size_t list_leng = (size_t)count_list(list);
    struct node *note_to_delete;
    struct node *next_item;

    // Determine if index is inside of list
    if (!(index > 0 && index < list_leng))
    {
        printf("CANNOT DELETE!\n Item is outside of list range!\n");
        printf("Index: %zu -- List length: %zu\n\n", index, list_leng);

        return;
    }

    // Get the node at the index
    note_to_delete = list->start;
    while (note_to_delete != NULL && count <= index)
    {
        note_to_delete = note_to_delete->next;
        count++;
    }

    // Take current node's next
    // TODO: Take current item and remove it
    //      then take the previous item in the list
    //      and change the next value to the deleted item's
    //      next value. 

    return;
}

int count_list(struct linked_list *list)
{
    // Variables
    int count = 0;

    // Get head of list
    struct node *current = list->start;

    // While the currently examined item is not null, increment count
    // and assign the next value to the current pointer
    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    return count;
}

/* Remove an item from the list */
void pop(struct linked_list *list)
{
    // Variables
    /* Take the head of the list's node*/
    struct node *node_to_remove = list->start;
    /* Take the had of the list's next item*/
    struct node *node_to_relink = list->start->next;


    // Assign the node to relink to the list start
    list->start = node_to_relink;

    // Free the node to remove
    free(node_to_remove);

    // Close function
    return;
}

/* Delete all the items in the list */
int free_list(struct linked_list *list)
{
    // Variables

    // whenever the head of the list is not null
    // iterate through the list and free the nodes.
    while (list->start != NULL)
    {
        struct node *n = list->start;
        list->start = list->start->next;
        free(n);
    }

    // Free the head of the list
    free(list);

    // Report success
    return 1;
}

/* =================================================== */