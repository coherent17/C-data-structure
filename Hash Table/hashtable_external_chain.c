#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct person{
    char name[MAX_NAME];
    int age;
    struct person *next;
}person;

person *hash_table[TABLE_SIZE];

//define the hash function
unsigned int hash(char *name){
    int length=strnlen(name, MAX_NAME);
    unsigned int hash_value=0;
    for(int i=0;i<length;i++){
        hash_value+=name[i];
        hash_value=(hash_value*name[i])%TABLE_SIZE;
    }
    return hash_value;
}

//initialize the hash table to NULL (let it be empty)
void init_hash_table(){
    for(int i=0;i<TABLE_SIZE;i++){
        hash_table[i]=NULL;
    }
}

//print out the hash table
void print_table(){
    printf("---Start---\n");
    for(int i=0;i<TABLE_SIZE;i++){
        //nothing in the hash table
        if(hash_table[i]==NULL)
            printf("\t%d\t---\n",i);

        else{
            printf("\t%d\t",i);
            person *temp = hash_table[i];
            while(temp!=NULL){
                printf("%s - ", temp->name);
                temp = temp->next;
            }
            printf("\n");
        }
    }
    printf("---End-----\n");
}

//insert the element into the hash_table
bool hash_table_insert(person *p){
    //calculate the index by hash_function
    int index=hash(p->name);
    
    //insert the person as the head node of the chain
    person *newperson = malloc(sizeof(person));
    strcpy(newperson->name, p->name);
    newperson->age = p->age;
    newperson->next = NULL;
    newperson->next = hash_table[index];
    hash_table[index] = newperson;
    return true;
}

//want to look up whether the person is in hash_table
//if not, return null, if yes, return the pointer to the person
person *hash_table_lookup(char *name){
    int index=hash(name);
    person *temp = hash_table[index];
    while(temp!=NULL && strncmp(temp->name, name, MAX_NAME)!=0){
        temp = temp->next;
    }
    return temp;
}

//want to delete the person in the hash_table
//if delete, return the address of that guy, and free the address in main
void hash_table_delete(char *name){
    int index=hash(name);
    person *temp = hash_table[index];
    person *prev = NULL;
    while(temp!=NULL && strncmp(temp->name, name, MAX_NAME)!=0){
        prev = temp;
        temp = temp->next;
    }
    //delete head pointer
    if(prev==NULL)
        hash_table[index] = hash_table[index]->next;
    else{
        prev->next = temp->next;
    }
    free(temp);
}

int main(){

    init_hash_table();

    //hash function calculate
    printf("Walt -> %u\n",hash("Walt"));
    printf("Skyler -> %u\n",hash("Skyler"));
    printf("Saul -> %u\n",hash("Saul"));
    printf("Mike -> %u\n",hash("Mike"));
    printf("Hank -> %u\n",hash("Hank"));
    printf("Mary -> %u\n",hash("Mary"));
    printf("Holy -> %u\n",hash("Holy"));
    printf("Jessie -> %u\n",hash("Jessie"));
    printf("Todd -> %u\n",hash("Todd"));


    person Walt={.name="Walt",.age=26};
    person Skyler={.name="Skyler",.age=27};
    person Saul={.name="Saul",.age=28};
    person Mike={.name="Mike",.age=29};
    person Hank={.name="Hank",.age=30};
    person Mary={.name="Mary",.age=31};
    person Holy={.name="Holy",.age=32};
    person Jessie={.name="Jessie",.age=33};
    person Todd={.name="Todd",.age=34};

    
    //add person into hash_table
    hash_table_insert(&Walt);
    hash_table_insert(&Skyler);
    hash_table_insert(&Saul);
    hash_table_insert(&Mike);
    hash_table_insert(&Hank);
    hash_table_insert(&Mary);
    hash_table_insert(&Holy);
    hash_table_insert(&Jessie);
    hash_table_insert(&Todd);

    print_table();

    hash_table_delete("Saul");
    hash_table_delete("Holy");
    hash_table_delete("Mike");

    print_table();
    return 0;
}