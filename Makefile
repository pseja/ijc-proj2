CC=gcc
FLAGS=-std=c11 -Wall -Wextra -Werror 

tail: tail.c
	$(CC) $(FLAGS) tail.c -o tail 
