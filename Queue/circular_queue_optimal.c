#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define INT_MIN (-2147483648)
#define QUEUE_EMPTY INT_MIN
#define MAX_SIZE 5


typedef struct queue{
    //initialize in main
    int *values;
    int head;
    int tail;
    int num_entries;
} queue;

void init_queue(queue *q){
    q->values = malloc(sizeof(int) * MAX_SIZE);
    q->num_entries = 0;
    q->head = -1;
    q->tail = -1;
}

bool queue_empty(queue *q){
    return (q->num_entries == 0);
}

bool queue_full(queue *q){
    if((q->head==q->tail+1)||(q->head==0&&q->tail==MAX_SIZE-1))
        return true;
    return false;
}

void queue_destroy(queue *q){
    free(q->values);
}

bool enqueue(queue *q, int value){

    if(queue_full(q)){
        return false;
    }

    //the first element entry the queue
    if(q->head==-1)
        q->head = 0;

    q->tail = (q->tail + 1) % MAX_SIZE;
    q->values[q->tail] = value;
    q->num_entries++;
    return true;
}

int dequeue(queue *q){
    int result;

    if(queue_empty(q)){
        return QUEUE_EMPTY;
    }
    else{
        result = q->values[q->head];
        if(q->head==q->tail){
            q->head = -1;
            q->tail = -1;
        }
        else{
            q->head = (q->head + 1) % MAX_SIZE;
        }
        q->num_entries--;
    }
    return result;
}

void printQueue(queue *q){
    if(queue_empty(q)){
        printf("\nQueueEmpty\n");
    }
    else{
        int i;
        printf("\n head -> %d", q->head);
        printf("\n values -> ");
        for (i = q->head; i != q->tail;i=(i+1)%MAX_SIZE){
            printf("%d ", q->values[i]);
        }
        printf("%d ", q->values[i]);
        printf("\n tail -> %d\n", q->tail);
    }
}

int main(){

    queue q;
    init_queue(&q);

    printQueue(&q);

    enqueue(&q, 1);
    enqueue(&q, 2);
    enqueue(&q, 3);
    enqueue(&q, 4);
    enqueue(&q, 5);

    printQueue(&q);

    int t = dequeue(&q);
    printf("t = %d\n", t);

    t = dequeue(&q);
    printf("t = %d\n", t);

    enqueue(&q, 6);
    enqueue(&q, 7);

    printQueue(&q);

    return 0;
}
