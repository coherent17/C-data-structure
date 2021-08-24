CC = gcc
CFLAGS = -g -Wall

all: stack_array stack_linkedlist stack_linkedlist_optimal stack_array_optimal

stack_array: stack_array.c
	$(CC) $(CFLAGS) stack_array.c -o stack_array

stack_linkedlist: stack_linkedlist.c 
	$(CC) $(CFLAGS) stack_linkedlist.c -o stack_linkedlist

stack_linkedlist_optimal: stack_linkedlist_optimal.c
	$(CC) $(CFLAGS) stack_linkedlist_optimal.c -o stack_linkedlist_optimal

stack_array_optimal: stack_array_optimal.c
	$(CC) $(CFLAGS) stack_array_optimal.c -o stack_array_optimal

clean:
	rm -f stack_array stack_linkedlist stack_linkedlist_optimal stack_array_optimal