#include <stdio.h>
#include <stdbool.h>

#define STACK_LENGTH 5
#define EMPTY (-1)
#define INT_MIN (-2147483648)
#define STACK_EMPTY INT_MIN

int stack[STACK_LENGTH];
int top = EMPTY;

bool push(int value){
    if(top >= STACK_LENGTH-1) return false;

    top++;
    stack[top] = value;
    return true;
}

int pop(){
    if(top == EMPTY) return STACK_EMPTY;

    int reuslt = stack[top];
    top--;
    return reuslt;
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