#include <stdio.h>
#include <stdbool.h>

#define QUEUE_LENGTH 5
#define EMPTY (-1)
#define INT_MIN (-2147483648)
#define QUEUE_EMPTY INT_MIN

int queue[QUEUE_LENGTH];
int tail = -1;
int head = -1;

bool enqueue(int value){
    if(tail >= QUEUE_LENGTH-1) return false;
    tail++;
    queue[tail] = value;
    return true;
}

int dequeue(){
    if(tail==EMPTY)
        return QUEUE_EMPTY;
    int result = queue[head+1];

    //shift all of the element forword
    for (int i = 1; i <= tail;i++){
        queue[i - 1] = queue[i];
    }
    tail--;
    return result;
}

int main(){
    enqueue(1);
    enqueue(4);
    enqueue(3);

    int t;
    while((t=dequeue())!=QUEUE_EMPTY){
        printf("t = %d\n", t);
    }
    return 0;
}