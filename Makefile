CC=gcc
CXX=g++

CFLAGS=-std=c11 # -Wall -Wextra -Werror
CXXFLAGS=-std=c++17 -Wall -Wextra -Werror
LDFLAGS=-fPIC

.PHONY: all clean

all: tail wordcount-cc wordcount wordcountStatistics wordcountDynamic

# binary files
tail: tail.o
	$(CC) $(CFLAGS) -o $@ $^

wordcount-cc: wordcount.cc
	$(CXX) $(CXXFLAGS) $< -o $@

wordcount: wordcount.o io.o libhtab.a
	$(CC) $(CFLAGS) -o $@ $^

wordcountStatistics: wordcount-statistics.o io.o libhtab.a
	$(CC) $(CFLAGS) -o $@ -static $^ -L. -lhtab

wordcountDynamic: wordcount.o io.o libhtab.so
	$(CC) $(CFLAGS) -o $@ $^ -L. -lhtab

# object files
tail.o: tail.c
	$(CC) $(CFLAGS) -c $< -o $@

wordcount.o: wordcount.c
	$(CC) $(CFLAGS) -c $< -o $@

wordcount-statistics.o: wordcount.c
	$(CC) $(CFLAGS) -DSTATISTICS -c $< -o $@

io.o: io.c io.h
	$(CC) $(CFLAGS) -c $< -o $@

# library source files
HTAB_C_FILES = htab_bucket_count.c htab_clear.c htab_erase.c htab_find.c \
				htab_for_each.c htab_free.c htab_hash_function.c htab_init.c \
				htab_lookup_add.c htab_size.c htab_statistics.c
HTAB_O_FILES = $(HTAB_C_FILES:.c=.o)

# static library
libhtab.a: $(HTAB_O_FILES)
	ar crs $@ $^

# dynamic library
HTAB_DYNAMIC_FILES = $(HTAB_C_FILES:.c=-dynamic.o)

libhtab.so: $(HTAB_DYNAMIC_FILES)
	$(CC) $(CFLAGS) -shared -o $@ $^

%-dynamic.o: %.c htab.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

run: tail wordcount-cc wordcount wordcountStatistics wordcountDynamic
	seq 1000000 2000000 | shuf > temp.txt
	./tail < temp.txt
	./wordcount-cc < temp.txt
	./wordcount < temp.txt
	./wordcountStatistics < temp.txt
	LD_LIBRARY_PATH="." ./wordcountDynamic < temp.txt
	rm temp.txt

clean:
	rm tail wordcount wordcount-cc wordcountStatistics wordcountDynamic *.o libhtab.a libhtab.so
