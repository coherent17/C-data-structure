#include<stdio.h>

struct nodes{
    int value;
    struct nodes *next;
};

typedef struct nodes node;

void printList(node *);

int main(){
    node node1, node2, node3;
    node *head; //point to the head of the linkedlist

    
    node1.value=128;
    node2.value=64;
    node3.value=45;

    //link them into the chain: head -> node1 -> node2 -> node3 -> NULL
    head=&node1;
    node1.next=&node2;
    node2.next=&node3;
    node3.next=NULL;

    //insert new node between node2 and node3
    node node_to_insert;
    node_to_insert.value=17;
    node2.next=&node_to_insert;
    node_to_insert.next=&node3;

    //print them out
    printList(head);

    return 0;
}

void printList(node *head){
    node *temp=head;
    printf("head - ");
    while(temp!=NULL){
        printf("%d - ",temp->value);
        temp=temp->next;
    }
    printf("NULL\n");
}