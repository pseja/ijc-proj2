CC=gcc
CXX=g++

CFLAGS=-std=c11 # -Wall -Wextra -Werror
CXXFLAGS=-std=c++17 -Wall -Wextra -Werror

.PHONY: all clean

all: tail wordcount-c wordcount-cc

wordcount-c: wordcount.c htab_init.c htab_free.c htab_size.c htab_bucket_count.c htab_hash_function.c htab_lookup_add.c htab_clear.c htab_find.c htab_erase.c htab_for_each.c htab_statistics.c htab.h htab_private.h io.c io.h
	$(CC) $(CFLAGS) htab_init.c htab_free.c htab_size.c htab_bucket_count.c htab_hash_function.c htab_lookup_add.c htab_clear.c htab_find.c htab_erase.c htab_for_each.c htab_statistics.c io.c wordcount.c -o wordcount-c.o

tail: tail.c
	$(CC) $(CFLAGS) tail.c -o tail.o

wordcount-cc: wordcount.cc
	$(CXX) $(CXXFLAGS) wordcount.cc -o wordcount-cc

clean:
	rm *.o