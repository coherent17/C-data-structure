#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct nodes{
    int value;
    struct nodes *next;
};

typedef struct nodes node;

void printList(node *);
node *create_node(int);
void insert_at_head(node **, node *);
void insert_at_tail(node *, node *);
node *find_node(node *, int);
void insert_after_node(node *, int);
void delete_node(node *, int);
int number_of_node(node *);
void sortList(node *);
int *list_to_array(node *, int *);
node *middleNode(node *);

int main(){
    node *head=NULL; //point to the head of the linkedlist
    node *temp;

    for(int i=0;i<20;i++){
        temp=create_node(i);
        insert_at_head(&head, temp);
    }

    //find the element in the node:
    find_node(head, 13);
    find_node(head, 20);

    printf("Before\n");
    printList(head);

    //insert 26 after 17
    insert_after_node(find_node(head,17),26);
    
    //delete 6
    delete_node(head, 6);

    //insert 100 at the end of the linkedlist:
    insert_at_tail(head, create_node(100));

    printf("After\n");
    printList(head);
    
    printf("There are %d nodes in the linkedlist\n", number_of_node(head));
    sortList(head);
    printf("After sorting:\n");
    printList(head);

    //copy the linked to array
    int size_of_array;
    int *array=list_to_array(head, &size_of_array);
    printf("Array:\n");
    for(int i=0;i<size_of_array;i++){
        printf("%d ", array[i]);
    }
    printf("\n");
    printf("The middle node of the linkedlist is %d\n", middleNode(head)->value);

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

node *create_node(int value){
    node *temp=malloc(sizeof(node));
    temp->value=value;
    temp->next=NULL;
    return temp;
}

void insert_at_head(node **head, node* node_to_insert){
    node_to_insert->next=*head;
    *head=node_to_insert;
}

void insert_at_tail(node *head, node *node_to_insert){
    node *temp=head;
    while(temp!=NULL){
        if(temp->next==NULL) break;
        temp=temp->next;
    }
    temp->next=node_to_insert;
    node_to_insert->next=NULL;
}

node *find_node(node *head, int value){
    node *temp=head;
    while(temp!=NULL){
        if(temp->value==value){
            printf("Found %d at %p\n", temp->value, &temp->value);
            return temp;
        }
        temp=temp->next;
    }
    //if the element can't be found in the linkedlist
    printf("Not found %d in the linkedlist\n", value);
    return NULL;
}

void insert_after_node(node *node_to_insert_after, int new_node_value){
    node *new_node=create_node(new_node_value);
    new_node->next=node_to_insert_after->next;
    node_to_insert_after->next=new_node;
}

void delete_node(node *head, int value){
    node *temp=head;
    while(temp->next!=NULL){
        if(temp->next->value==value){
            temp->next=temp->next->next;
        }
        temp=temp->next;
    }
}

int number_of_node(node *head){
    node *temp=head;
    int count=0;
    while(temp!=NULL){
        count+=1;
        temp=temp->next;
    }
    return count;
}

void sortList(node *head){
    node *i, *j;
    for(i=head;i->next!=NULL;i=i->next){
        for(j=i->next;j!=NULL;j=j->next){
            if(i->value > j->value){
                int exchange_temp=j->value;
                j->value=i->value;
                i->value=exchange_temp;
            }
        }
    }
}

int *list_to_array(node *head, int *returnSize){
    node *temp=head;
    int *array=malloc(sizeof(node)*number_of_node(head));
    *returnSize=0;
    while(temp!=NULL){
        array[*returnSize]=temp->value;
        *returnSize+=1;
        temp=temp->next;
    }
    return array;
}

//two pointers
node *middleNode(node *head){
    node *slow_pointer=head;
    node *fast_pointer=head->next;
    while(fast_pointer!=NULL){
        //fast pointer move one step
        fast_pointer=fast_pointer->next;
        if(fast_pointer!=NULL){
            //slow pointer move one step
            slow_pointer=slow_pointer->next;
            //fast pointer move second step
            fast_pointer=fast_pointer->next;
        }
    }
    return slow_pointer;
}