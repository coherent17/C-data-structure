#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define INT_MIN (-2147483648)
#define QUEUE_EMPTY INT_MIN


typedef struct queue{
    //initialize in main
    int *values;
    int head;
    int tail;
    int num_entries;
    int size;
} queue;

void init_queue(queue *q, int max_size){
    q->size = max_size;
    q->values = malloc(sizeof(int) * q->size);
    q->num_entries = 0;
    q->head = 0;
    q->tail = 0;
}

bool queue_empty(queue *q){
    return (q->num_entries == 0);
}

bool queue_full(queue *q){
    return (q->num_entries == q->size);
}

void queue_destroy(queue *q){
    free(q->values);
}

bool enqueue(queue *q, int value){

    if(queue_full(q)){
        return false;
    }

    q->values[q->tail] = value;
    q->num_entries++;
    q->tail = (q->tail + 1) % q->size;
    return true;
}

int dequeue(queue *q){
    int result;

    if(queue_empty(q)){
        return QUEUE_EMPTY;
    }

    result = q->values[q->head];
    q->head = (q->head + 1) % q->size;
    q->num_entries--;
    return result;
}

int main(){

    queue q;
    init_queue(&q, 5);

    enqueue(&q, 56);
    enqueue(&q, 78);
    enqueue(&q, 23);
    enqueue(&q, 988);
    enqueue(&q, 13);
    enqueue(&q, 2);

    int t;
    while((t=dequeue(&q))!=QUEUE_EMPTY){
        printf("t = %d\n", t);
    }
    return 0;
}
