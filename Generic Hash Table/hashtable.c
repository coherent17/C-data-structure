#include "hashtable.h"
#include <string.h>
#include <stdio.h>

typedef struct entry{
    char *key;
    void *obj;
    struct entry *next; //external chaining
}entry;

typedef struct _hash_table{
    uint32_t size;
    hashfunction *hash;
    entry **elements;   //array of pointers
}hash_table;

//private function to get the index of the given key
static size_t hash_table_index(hash_table *ht, const char *key){
    size_t result = (ht->hash(key, strlen(key)) % ht->size);
    return result;
}


hash_table *hash_table_create(uint32_t size, hashfunction *hf){
    hash_table *ht = malloc(sizeof(ht));
    ht->size = size;
    ht->hash = hf;
    ht->elements = calloc(sizeof(entry *), ht->size);
    return ht;
}

void hash_table_destroy(hash_table *ht){
    free(ht->elements);
    free(ht);
}

void hash_table_print(hash_table *ht){
    printf("Start Table\n");
    for(uint32_t i = 0; i < ht->size; i++){
        if(ht->elements[i] == NULL){
            //printf("\t%i\t---\n", i);
        }
        else{
            printf("\t%i\t", i);
            entry *tmp = ht->elements[i];
            while(tmp != NULL){
                printf(" \"%s\" [%p] - ", tmp->key, tmp->obj);
                tmp = tmp->next;
            }
            printf("\n");
        }
    }
    printf("End Table\n");
}


bool hash_table_insert(hash_table *ht, const char *key, void *obj){
    //can't be NULL key nor NULL object nor NULL hash table
    if(key == NULL || obj == NULL || ht == NULL) return false;
    size_t index = hash_table_index(ht, key);

    //make sure no duplicate key
    if(hash_table_lookup(ht, key) != NULL) return false;

    //create a new entry
    entry *e = malloc(sizeof(entry));
    e->obj = obj;
    e->key = malloc(strlen(key) + 1);
    strcpy(e->key, key);

    //insert the entry
    e->next = ht->elements[index];
    ht->elements[index] = e;
    return true;
}

void *hash_table_lookup(hash_table *ht, const char *key){
    //can't be NULL key nor NULL object nor NULL hash table
    if(key == NULL || ht == NULL) return false;
    size_t index = hash_table_index(ht, key);

    entry *tmp = ht->elements[index];
    while(tmp != NULL && strcmp(tmp->key, key) != 0){
        tmp = tmp->next;
    }
    if(tmp == NULL) return NULL;
    return tmp->obj;
}

void *hash_table_delete(hash_table *ht, const char *key){
    //can't be NULL key nor NULL object nor NULL hash table
    if(key == NULL || ht == NULL) return false;
    size_t index = hash_table_index(ht, key);

    entry *tmp = ht->elements[index];
    entry *prev = NULL;

    while(tmp != NULL && strcmp(tmp->key, key) != 0){
        prev = tmp;
        tmp = tmp->next;
    }
    if(tmp == NULL) return NULL;

    if(prev == NULL){
        //delete the head of the list
        ht->elements[index] = tmp->next;
    }
    else{
        //delete from somewhere not the head
        prev->next = tmp->next;
    }

    void *result = tmp->obj;
    free(tmp);
    return result;
}