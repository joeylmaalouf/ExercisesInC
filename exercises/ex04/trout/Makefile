trout.o: trout.c trout.h
	gcc -Wall -c trout.c -o trout.o
util.o:  util.c trout.h
	gcc -Wall -c util.c -o util.o
trout: main.c trout.o util.o
	gcc -Wall main.c trout.o util.o -o trout
