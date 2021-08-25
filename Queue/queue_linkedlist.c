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

node *head = NULL;
node *tail = NULL;

bool enqueue(int value){
    node *newnode = malloc(sizeof(node));
    newnode->value = value;
    newnode->next = NULL;

    //the first element add into the queue
    if(head == NULL && tail == NULL){
        head = newnode;
        tail = newnode;
    }

    //add the seoond or third node into the queue
    else{
        tail->next = newnode;
        tail = newnode;
    }
    return true;
}

int dequeue(){

    //check if the queue is empty
    if(head==NULL)
        return QUEUE_EMPTY;

    int result = head->value;
    node *temp = head;
    head = head->next;
    if(head==NULL){
        tail = NULL;
    }
    free(temp);
    return result;
}

int main(){
    enqueue(3);
    enqueue(6);
    enqueue(5);

    int t;
    while((t=dequeue())!=QUEUE_EMPTY){
        printf("t = %d\n", t);
    }
    return 0;
}
