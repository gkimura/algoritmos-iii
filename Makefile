CC = gcc
CFLAGS = -Wall

main : main.o dicionario.o 
	$(CC) $(CFLAGS) main.o dicionario.o -o dicionario

main.o : main.c	
	$(CC) $(CFLAGS) -c main.c

dicionario.o : dicionario.c
	$(CC) $(CFLAGS) -c dicionario.c

clean :
	rm *.o dicionario
