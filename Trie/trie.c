#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NUM_CHAR 256

typedef struct trienode{
    struct trienode *children[NUM_CHAR];
    bool terminal;
} trienode;

trienode *createnode(){
    trienode *newnode = malloc(sizeof(* newnode));

    for (int i = 0; i < NUM_CHAR;i++){
        newnode->children[i] = NULL;
    }
    newnode->terminal = false;
    return newnode;
}

bool trieinsert(trienode **root, char *signedtext){
    if(*root == NULL){
        *root = createnode();
    }

    unsigned char *text = (unsigned char *)signedtext;
    trienode *temp = *root;
    int length = strlen(signedtext);

    for (int i = 0; i < length;i++){
        if(temp->children[text[i]] == NULL){
            temp->children[text[i]] = createnode();
        }
        temp = temp->children[text[i]];
    }
    if(temp->terminal){
        return false;
    }
    else{
        temp->terminal = true;
        return true;
    }
}

void printtrie_rec(trienode *node, unsigned char *prefix, int length){
    unsigned char newprefix[length + 2];
    memcpy(newprefix, prefix, length);
    newprefix[length + 1] = 0;

    if(node->terminal){
        printf("Word: %s\n", prefix);
    }

    for (int i = 0; i < NUM_CHAR;i++){
        if(node->children[i]!=NULL){
            newprefix[length] = i;
            printtrie_rec(node->children[i], newprefix, length + 1);
        }
    }
}

void printtrie(trienode *root){
    if(root == NULL){
        printf("Trie is empty!\n");
        return;
    }
    printtrie_rec(root, NULL, 0);
}

int main(){
    trienode *root = NULL;
    trieinsert(&root, "KIT");
    trieinsert(&root, "CATTLE");
    trieinsert(&root, "KIN");
    trieinsert(&root, "CAT");
    trieinsert(&root, "HAPPY");
    printtrie(root);
    return 0;
}