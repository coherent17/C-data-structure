CC = gcc
CFLAGS = -g -Wall
OBJ = basicTree binarySearchTree

all: $(OBJ)

basicTree: basicTree.c
	$(CC) $(CFLAGS) basicTree.c -o basicTree

binarySearchTree: binarySearchTree.c
	$(CC) $(CFLAGS) binarySearchTree.c -o binarySearchTree

clean:
	rm -f $(OBJ)