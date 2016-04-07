CC = gcc
CFLAGS = -Wall
OBJECTS = main.o aux.o

rmdup: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o rmdup
	
aux.o: aux.h aux.c
	$(CC) -c aux.c

main.o: aux.h main.c
	$(CC) -c main.c