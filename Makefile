
## David Zausner 


CC=g++
C++FLAGS=-g -Wall -pedantic -std=c++11
INCLUDES=-I.
PROG_NAME=findPaths
ALL_OBJ = main.o dijkstra.o

%.o : %.cpp
	g++  -c $< -o $@ $(C++FLAGS)

$(PROG_NAME): $(ALL_OBJ)
	$(CC) $(C++FLAG) -o $@ $(ALL_OBJ) $(INCLUDES)

all:
	make $(PROG_NAME)

clean:
	rm -f $(PROG_NAME)
	rm -rf *o main.o
