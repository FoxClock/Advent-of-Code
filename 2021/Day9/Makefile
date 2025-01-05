CC=gcc
Day=9
challenge1=Day9
challenge2=Day9-2

commonPath=../Common
common=common.c
commonObj=common.o

# Open GL frameworks
FRAMEWORKS=-framework OpenGL -framework GLUT -Wno-deprecated-declarations

all: AOC-challenge1

$(commonObj): $(commonPath)/$(common)
	$(CC) -c $(commonPath)/$(common) -o $(commonObj) $(FRAMEWORKS)

AOC-challenge1: $(challenge1).c $(commonObj)
	$(CC) -o AOC$(Day) $(challenge1).c $(commonPath)/$(common) $(FRAMEWORKS)

AOC-challenge2: $(challenge2).c $(commonObj)
	$(CC) -o AOC$(Day) $(challenge2).c $(commonPath)/$(common) $(FRAMEWORKS)
	
clean:
	rm -f *.o AOC$(Day) AOC$(Day)-2
