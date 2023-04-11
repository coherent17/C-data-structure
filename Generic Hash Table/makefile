CC = gcc
CFLAGS = -g -Wall
OBJS = hashtable.o
BINS = main

all: $(BINS)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BINS): main.c $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@


clean:
	rm $(BINS) $(OBJS)

.PHONY: all clean