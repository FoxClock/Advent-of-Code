CC=CC
Day=7
challenge1=Day$(Day)
challenge2=Day$(Day)-2
commonPath=../Common
common=common.c
all: AOC-challenge1

AOC-challenge1:
	$(CC) -o AOC$(Day) $(challenge1).c $(commonPath)/$(common)

AOC-challenge2:
	$(CC) -o AOC$(Day) $(challenge2).c $(commonPath)/$(common)

clean:
	rm *.o
