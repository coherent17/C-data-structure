#include "hashtable.h"
#include <stdio.h>
#include <string.h>

#define MAX_LINE 4096

uint64_t hash(const char *name, size_t length){
    uint64_t hash_value = 0;
    for(int i = 0; i < length; i++){
        hash_value += name[i];
        hash_value = hash_value * name[i];
    }
    return hash_value;
}

void generate_random_words(char *buffer, size_t length){
    for(size_t i = 0; i < length - 1; i++){
        buffer[i] = 'a' + (rand() % 26);
    }
    buffer[length-1] = 0;
}

int main(int argc, char **argv){
    if(argc != 3){
        printf("usage: %s <wordlist filename> <num gusses>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *filename = argv[1];
    uint32_t num_guesses = atol(argv[2]);

    //1 << 20 == 1048576, has 1 Mega Entry
    const int tablesize = (1<<20);
    hash_table *table = hash_table_create(tablesize, hash);

    FILE *fp = fopen(filename, "r");
    char buffer[MAX_LINE];
    uint32_t numwords = 0;
    while(!feof(fp) && fgets(buffer, MAX_LINE, fp) != NULL){
        buffer[strcspn(buffer, "\n\r")] = 0;

        //dynamic allocate memory for void *obj
        char *newentry = malloc(strlen(buffer) + 1);
        strcpy(newentry, buffer);
        hash_table_insert(table, buffer, newentry);
        numwords++;
    }
    fclose(fp);
    printf("Loaded %d words into the table.\n", numwords);
    
    //hash_table_print(table);

    //make some guesses
    uint32_t good_guesses = 0;
    const int shortest_guess = 2;
    const int longest_guess = 15;
    for(uint32_t i = 0; i < num_guesses; i++){
        generate_random_words(buffer, shortest_guess + rand() % (longest_guess - shortest_guess));
        if(hash_table_lookup(table, buffer)){
            good_guesses++;
        }
    }

    printf("%u out of %u guesses were in the table\n", good_guesses, num_guesses);
    hash_table_destroy(ht);
    return 0;
}