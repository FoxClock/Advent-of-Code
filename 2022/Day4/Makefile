CC=cc
Day=4
challenge1=Day$(Day)
challenge2=Day$(Day)-2
commonPath=../Common
common=common
flags=-Wextra

all: AOC-challenge1
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
	./AOC$(Day)
