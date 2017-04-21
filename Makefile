SHELL = /bin/sh
FLAGS = -g
CC = g++

all:    2p2c 1p  2p3c dynpipe

2p2c:     TwoPipesTwoChildren.cpp
	$(CC) $(FLAGS) -o $@ TwoPipesTwoChildren.cpp

2p3c:     TwoPipesThreeChildren.cpp
	$(CC) $(FLAGS) -o $@ TwoPipesTwoChildren.cpp

1p:     onepipe.cpp
	$(CC) $(FLAGS) -o $@ onepipe.cpp

dynpipe: DynPipe.cpp
	$(CC) $(FLAGS) -o $@ DynPipe.cpp
clean:
	rm 2p2c 1p 2p3c dynpipe
