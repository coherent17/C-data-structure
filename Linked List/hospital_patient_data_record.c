#include <stdio.h>
#include <stdlib.h>

struct data{
    char name[15];
    int age;
    float height;
    float weight;
    struct data *next;
};

typedef struct data person;

person *create_person(person *head){
    //personal data
    person *new_person=malloc(sizeof(person));
    printf("Please enter the user name\n");
    scanf("%s",new_person->name);
    printf("Please enter the age of the user\n");
    scanf("%d",&(new_person->age));
    printf("Please enter the height of the user\n");
    scanf("%f",&(new_person->height));
    printf("Please enter the weight of the user\n");
    scanf("%f",&(new_person->weight));
    new_person->next=NULL;
    return new_person;
}

void print_personal_data(person *temp){
    printf("%-8s: %s\n","Name",temp->name);
    printf("%-8s: %d\n","Age",temp->age);
    printf("%-8s: %.1f\n","Height",temp->height);
    printf("%-8s: %.1f\n","Weight",temp->weight);
    printf("\n");
}

void insert_at_head(person **head, person *person_to_insert){
    if(*head==NULL){
        *head=person_to_insert;
        person_to_insert->next=NULL;
    }
    else{
        person_to_insert->next=*head;
        *head=person_to_insert;
    } 
}

void insert_at_tail(person **head, person *person_to_insert){
    if(*head==NULL){
        *head=person_to_insert;
        person_to_insert->next=NULL;
        return;
    } 
    person *temp=*head;
    while(temp!=NULL){
        if(temp->next==NULL) break;
        temp=temp->next;
    }
    temp->next=person_to_insert;
    person_to_insert->next=NULL;
}

void printList(person *head){
    person *temp=head;
    int count=1;
    while(temp!=NULL){
        printf("Person %d:\n", count);
        printf("----------------\n");
        print_personal_data(temp);
        temp=temp->next;
        count+=1;
    }
    printf("\n");
}



int main(){
    person *head=NULL;
    person *temp;

    temp=create_person(head);
    insert_at_tail(&head, temp);

    temp=create_person(head);
    insert_at_head(&head, temp);

    temp=create_person(head);
    insert_at_head(&head, temp);

    temp=create_person(head);
    insert_at_head(&head, temp);

    temp=create_person(head);
    insert_at_tail(&head, temp);

    printList(head);

    return 0;
}