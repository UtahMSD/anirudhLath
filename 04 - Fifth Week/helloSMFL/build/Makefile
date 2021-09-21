
SRCDIR=../helloSMFL

INCLUDE=-I/opt/homebrew/include

# Compilation Flags
CFLAGS=-std=c++11 $(INCLUDE)
# Linking Flags
LFLAGS=-L/opt/homebrew/lib -lsfml-graphics -lsfml-system -lsfml-window

CC=g++

.PHONY : all
all : main

OBJS=main.o

main.o : $(SRCDIR)/main.cpp
	$(CC) $(CFLAGS) -c $<

main : $(OBJS)
	$(CC) $(LFLAGS) -o helloSMFL $(OBJS)
