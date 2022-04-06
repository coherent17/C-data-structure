CC = gcc
CFLAGS = -g -Wall
OBJS = btree.o
BIN = Btree

all: $(BIN)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN): main.c $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lm

do:
	./Btree

clean:
	rm -f $(OBJ)