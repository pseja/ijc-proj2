CC=gcc
CXX=g++

CFLAGS=-std=c11 -Wall -Wextra -Werror
CXXFLAGS=-std=c++17 -Wall -Wextra -Werror

# wordcount: wordcount.cc
# 	$(CXX) $(CXXFLAGS) wordcount.cc -o wordcount-cc

tail: tail.c
	$(CC) $(CFLAGS) tail.c -o tail 
