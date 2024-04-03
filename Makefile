CC=gcc
CXX=g++

CFLAGS=-std=c11 -Wall -Wextra -Werror
CXXFLAGS=-std=c++17 -Wall -Wextra -Werror

wordcount-c: wordcount.c htab_init.c htab.h htab_private.h
	$(CC) $(CFLAGS) htab_init.c wordcount.c -o wordcount-c

# wordcount-cc: wordcount.cc
# 	$(CXX) $(CXXFLAGS) wordcount.cc -o wordcount-cc

# tail: tail.c
# 	$(CC) $(CFLAGS) tail.c -o tail
