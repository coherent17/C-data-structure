CC = gcc
CFLAGS = -g -Wall
BIN = RBT
OBJ = RBT.o

all: $(BIN)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

$(BIN): main.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm $(BIN) $(OBJ)