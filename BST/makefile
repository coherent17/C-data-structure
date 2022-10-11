CC = gcc
CFLAGS = -g -Wall
BIN = BST
OBJ = BST.o

all: $(BIN)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

$(BIN): main.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm $(BIN) $(OBJ)