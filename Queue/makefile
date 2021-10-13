CC = gcc
CFLAGS = -g -Wall
OBJ = queue_linkedlist queue_array queue_array_optimal queue_linkedlist_optimal circular_queue circular_queue_optimal

all: $(OBJ)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJ)
