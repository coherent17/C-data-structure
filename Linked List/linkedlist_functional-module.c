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

node_t *create_new_node(int value){
    node_t *result=malloc(sizeof(node_t));
    result->value=value;
    //temporary point to NULL, we'll point to the exact address in the main function
    result->next=NULL;
    return result;
}

node_t *insert_at_head(node_t *head, node_t *node_to_insert){
    node_to_insert->next=head;
    //return the new head address
    return node_to_insert;
}

void insert_after_node(node_t *node_to_insert_after, node_t *newnode){
    newnode->next=node_to_insert_after->next;
    node_to_insert_after->next=newnode;
}

void delete_node(node_t *head, int value){
    node_t *temp=head;
    while(temp->next!=NULL){
        if(temp->next->value==value){
            temp->next=temp->next->next;
        }
        temp=temp->next;
    }
}

node_t *find_node(node_t *head,int value){
    node_t *temp=head;
    while(temp!=NULL){
        if(temp->value==value) return temp;
        //move to the next address in the linkedlist
        temp=temp->next;
    }
    //if not found the node return NULL
    return NULL;
}

//using bubble_sort to sort the linkedlist
void sort_linkedlist(node_t *head){
    node_t *temp=head;
    while(temp->next!=NULL){
        if(temp->next->value > temp->value){
            int exchange_temp=temp->value;
            temp->value=temp->next->value;
            temp->next->value=exchange_temp;
        }
        temp=temp->next;
    }
}

int main(){
    node_t *head=NULL;
    node_t *temp;

    for(int i=0;i<25;i++){
        temp=create_new_node(i);
        head=insert_at_head(head,temp);
    }

    temp=find_node(head, 13);
    printf("found the node with value %d\n", temp->value);

    //insert 75 after 13
    insert_after_node(temp,create_new_node(75));

    //delete 75 from the linkedlist
    delete_node(head, 75);

    sort_linkedlist(head);
    printlist(head);

    return 0;
}