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
    result->next=NULL;
    return result;
}

int main(){
    node_t *head=NULL;
    node_t *temp;

    for(int i=0;i<25;i++){
        temp=create_new_node(i);
        temp->next=head;
        head=temp;
    }
    printlist(head);

    return 0;
}

//temp=create_new_node(0)
//node   :  0
//value  :  0
//address: temp  head(NULL)

//head=temp:
//node   :  0
//value  :  0
//address: head  NULL

//temp=create_new_node(1)
//node   :  0               1
//value  :  0               1
//address: head  NULL      temp

//temp -> next =head:
//node   :  1     0               
//value  :  1     0              
//address: temp  head  NULL  

//head = temp:
//node   :  1     0               
//value  :  1     0              
//address: head       NULL   

//temp=create_new_node(2)
//node   :  1     0               2
//value  :  1     0               2
//address: head       NULL       temp

//temp -> next =head:
//node   :   2      1     0               
//value  :   2      1     0               
//address: temp   head       NULL       

//head = temp:
//node   :   2      1     0               
//value  :   2      1     0               
//address:  head               NULL  

//therefore the list is reversed