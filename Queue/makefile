CC = gcc
CFLAGS = -g -Wall

all: queue_linkedlist queue_array queue_array_optimal queue_linkedlist_optimal

queue_linkedlist: queue_linkedlist.c
	$(CC) $(CFLAGS) queue_linkedlist.c -o queue_linkedlist

queue_array: queue_array.c
	$(CC) $(CFLAGS) queue_array.c -o queue_array

queue_array_optimal: queue_array_optimal.c
	$(CC) $(CFLAGS) queue_array_optimal.c -o queue_array_optimal

queue_linkedlist_optimal: queue_linkedlist_optimal.c
	$(CC) $(CFLAGS) queue_linkedlist_optimal.c -o queue_linkedlist_optimal

clean:
	rm -f queue_linkedlist queue_array queue_array_optimal queue_linkedlist_optimal
