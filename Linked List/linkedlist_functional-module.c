#include <stdio.h>
#include <stdlib.h>

struct nodes{
    int value;
    struct nodes *next;
};
//avoid typing struct many times
typedef struct nodes node;

void printlist(node *head){
    node *temp=head;
    while(temp!=NULL){
        printf("%d - ", temp->value);
        temp=temp->next;
    }
    printf("\n");
}

node *create_new_node(int value){
    node *result=malloc(sizeof(node));
    result->value=value;
    //temporary point to NULL, we'll point to the exact address in the main function
    result->next=NULL;
    return result;
}

node *insert_at_head(node *head, node *node_to_insert){
    node_to_insert->next=head;
    //return the new head address
    return node_to_insert;
}

void insert_after_node(node *node_to_insert_after, node *newnode){
    newnode->next=node_to_insert_after->next;
    node_to_insert_after->next=newnode;
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

node *find_node(node *head,int value){
    node *temp=head;
    while(temp!=NULL){
        if(temp->value==value) return temp;
        //move to the next address in the linkedlist
        temp=temp->next;
    }
    //if not found the node return NULL
    return NULL;
}

int how_many_node(node *head){
    node *temp=head;
    int count=0;
    while(temp!=NULL){
        count+=1;
        temp=temp->next;
    }
    return count;
}

//using bubble_sort to sort the linkedlist
void sort_linkedlist(node *head){
    node *i,*j;
    for(i=head;i->next!=NULL;i=i->next){
        for(j=i->next;j!=NULL;j=j->next){
            if(i->value>j->value){
                int exchange_temp=j->value;
                j->value=i->value;
                i->value=exchange_temp;
            }
        }
    }
}

//want to find the mid point of the linkedlist and return the address
//using two pointer method: fast move two and slow move one
node *middle_of_the_linkedlist(node *head){
    node *slow_pointer=head;
    node *fast_pointer=head->next;
    //slow, fast
    while(fast_pointer!=NULL){
        //fast move one step ahead  slow, ___, fast
        fast_pointer=fast_pointer->next;
        //if fast is not the end of the linkedlist:
        if(fast_pointer!=NULL){
            //slow move one step
            slow_pointer=slow_pointer->next;
            //fast move the second step
            fast_pointer=fast_pointer->next;
        }
    }
    return slow_pointer;
}

int *copy_linkedlist_to_array(node *head){
    node *temp=head;
    int length=how_many_node(head);
    int *array=malloc(sizeof(int)*length);
    int index=0;
    while(temp!=NULL){
        array[index]=temp->value;
        index+=1;
        temp=temp->next;
    }
    return array;
}

int main(){
    node *head=NULL;
    node *temp;

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

    int node_count=how_many_node(head);
    printf("There are %d nodes in linkedlist\n", node_count);

    printlist(head);

    temp=middle_of_the_linkedlist(head);
    printf("the middle elemennt in the linkedlist is: %d\n", temp->value);

    int *array=copy_linkedlist_to_array(head);
    for(int i=0;i<node_count;i++){
        printf("%d ",array[i]);
    }
    return 0;
}