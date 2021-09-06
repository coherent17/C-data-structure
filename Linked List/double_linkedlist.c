#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node *next;
    struct node *prev;
} node;

void printList(node *head){
    node *temp = head;
    while(temp!=NULL){
        printf("%d - ", temp->value);
        temp = temp->next;
    }
    printf("\n");
}

node *create_new_node(int value){
    node *newnode = malloc(sizeof(node));
    newnode->value = value;
    newnode->prev = NULL;
    newnode->next = NULL;
    return newnode;
}

void insert_at_head(node **head, node *newnode){
    newnode->next = *head;
    if((*head)!=NULL){
        (*head)->prev = newnode;
    }
    *head = newnode;
}

void remove_node(node **head, node *node_to_remove){
    if(node_to_remove==NULL)
        return;
    //the node to remove is head node
    if(*head==node_to_remove){
        *head = node_to_remove->next;
        (*head)->prev = NULL;
    }
    //the node to remove is not a head node 
    else{
        node_to_remove->prev->next = node_to_remove->next;
        //the node to remove is not the tail node
        if(node_to_remove->next!=NULL){
            node_to_remove->next->prev = node_to_remove->prev;
        }
    }
    node_to_remove->next = NULL;
    node_to_remove->prev = NULL;
    free(node_to_remove);
}

node *find_node(node *head, int value){
    node *temp = head;
    while(temp!=NULL){
        if(temp->value == value)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

int main(){
    node *head=NULL;
    node *temp;

    for(int i=0;i<25;i++){
        temp=create_new_node(i);
        insert_at_head(&head,temp);
    }

    temp = find_node(head, 16);

    //remove the element in the linkedlist
    remove_node(&head, temp);

    remove_node(&head, NULL);

    //try to remove the head
    remove_node(&head, head);

    printList(head);
    return 0;
}