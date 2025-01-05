#define _CRT_SECURE_NO_WARNINGS
// Author:		Hayden Foxwell
// Date:		06/01/2022
/* Purpose:		To simulate the growth of lantern fish
				in a sea environment.
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <ctype.h>

// Defines
#define ARRAY_SIZE 1024
#define FISH_AGE_RANGE 9


// Structs
struct fish {
	char age;
	struct fish* next;
}fish;

// Global variables 
long long fishNumbers[FISH_AGE_RANGE] = { 0 };
long long fishNumbers_back[FISH_AGE_RANGE] = { 0 };

// Functions

/*******************/
// Main Functio	   */
/*******************/
int main(int argc, char* argv[])
{
	// Constants
	const char* fileName = "input.txt";
	const int simulationDays = 256;

	// Variables
	int ages = 0;
	int intAges[ARRAY_SIZE] = { 0 };
	char ageList[ARRAY_SIZE] = { 0 };
	FILE* fptr = fopen(fileName, "r");
	if (!fptr) {
		printf("File cannot be opened: %s", fileName);
		getchar();
		return 1;
	}

	// Read the fish ages from the file
	// Each is a CSV value between 8-0
	fgets(ageList, ARRAY_SIZE, fptr);

	// Print file contents.3
	printf("File Contents:\t%s\n", ageList);

	// Determine number of ages in file.
	int count = 0;
	while (ageList[count] != '\0') {
		if (isdigit(ageList[count])) {
			intAges[ages] = ageList[count] - '0';
			ages += 1;
		}
		count += 1;
	}

	printf("Number of fish:\t%d\n", ages);

	printf("To continue simulation Press any key...\n");
	getchar();

	// Iterate through file, count each value
	// Populate day
	for (int x = 0; x < ages; ++x) {
		fishNumbers[intAges[x]] += 1;
	}


	for (int x = 0; x < simulationDays; x++) {

		fishNumbers_back[8] = fishNumbers[0];
		fishNumbers_back[0] = fishNumbers[1];
		fishNumbers_back[1] = fishNumbers[2];
		fishNumbers_back[2] = fishNumbers[3];
		fishNumbers_back[3] = fishNumbers[4];
		fishNumbers_back[4] = fishNumbers[5];
		fishNumbers_back[5] = fishNumbers[6];
		fishNumbers_back[6] = fishNumbers[7];
		fishNumbers_back[6] += fishNumbers[0];
		fishNumbers_back[7] = fishNumbers[8];

		memset(fishNumbers, 0, sizeof(fishNumbers));
		memcpy(fishNumbers, fishNumbers_back, sizeof(fishNumbers));
		memset(fishNumbers_back, 0, sizeof(fishNumbers_back));
	}

	long long sum = 0;
	for (int count = 0; count < FISH_AGE_RANGE; ++count) {
		sum += fishNumbers[count];
	}
	printf("Answer: %lld\n", sum);

	system("PAUSE");
	return 0;
}

/**********************/
// Auxilary functions //
/**********************/