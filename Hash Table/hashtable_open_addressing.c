#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_NAME 256
#define TABLE_SIZE 10
//define address of the pointer if the element has been deleted
#define DELETED_NODE (person *)(0xFFFFFUL) 

typedef struct{
    char name[MAX_NAME];
    int age;
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
        if(hash_table[i]==NULL) printf("\t%d\t---\n",i);

        //something in the hash table has been deleted so that the pointer point to DELETED_NODE
        else if(hash_table[i]==DELETED_NODE) printf("\t%d\t---<deleted>\n",i);

        //there exists something in the hash table
        else printf("\t%d\t%s\n",i,hash_table[i]->name);
    }
    printf("---End-----\n");
}

//insert the element into the hash_table
bool hash_table_insert(person *p){
    //calculate the index by hash_function
    int index=hash(p->name);
    
    //find the open address in hash_table, and put person in it
    for(int i=0;i<TABLE_SIZE;i++){
        int try=(i+index) % TABLE_SIZE;
        //if the address is NULL(empty) or DELETED_NODE(something had been deleted before), insert the person into the address
        if(hash_table[try]==NULL || hash_table[try]==DELETED_NODE){
            hash_table[try]=p;
            return true;
        }
    }
    //go through entire array, and don't find any address to insert, return false
    return false;
}

//want to look up whether the person is in hash_table
//if not, return null, if yes, return the pointer to the person
person *hash_table_lookup(char *name){
    int index=hash(name);
    for(int i=0;i<TABLE_SIZE;i++){
        int try=(i+index)%TABLE_SIZE;

        //nothing in the hash table
        if(hash_table[try]==NULL) return false;

        //someone had been here before, but deleted, so keep going
        if(hash_table[try]==DELETED_NODE) continue;

        //if the name equal to the name in that pointer, then return the address
        if(strncmp(hash_table[try]->name,name,TABLE_SIZE)==0){
            return hash_table[try];
        }
    }
    return NULL;
}

//want to delete the person in the hash_table
//if delete, return the address of that guy, and let that pointer point to  DELETED_NODE
person *hash_table_delete(char *name){
    int index=hash(name);
    for(int i=0;i<TABLE_SIZE;i++){
        int try=(i+index)%TABLE_SIZE;
        
        //nothing in the hash table
        if(hash_table[try]==NULL) return NULL;

        //someone had been here before, but deleted, so keep going
        if(hash_table[try]==DELETED_NODE) continue;

        //if the name equal to the name in that pointer, then set the address to DELETED_NODE, and return the original address
        if(strncmp(hash_table[try]->name,name,TABLE_SIZE)==0){
            person *tmp=hash_table[try];
            /*if the element has been deleted, set the pointer as DELETED_NODE, instead of NULL to seperated 
            to seperate whether it is deleted or empty*/
            hash_table[try]=DELETED_NODE;
            return tmp;
        }
    }
    return NULL;
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

    //try lookup someone in the hash_table
    person *tmp=hash_table_lookup("Walt");
    if(tmp==NULL || tmp==DELETED_NODE) printf("Not Found!\n");
    else printf("%s is at the address of %p\n",tmp->name,tmp);

    //delete Walt in the hash_table
    hash_table_delete("Walt");

    //after deleted Walt in Hash_table look him again
    tmp=hash_table_lookup("Walt");
    if(tmp==NULL || tmp==DELETED_NODE) printf("Not Found!\n");
    else printf("%s is at the address of %p\n",tmp->name,tmp);

    print_table();

    return 0;
}