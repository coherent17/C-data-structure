#include <stdio.h>
#include <stdlib.h>

struct node{
    int value;
    struct node *next;
};
typedef struct node node_t;

void printlist(node_t *head){
    node_t *temp=head;
    while(temp!=NULL){
        printf("%d - ", temp->value);
        temp=temp->next;
    }
    printf("\n");
}


int main(){
    node_t n1, n2, n3;
    node_t *head; //where the linkedlist start

    n1.value=1;
    n2.value=2;
    n3.value=4;

    //link them up: n1 -> n2 -> n3
    head=&n1;
    n1.next=&n2;
    n2.next=&n3;
    n3.next=NULL; // when to stop

    //insert a new node between n2 and n3
    node_t new;
    new.value=3;
    n2.next=&new;
    new.next=&n3;

    printlist(head);

    return 0;
}
