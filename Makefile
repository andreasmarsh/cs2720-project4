compile: TreeDr

TreeDr: QueType.o TreeType.o TreeDr.cpp
	g++ -Wall -g -o TreeDr QueType.o TreeType.o TreeDr.cpp

QueType.o: QueType.cpp QueType.h
	g++ -Wall -c -std=c++14 -O0 -pedantic-errors -g QueType.cpp

TreeType.o: TreeType.cpp TreeType.h
	g++ -Wall -c -std=c++14 -O0 -pedantic-errors -g TreeType.cpp

run:
	./TreeDr

clean:
	/bin/rm *.o TreeDr
