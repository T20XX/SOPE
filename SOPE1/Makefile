CC = gcc
CFLAGS = -Wall
OBJECTS = main.o aux.o simp_file.o

rmdup: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o rmdup

simp_file.o: simp_file.h simp_file.c
	$(CC) $(CFLAGS) -c simp_file.c
	
aux.o: aux.h simp_file.h aux.c
	$(CC) $(CFLAGS) -c aux.c

main.o: aux.h simp_file.h main.c
	$(CC) $(CFLAGS) -c main.c