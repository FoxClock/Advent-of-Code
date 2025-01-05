#!/bin/sh

makefile="Makefile"
date=`date +"%d-%m-%Y"`

# Sets up a day for AOC
# Steps
# - Prompts user for the day they want to create -> $(Day)
# - Creates folder for that day
# - CD into folder
# - Create first and second C file 
# -- called $(Day).c and $(Day)-2.c
# - Create makefile
# - Create input.txt & testInput.txt

# Reads the Day number
echo "enter Day number to setup:\t"
read Day

echo "enter session cookie"
read session

# Create list of days
declare -a listofdays=("Day$Day.c" "Day$Day-2.c")

# makes the directory
mkdir -p 'Day'$Day

# Move to folder
cd 'Day'$Day

# Create c files
for i in "${listofdays[@]}"
do
    touch "$i"

    # Put comments, common imports, and common #defines 
    # at the top of the C files

echo '
// AUTHOR:	Hayden Foxwell
// DATE:	16-12-2022
// PURPOSE:	Day 3 -
// Imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Common/common.h"


// Defines
#if (1)
    #define INPUT_FILE "testInput.txt"
#else
    #define INPUT_FILE "input.txt"
#endif

/* Main function */
int main()
{
    // Code goes here:
}
' >> "$i"
done

# Get puzzle input
touch 'input.txt'
curl --cookie "session=$session"  "https://adventofcode.com/2022/day/"$Day"/input" >> input.txt


# Setup makefile
touch $makefile

echo "CC=cc" >> $makefile
echo "Day=$Day" >> $makefile
echo 'challenge1=Day$(Day)
challenge2=Day$(Day)-2
commonPath=../Common
common=common
flags=-Wextra

all: AOC-challenge2
	$(CC) -o AOC$(Day) *.o
	chmod +x AOC$(Day)

AOC-challenge1: $(challenge1).c common
	$(CC) -c $(challenge1).c $(flags)

AOC-challenge2: $(challenge1)-2.c common
	$(CC) -c $(challenge2).c $(flags)

common: $(commonPath)/$(common).c $(commonPath)/$(common).h
	$(CC) -c $(commonPath)/$(common).c

clean:
	rm *.o
	rm AOC$(Day)

run:
	./AOC$(Day)' >> $makefile

# Create text files
touch testInput.txt