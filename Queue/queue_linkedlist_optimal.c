#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define EMPTY (-1)
#define INT_MIN (-2147483648)
#define QUEUE_EMPTY INT_MIN

typedef struct node{
    int value;
    struct node *next;
} node;

typedef struct queue{
    //initialize in main
    node *head;
    node *tail;
} queue;

void init_queue(queue *q){
    q->head = NULL;
    q->tail = NULL;
}

bool enqueue(queue *q, int value){
    node *newnode = malloc(sizeof(node));
    newnode->value = value;
    newnode->next = NULL;

    //the first element add into the queue
    if(q->head == NULL && q->tail == NULL){
        q->head = newnode;
        q->tail = newnode;
    }

    if(q->tail!=NULL){
        q->tail->next = newnode;
        q->tail = newnode;
    }
    return true;
}

int dequeue(queue *q){

    //check if the queue is empty
    if(q->head==NULL)
        return QUEUE_EMPTY;

    int result = q->head->value;
    node *temp = q->head;
    q->head = q->head->next;
    if(q->head==NULL){
        q->tail = NULL;
    }
    free(temp);
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
