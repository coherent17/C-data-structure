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
    printf("Please enter the user name:\n");
    scanf("%s",new_person->name);
    printf("Please enter the age(integer) of the user:\n");
    scanf("%d",&(new_person->age));
    printf("Please enter the height(float) of the user:\n");
    scanf("%f",&(new_person->height));
    printf("Please enter the weight(float) of the user:\n");
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
            return;
        }
        temp=temp->next;
    }
    printf("Can't found the person named %s\n",name);
}

void insert_personal_data(person *head){
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

    switch(option){
        case(1):
            insert_at_head(&head,temp);
            break;
        case(2):
            insert_at_tail(&head,temp);
            break;
        case(3):
            insert_after_someone(&head,temp);
            break;
        default:
            printf("Not supported!\n");
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
        free(temp);
        *head=temp->next;
        printf("Deleted %s in list(head) successfully!\n",name);
        return;
    }
    
    temp=*head;
    while(temp!=NULL){
        if(strcmp(temp->next->name,name)==0){
            free(temp->next);
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
    printf("\n");
    while(temp!=NULL){
        printf("Person %d:\n", count);
        printf("----------------\n");
        print_personal_data(temp);
        temp=temp->next;
        count+=1;
    }
    printf("\n");
}

void count_person(person *head){
    if(head==NULL){
        printf("\nPlease enter 1 to create data first!\n\n");
        return;
    } 
    int count=0;
    person *temp=head;
    while(temp!=NULL){
        count+=1;
        temp=temp->next;    
    }
    printf("\nThere are %d people in the list\n\n",count);
}

void swap_int(int *a, int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}

void swap_float(float *a, float *b){
    float temp=*a;
    *a=*b;
    *b=temp;
}

void swap_string(char *a, char *b){
    char temp[15];
    //initialize the string
    memset(temp,'\0',sizeof(temp));
    //copy a to temp
    for(int i=0;i<strlen(a);i++){
        temp[i]=a[i];
    }
    memset(a,'\0',sizeof(a));
    for(int i=0;i<strlen(b);i++){
        a[i]=b[i];
    }
    memset(b,'\0',sizeof(b));
    for(int i=0;i<strlen(temp);i++){
        b[i]=temp[i];
    }
}

void sort_by_age(person *head){
    if(head==NULL){
        printf("\nPlease enter 1 to create data first!\n\n");
        return;
    }
     //bubble sort
     person *i,*j;
     for(i=head;i->next!=NULL;i=i->next){
        for(j=i->next;j!=NULL;j=j->next){
            if(i->age>j->age){
                //exchange personal data:
                swap_string((i->name),(j->name));
                swap_int(&(i->age),&(j->age));
                swap_float(&(i->height),&(j->height));
                swap_float(&(i->weight),&(j->weight));
            }
        }
    }
    printf("\nThe list has been sorted by age:\n");
    printList(head);
}

void sort_by_height(person *head){
    if(head==NULL){
        printf("\nPlease enter 1 to create data first!\n\n");
        return;
    }
     //bubble sort
     person *i,*j;
     for(i=head;i->next!=NULL;i=i->next){
        for(j=i->next;j!=NULL;j=j->next){
            if(i->height>j->height){
                //exchange personal data:
                swap_string((i->name),(j->name));
                swap_int(&(i->age),&(j->age));
                swap_float(&(i->height),&(j->height));
                swap_float(&(i->weight),&(j->weight));
            }
        }
    }
    printf("\nThe list has been sorted by height:\n");
    printList(head);
}

void sort_by_weight(person *head){
    if(head==NULL){
        printf("\nPlease enter 1 to create data first!\n\n");
        return;
    }
     //bubble sort
     person *i,*j;
     for(i=head;i->next!=NULL;i=i->next){
        for(j=i->next;j!=NULL;j=j->next){
            if(i->weight>j->weight){
                //exchange personal data:
                swap_string((i->name),(j->name));
                swap_int(&(i->age),&(j->age));
                swap_float(&(i->height),&(j->height));
                swap_float(&(i->weight),&(j->weight));
            }
        }
    }
    printf("\nThe list has been sorted by weight:\n");
    printList(head);
}

void save_txt(person *head){
    if(head==NULL){
        printf("\nPlease enter 1 to create data first!\n\n");
        return;
    }
    FILE *pfile;
    char filename[15];
    printf("Please enter the output filename + .txt:\n");
    scanf("%s",filename);
    pfile=fopen(filename,"w");
    person *temp=head;
    int count=1;
    while(temp!=NULL){
        fprintf(pfile,"Person %d:\n", count);
        fprintf(pfile,"----------------\n");
        fprintf(pfile,"%-8s: %s\n","Name",temp->name);
        fprintf(pfile,"%-8s: %d\n","Age",temp->age);
        fprintf(pfile,"%-8s: %.1f\n","Height",temp->height);
        fprintf(pfile,"%-8s: %.1f\n","Weight",temp->weight);
        fprintf(pfile,"\n");
        temp=temp->next;
        count+=1;
    }
    fclose(pfile);
    printf("\nSave the data to %s successfully!\n",filename);
}


void menu(){
    printf("*********************************************\n");
    printf("*   personal data linked list practice      *\n");
    printf("*                                           *\n");
    printf("*    1. Create personal data                *\n");
    printf("*    2. Print the datalist                  *\n");
    printf("*    3. Insert the data                     *\n");
    printf("*    4. Delete the data                     *\n");
    printf("*    5. Look up personal data               *\n");
    printf("*    6. Modify the personal data            *\n");
    printf("*    7. How many people in the list         *\n");
    printf("*    8. Sort by age                         *\n");
    printf("*    9. Sort by height                      *\n");
    printf("*   10. Sort by weight                      *\n");
    printf("*   11. Save the linkedlist as txt file     *\n");
    printf("*********************************************\n");
    printf("Please enter your choice(1~11, Ctrl+z for exit):");
}


int main(){
    menu();
    int choice;
    while(scanf("%d", &choice)!=EOF){
        person *temp;
        switch(choice){
            case(1):
                temp=create_person(head);
                insert_at_tail(&head, temp);
                break;
            case(2):
                printList(head);
                break;
            case(3):
                insert_personal_data(head);
                break;
            case(4):
                delete_person_data(&head);
                break;
            case(5):
                person_lookup(head);
                break;
            case(6):
                modify_person(head);
                break;
            case(7):
                count_person(head);
                break;
            case(8):
                sort_by_age(head);
                break;
            case(9):
                sort_by_height(head);
                break;
            case(10):
                sort_by_weight(head);
                break;
            case(11):
                save_txt(head);
                break;
            default:
                printf("Not supported!\n");
        }
        menu();
    }
    return 0;
}