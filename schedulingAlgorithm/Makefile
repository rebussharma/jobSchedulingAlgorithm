all: main

main: main.o process.o
	g++ main.o process.o -o main

main.o: main.cpp
	g++ -c main.cpp

process.o: process.cpp processes.h
	g++ -c process.cpp

clean:      
	 rm *.o main


