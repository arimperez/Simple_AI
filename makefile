
CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -g
INCLUDES = -Iinclude

BINDIR = bin/
SRCDIR = src/

OBJDIR = obj/

SOURCE = $(SRCDIR)BinarySearchTreeAPI.c $(SRCDIR)main.c $(SRCDIR)ai.c
TESTSRC = $(SRCDIR)BinarySearchTreeAPI.c $(SRCDIR)testMain.c

create:
	$(CC) $(CFLAGS) $(SOURCE) $(INCLUDES) -o $(BINDIR)run

test:
	$(CC) $(CFLAGS) $(TESTSRC) $(INCLUDES) -o $(BINDIR)test
run:
	./bin/run docs/words.txt

runTest:
	./bin/test

clean:
