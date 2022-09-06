#
# Makefile for P2
# COSC 051
# Spring 2019
#

a.out: main.o
	g++ -std=c++11 main.o

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

.PHONY: submit clean

submit:
	rm -f submit.zip
	zip submit.zip main.cpp Makefile

clean:
	rm -f *.o core a.out
