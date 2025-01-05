CC=CC
Day=8
challenge1=Day$(Day)
challenge2=Day$(Day)
commonPath=../Common
common=common.c

all: AOC-challenge1

AOC-challenge1:
	$(CC) -o AOC$(Day) $(challenge1).c $(commonPath)/$(common)

AOC-challenge2:
	$(CC) -o AOC$(Day) $(challenge2).c $(commonPath)/$(common)

clean:
	rm *.o
