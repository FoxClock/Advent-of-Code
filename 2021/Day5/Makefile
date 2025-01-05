CC=CC
Day=5
challenge1=Day\$(Day)
challenge2=Day$(Day)-2

all: AOC-challenge2

AOC-challenge1:
	$(CC) -o AOC$(Day) $(challenge1).c

AOC-challenge2:
	$(CC) -o AOC$(Day)-2 $(challenge2).c

clean:
	rm -r *.dSYM
	rm AOC$(Day)
	rm AOC$(Day)-2
	rm *.o