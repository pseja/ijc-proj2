CC=gcc
FLAGS=

tail: tail.c
	$(CC) $(FLAGS) tail.c -o tail 
