// Author:		Hayden Foxwell
// Date:		06/01/2022
/* Purpose:		To simulate the growth of lantern fish
   				in a sea environment.
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Defines
#define ARRAY_SIZE 1024

// Structs
struct fish {
	   int age;
	   struct fish* next;
}fish;

struct fishList {
	   struct fish *start;
}fishList;

// Global variables 

// Functions
void initList(struct fishList *lists);
void push(struct fishList *lists, int data);
void printList(struct fishList *lists);
void incrementList(struct fishList *lists, int simLength);
int countList(struct fishList *lists);
void freeList(struct fishList *lists);

/*******************/
// Main Functio	   */
/*******************/
int main(int argc, char *argv[])
{
  // Constants
  const char *fileName = "input.txt";
  const int simulationDays = 80;

  // Variables
  int ages = 0;
  int intAges[ARRAY_SIZE] = {0};  
  char ageList[ARRAY_SIZE] = {0};
  FILE *fptr = fopen(fileName, "r");
  if (!fptr) {
  	 printf("File cannot be opened: %s", fileName);
	 getchar();
	 return 1;
  }

  // Read the fish ages from the file
  // Each is a CSV value between 8-0
  fgets(ageList, ARRAY_SIZE, fptr);
  
  // Print file contents.
  printf("File Contents:\t%s\n", ageList);

  // Determine number of ages in file.
  int count = 0;
  while (ageList[count] != '\0') {
  		if (isdigit(ageList[count])){
		   intAges[ages] = ageList[count] - '0'; 
		   ages +=1;
		}	
		count +=1;
  }
  
  // Print number of ages
  printf("Number of ages:\t%d\n",ages);

  printf("Press Key to start simulation for: %d Days.\n", simulationDays);
  getchar();

  // Create fish linked list
  // initalise list
  initList(&fishList);
  
  for (int x = 0; x < ages; ++x) {
  	  push(&fishList, intAges[x]);
  }
  
  // Print ages
  //printf("Print linked list\n");
  //printList(&fishList);
  

  // Iterate through the list, decrementing the values
  // IF a value reaches zero, add a new fish to the list
  // repeat for NumOfDays
  /* when a fish reaches 0, it should be reset to 6.
  	 A new fish is added with the age value of 8. 
  */
  incrementList(&fishList, simulationDays);
  
  // Print new fish list
  printList(&fishList);
  printf("\n");  

  printf("Number of fish:\t%d\n",countList(&fishList));

  // Free system memory
  freeList(&fishList);

  system("PAUSE");	
  return 0;
}

/**********************/
// Auxilary functions //
/**********************/

// initalise list start to null.
void initList(struct fishList *lists) {
	 lists->start = NULL;
}

// Push item onto the list
void push(struct fishList *lists, int data) {
	 struct fish *p;
	 p = malloc(sizeof(struct fish));
	 p->age = data;
	 p->next = lists->start;
	 lists->start = p;
}

// print items from the list
void printList(struct fishList *lists) {
	 struct fish *p = lists->start;
	 while (p != NULL) {
	 	   printf("%d ", p->age);
		   p = p->next;
	}
}

void incrementList(struct fishList *lists, int simLength) {
	 struct fish *index = lists->start;
	 for (int i = 0; i < simLength; ++i) {
	 int counter = 0;
  	    while (index != NULL) {
			  if (index->age == 0) {
			  	 counter += 1;
				 index->age = 6;
			  } else {
			  	index-> age -= 1;
			  }
			  index = index->next;
		}
		for (int x = 0; x < counter; ++x) {
			push(&fishList, 8);
		}
		index = lists->start;
	}
}

int countList(struct fishList *lists) {
	 // Variables
	 int count = 0;
	 struct fish *index = lists->start;
	 while (index != NULL) {
	 	   count +=1;
		   index = index->next;
	}
	return count;
}

void freeList(struct fishList *lists) {
	 while (lists->start != NULL) {
	 	   struct fish *p = lists->start;
		   lists->start = lists->start->next;
		   free(p);
	}
}
