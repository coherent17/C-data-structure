#include <stdio.h>
#include <stdbool.h>

#define STACK_LENGTH 5
#define EMPTY (-1)
#define INT_MIN (-2147483648)
#define STACK_EMPTY INT_MIN

typedef struct stack{
    int value[STACK_LENGTH];
    //initialize each top of the each stack in main
    int top;
}stack;

bool push(stack *s, int value){
    if(s->top >= STACK_LENGTH-1) return false;

    s->top++;
    s->value[s->top] = value;
    return true;
}

int pop(stack *s){
    if(s->top == EMPTY) return STACK_EMPTY;

    int reuslt = s->value[s->top];
    s->top--;
    return reuslt;
}

int main(){

    stack stack1, stack2, stack3;
    stack1.top = EMPTY;
    stack2.top = EMPTY;
    stack3.top = EMPTY;

    push(&stack1, 56);
    push(&stack1, 78);
    push(&stack1, 13);

    push(&stack2, 25);
    push(&stack2, 75);
    push(&stack2, 69);

    push(&stack3, 43);
    push(&stack3, 29);
    push(&stack3, 46);

    int t;
    while((t=pop(&stack2))!=STACK_EMPTY){
        printf("t = %d\n", t);
    }
    return 0;
}