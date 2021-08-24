#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define EMPTY (-1)
#define INT_MIN (-2147483648)
#define STACK_EMPTY INT_MIN

typedef struct node{
    int value;
    struct node *next;
} node;

node *head = NULL;

bool push(int value){
    node *newnode = malloc(sizeof(node));
    newnode->value = value;
    newnode->next = head;
    head = newnode;
    return true;
}

int pop(){
    if(head==NULL)
        return STACK_EMPTY;

    int result = head->value;
    node *temp = head;
    head = head->next;
    free(temp);
    return result;
}

int main(){
    push(56);
    push(78);
    push(13);

    int t;
    while((t=pop())!=STACK_EMPTY){
        printf("t = %d\n", t);
    }
    return 0;
}