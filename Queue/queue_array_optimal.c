#include <stdio.h>
#include <stdbool.h>

#define QUEUE_LENGTH 5
#define EMPTY (-1)
#define INT_MIN (-2147483648)
#define QUEUE_EMPTY INT_MIN


typedef struct queue{
    int value[QUEUE_LENGTH];
    //initialize each head and tail in main
    int tail;
    int head;
} queue;

void init_queue(queue *q){
    q->head = EMPTY;
    q->tail = EMPTY;
}

bool enqueue(queue *q, int value){
    if(q->tail >= QUEUE_LENGTH-1) return false;
    q->tail++;
    q->value[q->tail] = value;
    return true;
}

int dequeue(queue *q){
    if(q->tail==EMPTY)
        return QUEUE_EMPTY;
    int result = q->value[q->head+1];

    //shift all of the element forword
    for (int i = 1; i <= q->tail;i++){
        q->value[i - 1] = q->value[i];
    }
    q->tail--;
    return result;
}

int main(){

    queue q1, q2, q3;
    init_queue(&q1);
    init_queue(&q2);
    init_queue(&q3);

    enqueue(&q1, 15);
    enqueue(&q1, 16);
    enqueue(&q1, 29);
    
    enqueue(&q2, 46);
    enqueue(&q2, 23);
    enqueue(&q2, 49);

    enqueue(&q3, 23);
    enqueue(&q3, 21);
    enqueue(&q3, 27);

    int t;
    while((t=dequeue(&q2))!=QUEUE_EMPTY){
        printf("t = %d\n", t);
    }
    return 0;
}