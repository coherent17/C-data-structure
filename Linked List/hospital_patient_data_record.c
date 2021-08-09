#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data{
    char name[15];
    int age;
    float height;
    float weight;
    struct data *next;
};

typedef struct data person;

//global variable
person *head=NULL;

person *create_person(){
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

void insert_after_someone(person **head, person *person_to_insert){
    printf("The person's name to insert after:");
    printf("\n");
    char name[15];
    scanf("%s", name);
    person *temp=*head;
    while(temp!=NULL){
        if(strcmp(temp->name, name)==0){
            person_to_insert->next=temp->next;
            temp->next=person_to_insert;
            printf("Insert sucessfully!\n");
        }
        temp=temp->next;
    }
    printf("Can't found the person named %s\n",name);
}

void insert_personal_data(){
    if(head==NULL){
        printf("\nPlease enter 1 to create data first!\n\n");
        return;
    } 
    printf("Please enter the person data to insert:\n");
    person *temp;
    temp=create_person();
    printf("\nPlease enter the option to insert\n");
    printf("1. insert at head\t2. insert at tail\t3.insert after someone\n");
    int option;
    scanf("%d",&option);
    if(option==1){
        insert_at_head(&head,temp);
    }
    else if(option==2){
        insert_at_tail(&head,temp);
    }
    else{
        insert_after_someone(&head,temp);
    }
}

void delete_person_data(person **head){
    if(*head==NULL){
        printf("\nPlease enter 1 to create data first!\n\n");
        return;
    } 
    printf("Please enter the name of the person to delete:\n");
    char name[15];
    scanf("%s",name);
    person *temp=*head;
    //if the delete person is the head person:
    if(strcmp(temp->name,name)==0 && temp==*head){
        *head=temp->next;
        printf("Deleted %s in list(head) successfully!\n",name);
        return;
    }
    
    temp=*head;
    while(temp!=NULL){
        if(strcmp(temp->next->name,name)==0){
            temp->next=temp->next->next;
            printf("Deleted %s in list successfully!\n",name);
            return;
        }
        temp=temp->next;
    }
    printf("Not found %s in the list\n",name);
}

void person_lookup(person *head){
    if(head==NULL){
        printf("\nPlease enter 1 to create data first!\n\n");
        return;
    } 
    printf("Please enter the name of the person to lookup the data:\n");
    char name[15];
    scanf("%s",name);
    person *temp=head;
    while(temp!=NULL){
        if(strcmp(temp->name,name)==0){
            print_personal_data(temp);
            return;
        }
        temp=temp->next;
    }
    printf("\nNot found %s in the list!\n\n",name);
}

void modify_person(person *head){
    if(head==NULL){
        printf("\nPlease enter 1 to create data first!\n\n");
        return;
    }
    printf("Please enter the name of the person to modify:\n");
    char name[15];
    scanf("%s",name);
    person *temp=head;
    while(temp!=NULL){
        if(strcmp(temp->name,name)==0){
            printf("Please enter the new user name\n");
            scanf("%s",temp->name);
            printf("Please enter the new age of the user\n");
            scanf("%d",&(temp->age));
            printf("Please enter the new height of the user\n");
            scanf("%f",&(temp->height));
            printf("Please enter the new weight of the user\n");
            scanf("%f",&(temp->weight));
            printf("Finish modifying, here is the new personal data:\n");
            print_personal_data(temp);
            return;
        }
        temp=temp->next;
    }
    printf("Not found %s in the list\n\n",name);
}

void printList(person *head){
    if(head==NULL){
        printf("\nPlease enter 1 to create data first!\n\n");
        return;
    } 
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

void menu(){
    printf("********************************************\n");
    printf("        Hospital personal datalist          \n");
    printf("                                            \n");
    printf("\t1. create personal data\n");
    printf("\t2. print the datalist\n");
    printf("\t3. insert the data\n");
    printf("\t4. delete the data\n");
    printf("\t5. look up personal data\n");
    printf("\t6. modify the personal data\n");
    printf("********************************************\n");
    printf("Please enter your choice(1~5, Ctrl+z for exit):");
}

void selection_function(){
    menu();
    int choice;
    while(scanf("%d", &choice)!=EOF){
        if(choice==1){
            person *temp=create_person(head);
            insert_at_tail(&head, temp);
        }

        else if(choice==2){
            printList(head);
        }

        else if(choice==3){
            insert_personal_data();
        }

        else if(choice==4){
            delete_person_data(&head);
        }

        else if(choice==5){
            person_lookup(head);
        }

        else if(choice==6){
            modify_person(head);
        }

        menu();
    }
}

int main(){
    selection_function();
    return 0;
}