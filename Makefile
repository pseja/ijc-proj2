CC=gcc
CXX=g++

CFLAGS=-std=c11 # -Wall -Wextra -Werror
CXXFLAGS=-std=c++17 -Wall -Wextra -Werror

wordcount-c: wordcount.c htab_init.c htab_free.c htab_size.c htab_bucket_count.c htab_hash_function.c htab_lookup_add.c htab_clear.c htab.h htab_private.h
	$(CC) $(CFLAGS) htab_init.c htab_free.c htab_size.c htab_bucket_count.c htab_hash_function.c htab_lookup_add.c htab_clear.c wordcount.c -o wordcount-c

# wordcount-cc: wordcount.cc
# 	$(CXX) $(CXXFLAGS) wordcount.cc -o wordcount-cc

# tail: tail.c
# 	$(CC) $(CFLAGS) tail.c -o tail
