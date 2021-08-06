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

int how_many_node(node_t *head){
    node_t *temp=head;
    int count=0;
    while(temp!=NULL){
        count+=1;
        temp=temp->next;
    }
    return count;
}

//using bubble_sort to sort the linkedlist
void sort_linkedlist(node_t *head){
    node_t *i,*j;
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
node_t *middle_of_the_linkedlist(node_t *head){
    node_t *slow_pointer=head;
    node_t *fast_pointer=head->next;
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

//using do-while to loop the binary search do it first then check
node_t *binary_search_node(node_t *head, int number){
    node_t *left=head;
    node_t *right=NULL;
    do{
        node_t *mid=middle_of_the_linkedlist(head);
        //if middle element is same as the required number
        if(mid->value==number) return mid;
        //middle element is greater than the element
        else if(mid->value<number) left=mid->next;
        else right=mid;
    }while(right==NULL || right!=left);
    //if not found the value, return NULL
    return NULL;
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

    int node_count=how_many_node(head);
    printf("There are %d nodes in linkedlist\n", node_count);

    printlist(head);

    temp=middle_of_the_linkedlist(head);
    printf("the middle elemennt in the linkedlist is: %d\n", temp->value);

    //binary search:
    temp=binary_search_node(head,19);
    printf("%d\n", temp->value);
    return 0;
}