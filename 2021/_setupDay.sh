#!/bin/sh

makefile="Makefile"
date=$(date +"%d-%m-%Y")

# Sets up a day for AOC
# Steps
# - Prompts user for the day they want to create -> $(Day)
# - Creates folder for that day
# - CD into folder
# - Create first and second C file 
# -- called $(Day).c and $(Day)-2.c
# - Create makefile
# - Create input.txt & testInput.txt

# Read the Day number
printf "Enter Day number to set up:\t"
read Day

# Validate input
if ! [[ "$Day" =~ ^[0-9]+$ ]]; then
    echo "Error: Day number must be a positive integer."
    exit 1
fi

# Make the directory
directory="Day$Day"
mkdir -p "$directory" || { echo "Error: Failed to create directory."; exit 1; }

# Move to folder
cd "$directory" || { echo "Error: Failed to change directory."; exit 1; }

# Create C files with comments
for file in "${directory}.c" "${directory}-2.c"; do
    touch "$file" || { echo "Error: Failed to create $file."; exit 1; }
    printf "// AUTHOR:\tHayden Foxwell\n" >> "$file"
    printf "// DATE:\t%s\n" "$date" >> "$file"
    printf "// PURPOSE:\tDay %s -\n" "$Day" >> "$file"
done

# Setup Makefile
cat <<EOF > "$makefile" || { echo "Error: Failed to create $makefile."; exit 1; }
CC=gcc
Day=$Day
challenge1=Day$Day
challenge2=Day${Day}-2

commonPath=../Common
common=common.c

all: AOC-challenge1

AOC-challenge1:
	\$(CC) -o AOC\$(Day) \$(challenge1).c \$(commonPath)/\$(common)

AOC-challenge2:
	\$(CC) -o AOC\$(Day) \$(challenge2).c \$(commonPath)/\$(common)

clean:
	rm -f *.o
EOF

# Create text files
touch input.txt testInput.txt || { echo "Error: Failed to create text files."; exit 1; }

echo "Setup completed successfully."
