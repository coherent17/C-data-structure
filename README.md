# 資料結構筆記in C
---
*    堆疊(Stack)
*    佇列(Queue)
*    連結串列(Linke送一隻傳˙d list)
*    樹(Tree)
*    雜湊表(Hash table)

**目錄:**
[TOC]

## 堆疊(Stack):
堆疊是一種先進後出(FILO)-First In Last Out的資料結構，就像是將書堆在桌上一樣，會越堆越高，要拿取最底下那本書只能將上面的書都先移除，而後才能拿他。針對Stack有兩種作用方式，第一種是push，將元素加入這個堆中，第二種是pop，將元素從堆疊中移除。

### Array版:
缺點是一開始就要先訂好stack的長度，若要產生一個不知道多長的stack則需要使用linkedlist達成。

#### push():
為了要知道這個堆疊了多少，因此會使用一個變數$top$來紀錄到底堆了多少。一開始先設定$top=-1$，每當要push元素進入stack的時候，將$top+1$，將其放入$index=top+1$這個位置。

#### pop():
將最後放入堆疊的元素移出，因此返回$index=top$的元素，而後將$top-1$。那我們要如何知道已經pop到底了呢?設定一個在stack中不會用到的數字(ex:-2147283648)，當$top$已經見底$(top=-1)$的時候，將其回傳以表示stack已經被pop到底了。

#### Array版實作:
```c=
#include <stdio.h>
#include <stdbool.h>

#define STACK_LENGTH 5
#define EMPTY (-1)
#define INT_MIN (-2147483648)
#define STACK_EMPTY INT_MIN

int stack[STACK_LENGTH];
int top = EMPTY;

bool push(int value){
    if(top >= STACK_LENGTH-1) return false;

    top++;
    stack[top] = value;
    return true;
}

int pop(){
    if(top == EMPTY) return STACK_EMPTY;

    int reuslt = stack[top];
    top--;
    return reuslt;
}

int main(){
    push(56);
    push(78);
    push(13);

    int t;
    while((t=pop())!=STACK_EMPTY){
        printf("t = %d\n", t);
    }
    return 0;
}
```
code:https://github.com/coherent17/C-data-structure/blob/main/Stack/stack_array.c

編譯執行後可以發現這個stack pop出來的順序真的是FILO，輸出為: ![](https://i.imgur.com/EAe7YB2.png)

### Linkedlist版:
若是使用linkedlist來實作stack的話，對於每個元素的節點都需要去存放比該元素前一個放入的元素的記憶體位址，而head則是要持續更新為新加入節點的記憶體位址。

#### push():
在做push的時候需要先宣告一個記憶體空間，而後更新head的位址。更新方法如下:  
*    一開始初始化head = NULL
*    將newnode1->next = head = NULL
*    將head更新為newnode1
  
所以linkedlist變為 head - newnode1 - NULL   
再push一個:  
*    head = newnode1
*    newnode2->next = head = newnode1
*    將head更新為newnode2

所以linkedlist變為 head - newnode2 - newnode1 - NULL   

可以特別注意到最早進來的newnode1是被放在較靠近NULL的一端，而較晚進來的newnode2的記憶體位址則是被head所存。

#### pop():
因為head是存放最晚進來的node的位址，因此在pop的時候就直接將其位址指向的數值返還，而後將head改為該節點原本所指向的記憶體位址即可。

#### Linkedlist版實作:
```c=
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define EMPTY (-1)
#define INT_MIN (-2147483648)
#define STACK_EMPTY INT_MIN

typedef struct node{
    int value;
    struct node *next;
} node;

node *head = NULL;

bool push(int value){
    node *newnode = malloc(sizeof(node));
    newnode->value = value;
    newnode->next = head;
    head = newnode;
    return true;
}

int pop(){
    if(head==NULL)
        return STACK_EMPTY;

    int result = head->value;
    node *temp = head;
    head = head->next;
    free(temp);
    return result;
}

int main(){
    push(56);
    push(78);
    push(13);

    int t;
    while((t=pop())!=STACK_EMPTY){
        printf("t = %d\n", t);
    }
    return 0;
}
```
code:https://github.com/coherent17/C-data-structure/blob/main/Stack/stack_linkedlist.c

### 優化改良版:
由上面的兩隻程式皆可以發現都push及pop的功能僅限於全域的array或是linkedlist，若有多個stack，應該要多出能夠指定針對哪一個stack進行push或是pop的功能，因此需要再多傳一些參數進入push及pop的function內部，使其可以更好的針對"特定的"stack進行動作。

#### Array 優化改良版:
目標是要能夠針對特定的stack進行push與pop，因此建立一個struct，內部包含陣列及$top$這個變數，而後透過指標將stack這個struct的位址傳入function，便能夠執行針對特定的stack進型push及pop的動作了!

##### Array optimal版實作:
```c=
#include <stdio.h>
#include <stdbool.h>

#define STACK_LENGTH 5
#define EMPTY (-1)
#define INT_MIN (-2147483648)
#define STACK_EMPTY INT_MIN

typedef struct stack{
    int value[STACK_LENGTH];
    //initialize each top of the each stack in main
    int top;
}stack;

bool push(stack *s, int value){
    if(s->top >= STACK_LENGTH-1) return false;

    s->top++;
    s->value[s->top] = value;
    return true;
}

int pop(stack *s){
    if(s->top == EMPTY) return STACK_EMPTY;

    int reuslt = s->value[s->top];
    s->top--;
    return reuslt;
}

int main(){

    stack stack1, stack2, stack3;
    stack1.top = EMPTY;
    stack2.top = EMPTY;
    stack3.top = EMPTY;

    push(&stack1, 56);
    push(&stack1, 78);
    push(&stack1, 13);

    push(&stack2, 25);
    push(&stack2, 75);
    push(&stack2, 69);

    push(&stack3, 43);
    push(&stack3, 29);
    push(&stack3, 46);

    int t;
    while((t=pop(&stack2))!=STACK_EMPTY){
        printf("t = %d\n", t);
    }
    return 0;
}
```
code:https://github.com/coherent17/C-data-structure/blob/main/Stack/stack_array_optimal.c

#### Linkedlist 優化改良版:
目標是要在push或是pop的時候能夠更特定的指定是要push或pop到哪一個stack上，因此我們可以多傳入存放stack位址head的記憶體位址，我們可以透過指標的指標將欲指定stack的head的記憶體位址傳入function，而後透過$"*"$去dereference這個指標的指標，去更改head實際上存取節點位址。

##### Linkedlist optimal版實作:
```c=
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define EMPTY (-1)
#define INT_MIN (-2147483648)
#define STACK_EMPTY INT_MIN

typedef struct node{
    int value;
    struct node *next;
} node;


bool push(node **head, int value){
    node *newnode = malloc(sizeof(node));
    newnode->value = value;
    newnode->next = (*head);
    (*head) = newnode;
    return true;
}

int pop(node **head){
    if((*head) == NULL)
        return STACK_EMPTY;

    int result = (*head)->value;
    node *temp = (*head);
    (*head) = (*head)->next;
    free(temp);
    return result;
}

int main(){

    node *head1 = NULL;
    node *head2 = NULL;
    node *head3 = NULL;

    push(&head1, 56);
    push(&head1, 13);
    push(&head1, 12);

    push(&head2, 17);
    push(&head2, 19);
    push(&head2, 28);

    push(&head3, 26);
    push(&head3, 24);
    push(&head3, 32);

    int t;
    while((t=pop(&head2))!=STACK_EMPTY){
        printf("t = %d\n", t);
    }
    return 0;
}
```
code:https://github.com/coherent17/C-data-structure/blob/main/Stack/stack_linkedlist_optimal.c

## 佇列(Queue):
佇列是一種先進先出(FIFO)-First In First Out的資料結構。針對這種資料結構，可以進行兩種行為:在queue中增加元素稱為enqueue，而在queue中取出元素則稱為dequeue。此外，先enqueue進queue中的元素，會先被dequeue出來。

### Array版:
缺點是一開始就要先訂好queue的長度，若要產生一個不知道多長的queue則需要使用linkedlist達成。

#### enqueue():
為了要知道這個佇列存了多少東西，使用head與tail來持續追蹤。具體實踐如下:  
*    先將head與tail都初始化為-1
*    當enqueue第一個新元素進入queue之後，將其放入$index=tail+1$的位置
*    之後再enqueue新的元素也比照辦理，因此$tail+1$便是佇列中的元素個數

實作想法:
*    初始化head=-1, tail=-1
*    enqueue(3):  
        *  tail=0, array[tail]=3
    
        | index | -1/head | 0/tail |  1  | 2   |
        | ----- |:-------:|:------:|:---:| --- |
        | value |    X    |   3    |     |     |
        
*    enqueue(1):  
        *    tail=1, array[tail]=1
        
        | index | -1/head |  0  | 1/tail | 2   |
        | ----- |:-------:|:---:|:------:| --- |
        | value |    X    |  3  |   1    |     |
        
*    enqueue(4):  
        *    tail=2, array[tail]=4
        
        | index | -1/head |  0  |  1  | 2/tail |
        | ----- |:-------:|:---:|:---:|:------:|
        | value |    X    |  3  |  1  |   4    |

#### dequeue():
將最早放入佇列的元素移出，因此返回$index=head+1$的元素，而後將所有後面進來的元素都往前移一格。那我們要如何知道已經dequeue到底了呢?設定一個在queue中不會用到的數字(ex:-2147283648)，如果tail為-1，則回傳該數字，以表示這個佇列已經是空的了。

實作想法:
*    先進行enqueue(3), enqueue(1), enqueue(4)後，陣列為:  
        *    tail=2
        
        | index | -1/head |  0  |  1  | 2/tail |
        | ----- |:-------:|:---:|:---:|:------:|
        | value |    X    |  3  |  1  |   4    |
        
*    dequeue():
        *    回傳$index=head+1$的元素(3)，而後將後面所有元素往前移一格，tail-1
        
        | index | -1/head |  0  | 1/tail |  2  |
        | ----- |:-------:|:---:|:------:|:---:|
        | value |    X    |  1  |   4    |     |

#### Array版實作:
```c=
#include <stdio.h>
#include <stdbool.h>

#define QUEUE_LENGTH 5
#define EMPTY (-1)
#define INT_MIN (-2147483648)
#define QUEUE_EMPTY INT_MIN

int queue[QUEUE_LENGTH];
int tail = -1;
int head = -1;

bool enqueue(int value){
    if(tail >= QUEUE_LENGTH-1) return false;
    tail++;
    queue[tail] = value;
    return true;
}

int dequeue(){
    if(tail==EMPTY)
        return QUEUE_EMPTY;
    int result = queue[head+1];

    //shift all of the element forword
    for (int i = 1; i <= tail;i++){
        queue[i - 1] = queue[i];
    }
    tail--;
    return result;
}

int main(){
    enqueue(1);
    enqueue(4);
    enqueue(3);

    int t;
    while((t=dequeue())!=QUEUE_EMPTY){
        printf("t = %d\n", t);
    }
    return 0;
}
```
code:https://github.com/coherent17/C-data-structure/blob/main/Queue/queue_array.c

編譯執行後可以發現這個queue dequeue出來的順序真的是FIFO，輸出為: ![](https://i.imgur.com/bqwMjbi.png)

### Linkedlist版:
若是使用linkedlist來實作queue的話，需要使用兩個指標變數去追蹤queue的head及tail，

#### enqueue():
在做enqueue的時候需要先宣告一個記憶體空間，而後隨著新進來的元素去更新tail  

*    一開始初始化head = NULL, tail = NULL
*    宣告一個newnode1, 並設定newnode1->next = NULL
*    將head及tail更新為newnode1
  
所以linkedlist變為:   

*    head = newnode1, tail = newnode1, newnode1->next = NULL
*    
    | newnode1  | NULL |
    | --------- |:----:|
    | head tail |      |

再enqueue一個node:  
*    newnode2->next = NULL
*    tail->next = newnode2
*    tail = newnode2
*    
    | newnode1 | newnode2 | NULL |
    |:--------:|:--------:|:----:|
    |   head   |   tail   |      |

再enqueue一個node:  
*    newnode3->next = NULL
*    tail->next = newnode3
*    tail = newnode3
*    
    | newnode1 | newnode2 | newnode3 | NULL |
    |:--------:|:--------:|:--------:|:----:|
    |   head   |          |   tail   |      |

可以特別注意到最早進來的newnode1是被放在head端，而較晚進來的newnode3的則是被放在tail端，與stack相反。

#### dequeue():
因為head是存放最早進來的node的位址，因此在dequeue的時候就直接將其位址指向的數值返還，而後將head改為該節點原本所指向的記憶體位址即可。

#### Linkedlist版實作:
```c=
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define EMPTY (-1)
#define INT_MIN (-2147483648)
#define QUEUE_EMPTY INT_MIN

typedef struct node{
    int value;
    struct node *next;
} node;

node *head = NULL;
node *tail = NULL;

bool enqueue(int value){
    node *newnode = malloc(sizeof(node));
    newnode->value = value;
    newnode->next = NULL;

    //the first element add into the queue
    if(head == NULL && tail == NULL){
        head = newnode;
        tail = newnode;
    }

    //add the seoond or third node into the queue
    else{
        tail->next = newnode;
        tail = newnode;
    }
    return true;
}

int dequeue(){

    //check if the queue is empty
    if(head==NULL)
        return QUEUE_EMPTY;

    int result = head->value;
    node *temp = head;
    head = head->next;
    if(head==NULL){
        tail = NULL;
    }
    free(temp);
    return result;
}

int main(){
    enqueue(3);
    enqueue(6);
    enqueue(5);

    int t;
    while((t=dequeue())!=QUEUE_EMPTY){
        printf("t = %d\n", t);
    }
    return 0;
}
```
code:https://github.com/coherent17/C-data-structure/blob/main/Queue/queue_linkedlist.c

### 優化改良版:
由上面的兩隻程式皆可以發現都enqueue及dequeue的功能僅限於全域的array或是linkedlist，若有多個queue，應該要多出能夠指定針對哪一個queue進行enqueue或是dequeue的功能，因此需要再多傳一些參數進入enqueue及dequeue的function內部，使其可以更好的針對"特定的"queue進行動作。解決方法與stack的解決方法大同小異，對於array版，同樣也是包裝成struct，傳入位址即可解決，對於linkedlist版，將head及tail包裝好，傳入這個struct的位址，便能夠針對特定的queue進行enqueue及dequeue的動作了。

#### Array_optimal實作:
```c=
#include <stdio.h>
#include <stdbool.h>

#define QUEUE_LENGTH 5
#define EMPTY (-1)
#define INT_MIN (-2147483648)
#define QUEUE_EMPTY INT_MIN


typedef struct queue{
    int value[QUEUE_LENGTH];
    //initialize each head and tail in main
    int tail;
    int head;
} queue;

void init_queue(queue *q){
    q->head = EMPTY;
    q->tail = EMPTY;
}

bool enqueue(queue *q, int value){
    if(q->tail >= QUEUE_LENGTH-1) return false;
    q->tail++;
    q->value[q->tail] = value;
    return true;
}

int dequeue(queue *q){
    if(q->tail==EMPTY)
        return QUEUE_EMPTY;
    int result = q->value[q->head+1];

    //shift all of the element forword
    for (int i = 1; i <= q->tail;i++){
        q->value[i - 1] = q->value[i];
    }
    q->tail--;
    return result;
}

int main(){

    queue q1, q2, q3;
    init_queue(&q1);
    init_queue(&q2);
    init_queue(&q3);

    enqueue(&q1, 15);
    enqueue(&q1, 16);
    enqueue(&q1, 29);
    
    enqueue(&q2, 46);
    enqueue(&q2, 23);
    enqueue(&q2, 49);

    enqueue(&q3, 23);
    enqueue(&q3, 21);
    enqueue(&q3, 27);

    int t;
    while((t=dequeue(&q2))!=QUEUE_EMPTY){
        printf("t = %d\n", t);
    }
    return 0;
}
```
code:https://github.com/coherent17/C-data-structure/blob/main/Queue/queue_array_optimal.c

#### Linkedlist_optimal實作:
```c=
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define EMPTY (-1)
#define INT_MIN (-2147483648)
#define QUEUE_EMPTY INT_MIN

typedef struct node{
    int value;
    struct node *next;
} node;

typedef struct queue{
    //initialize in main
    node *head;
    node *tail;
} queue;

void init_queue(queue *q){
    q->head = NULL;
    q->tail = NULL;
}

bool enqueue(queue *q, int value){
    node *newnode = malloc(sizeof(node));
    newnode->value = value;
    newnode->next = NULL;

    //the first element add into the queue
    if(q->head == NULL && q->tail == NULL){
        q->head = newnode;
        q->tail = newnode;
    }

    else{
        q->tail->next = newnode;
        q->tail = newnode;
    }
    return true;
}

int dequeue(queue *q){

    //check if the queue is empty
    if(q->head==NULL)
        return QUEUE_EMPTY;

    int result = q->head->value;
    node *temp = q->head;
    q->head = q->head->next;
    if(q->head==NULL){
        q->tail = NULL;
    }
    free(temp);
    return result;
}

int main(){

    queue q1, q2, q3;
    init_queue(&q1);
    init_queue(&q2);
    init_queue(&q3);

    enqueue(&q1, 15);
    enqueue(&q1, 16);
    enqueue(&q1, 29);
    
    enqueue(&q2, 46);
    enqueue(&q2, 23);
    enqueue(&q2, 49);

    enqueue(&q3, 23);
    enqueue(&q3, 21);
    enqueue(&q3, 27);

    int t;
    while((t=dequeue(&q2))!=QUEUE_EMPTY){
        printf("t = %d\n", t);
    }
    return 0;
}
```
code:https://github.com/coherent17/C-data-structure/blob/main/Queue/queue_linkedlist_optimal.c

## 樹(Tree):
樹是一種非線性的資料結構，要在linkedlist或是array中尋找資料，從頭到尾整個找一次將會非常的耗費時間，若是使用tree的這種資料結構將能夠解決這種問題。若是未來在處理有層級的資料可以試著使用樹這個資料結構，或許能夠增快效率。

### 二元樹(binary tree):
對於這棵樹的任一節點，最多只有兩個分支。因此不像linkedlist僅需要去存放下一個節點的記憶體位址即可，需要兩個指標變數去存放左邊的分支與右邊的分支，而這棵樹內部可以依照需求放置不同的東西，可以放linkedlist,hash table, int, float, array，各種不一樣的元素都可以，這裡為求簡便先放置簡單的整數int來記錄。

#### 宣告節點:
因為需要去存放兩個分支的記憶體位置及該節點的數值，因此對於這種樹節點的宣告如下:
```c=
typedef struct node{
    int value;
    struct node *left;
    struct node *right;
} node;
```
可以看到對於這個節點的結構，我宣告了兩個指標變數以存取左右分支的節點位址。

#### 新增節點:
先初始化左右分之的節點都為NULL，在main中再串接，並返還該新節點的位址
```c=
node *createNode(int value){
    node *newnode = malloc(sizeof(node));
    newnode->value = value;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}
```

#### 串接節點:
在main中新增節點，並且將他們串接起來。
```c=
    node *node1 = createNode(5);
    node *node2 = createNode(6);
    node *node3 = createNode(7);
    node *node4 = createNode(8);
    node *node5 = createNode(9);

    node1->left = node2;
    node1->right = node3;
    node3->left = node4;
    node3->right = node5;
```

```
                                5
                               / \
                              6   7
                             / \ / \
                            x  x 8  9
```

#### 印出樹(以tab分層級):
希望能夠給予樹的根部，而後由左到右，由根部往葉子(Preorder)，先拜訪父節點再拜訪左右節點的方法將樹印出來，並且每往下一個層級多印一個tab鍵。
```c=
void printTabs(int numtabs){
    for (int i = 0; i < numtabs;i++){
        printf("\t");
    }
}

void printTreeRecursive(node *root, int level){
    if(root==NULL){
        printTabs(level);
        printf("---<empty>---\n");
        return;
    }

    printTabs(level);
    printf("value = %d\n", root->value);

    //recursive to print the branch of tree

    printTabs(level);
    printf("left\n");
    printTreeRecursive(root->left, level+1);

    printTabs(level);
    printf("right\n");
    printTreeRecursive(root->right, level+1);
    
    printTabs(level);
    printf("Done\n");
}

void printTree(node *root){
    printTreeRecursive(root, 0);
}
```
結果看起來像這樣:
```
value = 5
left
        value = 6
        left
                ---<empty>---
        right
                ---<empty>---
        Done
right
        value = 7
        left
                value = 8
                left
                        ---<empty>---
                right
                        ---<empty>---
                Done
        right
                value = 9
                left
                        ---<empty>---
                right
                        ---<empty>---
                Done
        Done
Done
```
從這邊已經可以大概看出樹的層級，那接下來來試著用樹來做搜尋吧。

#### binary tree:
```c=
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node *left;
    struct node *right;
} node;

node *createNode(int value){
    node *newnode = malloc(sizeof(node));
    newnode->value = value;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

void printTabs(int numtabs){
    for (int i = 0; i < numtabs;i++){
        printf("\t");
    }
}

void printTreeRecursive(node *root, int level){
    if(root==NULL){
        printTabs(level);
        printf("---<empty>---\n");
        return;
    }

    printTabs(level);
    printf("value = %d\n", root->value);

    //recursive to print the branch of tree

    printTabs(level);
    printf("left\n");
    printTreeRecursive(root->left, level+1);

    printTabs(level);
    printf("right\n");
    printTreeRecursive(root->right, level+1);
    
    printTabs(level);
    printf("Done\n");
}

void printTree(node *root){
    printTreeRecursive(root, 0);
}

int main(){

    node *node1 = createNode(5);
    node *node2 = createNode(6);
    node *node3 = createNode(7);
    node *node4 = createNode(8);
    node *node5 = createNode(9);

    node1->left = node2;
    node1->right = node3;
    node3->left = node4;
    node3->right = node5;

    printTree(node1);

    free(node1);
    free(node2);
    free(node3);
    free(node4);
    free(node5);

    return 0;
}
```
code: https://github.com/coherent17/C-data-structure/blob/main/Tree/basicTree.c

### 二元搜尋樹(binary search tree):
二元搜尋樹是一種便於搜尋的資料結構，對於任意節點而言，比該節點的父節點小的數值，將會被分配在該父節點左邊的分支，而比父節點大的數值，將會被分配在右邊的分支，透過這種分配的方法，能夠使我們在這種樹中搜尋元素只要依照大小便能夠去查找該元素是否在樹中。

#### 在二元搜尋樹中新增新元素:
來寫一個function能夠傳入樹的根部，而後能夠按照二元搜尋樹的規則將樹建立起來。所以在這個function會需要傳入的argument有根部節點的位址及要新增的數值，但是在一開始還沒新增任何元素進入樹的時候，根部這個指標不是指向一個新的節點而是被初始化指向NULL，而後我們會需要去更改這個根部指標將其改為存放新第一個被加入二元搜尋樹的節點的位址，因此一開始傳入根部行不通的，應該要傳入一個double pointer，指向根部，並且使用$"*"$去dereference，以將根這個指標變數從NULL改為存放某一節點的記憶體位址。在實作上，則是透過遞迴的方式，透過與父節點比大小，而將其分配到左邊的分支，或是右邊的分支。

```c=
bool insertNumber(node **rootptr, int value){
    node *root = (*rootptr);

    if(root==NULL){
        //the reason why we pass double pointer in the argument
        (*rootptr)=createNode(value);
        return true;
    }

    //if the element had been in the tree
    if(root->value==value){
        //do nothing
        return false;
    }

    //recursive to insert the number into tree
    else{
        if(value < root->value)
            return insertNumber(&(root->left), value);
        else
            return insertNumber(&(root->right), value);
    }
}
```

#### 在二元搜尋樹中尋找元素:
因為每次的比較都是分一半去搜尋，因此時間複雜度為$O(log(N))$，相比其他的資料結構，在搜尋演算法上效率高了不少。因為在做搜尋的時候並不會去更動到樹內部的數值，因此僅需要將根部節點的位址及要搜索的數值傳入即可，同樣也適用遞迴的方式去尋找該元素是否在這個樹中。

```c=
bool findNumber(node *root, int value){
    if(root==NULL)
        return false;
    if(root->value==value)
        return true;
    else{
        if(value < root->value)
            return findNumber(root->left, value);
        else
            return findNumber(root->right, value);
    }
}
```

#### binary search tree:
```c=
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
    int value;
    struct node *left;
    struct node *right;
} node;

node *createNode(int value){
    node *newnode = malloc(sizeof(node));
    newnode->value = value;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

/*
if the root of the tree is point to NULL, then we need to change the value of the root
therefore, we pass the double pointer to change the value of root
*/
bool insertNumber(node **rootptr, int value){
    node *root = (*rootptr);

    if(root==NULL){
        //the reason why we pass double pointer in the argument
        (*rootptr)=createNode(value);
        return true;
    }

    //if the element had been in the tree
    if(root->value==value){
        //do nothing
        return false;
    }

    //recursive to insert the number into tree
    else{
        if(value < root->value)
            return insertNumber(&(root->left), value);
        else
            return insertNumber(&(root->right), value);
    }
}

bool findNumber(node *root, int value){
    if(root==NULL)
        return false;
    if(root->value==value)
        return true;
    else{
        if(value < root->value)
            return findNumber(root->left, value);
        else
            return findNumber(root->right, value);
    }
}

void printTabs(int numtabs){
    for (int i = 0; i < numtabs;i++){
        printf("\t");
    }
}

void printTreeRecursive(node *root, int level){
    if(root==NULL){
        printTabs(level);
        printf("---<empty>---\n");
        return;
    }

    printTabs(level);
    printf("value = %d\n", root->value);

    //recursive to print the branch of tree

    printTabs(level);
    printf("left\n");
    printTreeRecursive(root->left, level+1);

    printTabs(level);
    printf("right\n");
    printTreeRecursive(root->right, level+1);
    
    printTabs(level);
    printf("Done\n");
}

void printTree(node *root){
    printTreeRecursive(root, 0);
}

int main(){

    node *root=NULL;

    insertNumber(&root, 85);
    insertNumber(&root, 100);
    insertNumber(&root, 26);
    insertNumber(&root, 71);
    insertNumber(&root, 1);
    insertNumber(&root, 4);
    insertNumber(&root, 3);
    insertNumber(&root, 2);
    insertNumber(&root, 5);
    insertNumber(&root, 16);
    insertNumber(&root, 24);
    insertNumber(&root, 8);
    insertNumber(&root, 96);
    insertNumber(&root, 17);

    printTree(root);

    printf("%d (%d)\n", 17, findNumber(root, 17));
    printf("%d (%d)\n", 4, findNumber(root, 4));
    printf("%d (%d)\n", 24, findNumber(root, 24));
    printf("%d (%d)\n", 98, findNumber(root,98));
    printf("%d (%d)\n",13, findNumber(root, 13));
    printf("%d (%d)\n", 25, findNumber(root, 25));


    return 0;
}
```
code:https://github.com/coherent17/C-data-structure/blob/main/Tree/binarySearchTree.c

結果:
```
value = 85
left
        value = 26
        left
                value = 1
                left
                        ---<empty>---
                right
                        value = 4
                        left
                                value = 3
                                left
                                        value = 2
                                        left
                                                ---<empty>---
                                        right
                                                ---<empty>---
                                        Done
                                right
                                        ---<empty>---
                                Done
                        right
                                value = 5
                                left
                                        ---<empty>---
                                right
                                        value = 16
                                        left
                                                value = 8
                                                left
                                                        ---<empty>---
                                                right
                                                        ---<empty>---
                                                Done
                                        right
                                                value = 24
                                                left
                                                        value = 17
                                                        left
                                                                ---<empty>---
                                                        right
                                                                ---<empty>---
                                                        Done
                                                right
                                                        ---<empty>---
                                                Done
                                        Done
                                Done
                        Done
                Done
        right
                value = 71
                left
                        ---<empty>---
                right
                        ---<empty>---
                Done
        Done
right
        value = 100
        left
                value = 96
                left
                        ---<empty>---
                right
                        ---<empty>---
                Done
        right
                ---<empty>---
        Done
Done
17 (1)
4 (1)
24 (1)
98 (0)
13 (0)
25 (0)
```

## 連結串列(Linked list):

### Why linked list?
若現在有一個陣列如下:

| index | 0   | 1   |  2  | 3   | 4   | 5   |  6  |
|:-----:| --- | --- |:---:| --- | --- | --- |:---:|
| value | 15  | 28  | 24  | 18  | 3   | 45  | 98  |

若想要在陣列的尾端新增元素是蠻輕鬆簡單的，但是倘若要在$index=4$跟$5$之間插入新的元素，那就變難了，要將原本陣列中$index=5$跟$6$的元素都往後移才能插入，因此這樣效率會變得很差，若資料數有很多筆，那麼將會花很多時間在做這類的copy和paste的動作，因此我們引入連結串列(Linked list)這種資料結構，來解決這個問題。簡略上來說，就是宣告記憶體來存我需要存的變數，並且給予一個指標，指向下一個元素，如此一來，便能輕鬆的插入變數或是更改元素間的順序了!

### 實作想法:
假設現在有三個元素要放入陣列:node1、node2、node3，分別存在或許不連續的記憶體位址，但是若要將其變為陣列，他們的記憶體位址將是連續的，因此我們可以先宣告一個$struct$存放元素的數值，及指標。而這個指標是指向將要放在陣列中下一個元素的記憶體位址，如此一來，我們便能夠串接了3個原本各自存放在不同記憶體位址的元素了。假如我現在想要增加一個新的元素node4在node2與node3之間，我只需要將node2這個元素的下一個指標指向node4這個記憶體位址，再將node4這個記憶體指標指向node3這個元素的記憶體位址，因此可以省去不少copy和paste動作的時間。

### 建立struct:
對於每個元素，我們都需要存放它的數值及存放下一個數值的記憶體位址，因此對於每一個節點，我們需要宣告一個struct如下:
```c=
struct nodes{
    int value;
    struct nodes *next;
};
//avoid typing struct many times
typedef struct nodes node;
```

### 實作串接:
為了知道這串linkedlist的起點為何，可以宣告一個指向node這個結構變數的指標為head，如此一來，我們便可以透過head來了解這串linkedlist的起點，而可以將這串linkedlist最後的一個元素中的指標指向NULL，以此判別該linkedlist已經結束。
```c=
#include<stdio.h>

struct nodes{
    int value;
    struct nodes *next;
};

typedef struct nodes node;

void printList(node *);

int main(){
    node node1, node2, node3;
    node *head; //point to the head of the linkedlist

    
    node1.value=128;
    node2.value=64;
    node3.value=45;

    //link them into the chain: head -> node1 -> node2 -> node3 -> NULL
    head=&node1;
    node1.next=&node2;
    node2.next=&node3;
    node3.next=NULL;

    //print them out
    printList(head);

    return 0;
}

void printList(node *head){
    node *temp=head;
    printf("head - ");
    while(temp!=NULL){
        printf("%d - ",temp->value);
        temp=temp->next;
    }
    printf("NULL\n");
}
```
結果: ![](https://i.imgur.com/06fxDaC.png)



### 實作插入:
假如我們想要在node2跟node3裡面加入新的節點為node_to_insert，那要如何做呢?我們可以宣告一個新的節點，給他數值之後，將node2指向他，而將自己的節點指向node3即可。如下:
```c=
    node node_to_insert;
    node_to_insert.value=17;
    node2.next=&node_to_insert;
    node_to_insert.next=&node3;
```
結果: ![](https://i.imgur.com/eZliBLv.png)


但是事實上，我們在使用linkedlist的時候，可能並不會知道會使用多少節點，因此我們需要將其發展推廣，並寫成函式，以方便後續的使用。

### 模組化功能:
*    新增節點
*    從串列的頭部新增節點
*    從串列的尾端新增節點
*    尋找節點
*    在某節點後插入節點
*    刪除節點
*    有多少節點
*    排序節點
*    陣列存取
*    [尋找串列中間的節點](https://leetcode.com/problems/middle-of-the-linked-list/)(Leetcode)

---
#### 新增節點:
在這個函式中，我想要新增加一個node，並給定他數值，並指定這個節點先暫時指向NULL，待我稍後使用，而最終要回傳這個節點的記憶體位址，以供後續將其插入linkedlist或其他功能使用。
```c=
node *create_node(int value){
    node *temp=malloc(sizeof(node));
    temp->value=value;
    temp->next=NULL;
    return temp;
}
```
Driven code:
```c=
int main(){
    node *head=NULL; 
    node *temp;

    temp=create_node(128);
    head=temp;

    temp=create_node(64);
    temp->next=head;
    head=temp;

    temp=create_node(17);
    temp->next=head;
    head=temp;

    temp=create_node(45);
    temp->next=head;
    head=temp;

    //print them out
    printList(head);

    return 0;
}
```
我先新增了一個節點(128)，而後將head指向他的位址，因此目前為head - 128，而後我再新增了一個節點(64)，而後我將64的這個節點指向128，再將head指向64的位址，因此串列變為head - 64 - 128，以此類推， 因此較晚進來這個陣列的元素，會被排在比較靠近head的地方。因此輸出如下:  
![](https://i.imgur.com/gGVLWAk.png)

透過上面的程式碼，可以看到一直在做重複的事情:(新增元素，然後將其指向前一個元素，而後更新head)，我們將其寫為一個函式:

---
#### 從串列的頭部新增節點:
在這個函式中，要做到的事為將新的節點接上舊的head，而後更新節點。因此我們需要舊的head和要插入的節點。而後將新的head回傳。
```c=
node *insert_at_head(node *head, node* node_to_insert){
    node_to_insert->next=head;
    head=node_to_insert;
    return head;
}
```
也可以趁機練習一下指標，用pointer to pointer來更改head指向的位址，便不用回傳head了。
```c=
void *insert_at_head(node **head, node* node_to_insert){
    node_to_insert->next=*head;
    *head=node_to_insert;
}
```
Driven code:
```c=
int main(){
    node *head=NULL; 
    node *temp;

    for(int i=0;i<20;i++){
        temp=create_node(i);
        insert_at_head(&head, temp);
    }

    //print them out
    printList(head);

    return 0;
}
```
結果:![](https://i.imgur.com/a4ZrHX7.png)

#### 從串列的尾端新增節點:
按照指標的順序一直往後找，在最後一個節點和NULL之間插入該節點即可。
```c=
void insert_at_tail(node *head, node *node_to_insert){
    node *temp=head;
    while(temp!=NULL){
        if(temp->next==NULL) break;
        temp=temp->next;
    }
    temp->next=node_to_insert;
    node_to_insert->next=NULL;
}
```
Driven code:
```c=
int main(){
    node *head=NULL; //point to the head of the linkedlist
    node *temp;

    for(int i=0;i<20;i++){
        temp=create_node(i);
        insert_at_head(&head, temp);
    }
    printList(head);
    
    insert_at_tail(head, create_node(100));
    printList(head);
    return 0;
}
```
結果:![](https://i.imgur.com/h6X3yxL.png)


---
#### 尋找節點:
在這個函式中，我們想要查詢該串列是否有特定元素在裡面，所以就照著指標走訪各個元素。
```c=
node *find_node(node *head, int value){
    node *temp=head;
    while(temp!=NULL){
        if(temp->value==value){
            printf("Found %d at %p\n", temp->value, &temp->value);
            return temp;
        }
        temp=temp->next;
    }
    //if the element can't be found in the linkedlist
    printf("Not found %d in the linkedlist\n", value);
    return NULL;
}
```
Driven code:
```c=
int main(){
    node *head=NULL; 
    node *temp;

    for(int i=0;i<20;i++){
        temp=create_node(i);
        insert_at_head(&head, temp);
    }

    //print them out
    printList(head);

    //find the element in the node:
    find_node(head, 13);
    find_node(head, 20);

    return 0;
}
```
結果:![](https://i.imgur.com/9pLEvQt.png)

---
#### 在某節點後插入節點:
在這個函式中，需要在該串列中指定的元素(node_to_insert_after)後面插入新的節點(new_node)，因此我們只要將新的節點(new_node)指向(node_to_insert_after)原本指向的節點，再將(node_to_insert_after)指向的節點改為(new_node)即可。
```c=
void insert_after_node(node *node_to_insert_after, int new_node_value){
    node *new_node=create_node(new_node_value);
    new_node->next=node_to_insert_after->next;
    node_to_insert_after->next=new_node;
}
```
Driven code:
```c=
int main(){
    node *head=NULL; 
    node *temp;

    for(int i=0;i<20;i++){
        temp=create_node(i);
        insert_at_head(&head, temp);
    }

    //insert 26 after 17
    insert_after_node(find_node(head,17),26);

    //print them out
    printList(head);
    return 0;
}
```
結果:![](https://i.imgur.com/paiNFQW.png)

---
#### 刪除節點:
找到欲刪除節點的前一個節點，將其跳過想要刪掉的那個節點，直接跳過他，指向下一個元素即可。
```c=
void delete_node(node *head, int value){
    node *temp=head;
    while(temp->next!=NULL){
        if(temp->next->value==value){
            temp->next=temp->next->next;
        }
        temp=temp->next;
    }
}
```
Driven code:
```c=
int main(){
    node *head=NULL; 
    node *temp;

    for(int i=0;i<20;i++){
        temp=create_node(i);
        insert_at_head(&head, temp);
    }

    printf("Before:\n");
    printList(head);

    //delete 6
    delete_node(head, 6);

    //print them out
    printf("After:\n");
    printList(head);
    return 0;
}
```
結果:
![](https://i.imgur.com/VTGl6gt.png)

---
#### 有多少節點:
按照指標循序計算，便可得知有多少個節點。
```c=
int number_of_node(node *head){
    node *temp=head;
    int count=0;
    while(temp!=NULL){
        count+=1;
        temp=temp->next;
    }
    return count;
}
```
Driven code:
```c=
int main(){
    node *head=NULL; 
    node *temp;

    for(int i=0;i<20;i++){
        temp=create_node(i);
        insert_at_head(&head, temp);
    }

    printList(head);
    
    printf("There are %d nodes in the linkedlist\n", number_of_node(head));
    return 0;
}
```
結果![](https://i.imgur.com/dR2baH2.png)

---
#### 排序節點:
使用最簡單的[bubblesort](https://hackmd.io/@VSCwqJYJSXeRPkfDpYnbnQ/Sy79MIyju#%E6%B0%A3%E6%B3%A1%E6%8E%92%E5%BA%8F%E6%B3%95Bubble-Sort)來進行，依序拜訪，若排序較後面的元素較小，則與前面交換。
```c=
void sortList(node *head){
    node *i, *j;
    for(i=head;i->next!=NULL;i=i->next){
        for(j=i->next;j!=NULL;j=j->next){
            if(i->value > j->value){
                int exchange_temp=j->value;
                j->value=i->value;
                i->value=exchange_temp;
            }
        }
    }
}
```
Driven code:
```c=
int main(){
    node *head=NULL; 
    node *temp;

    for(int i=0;i<20;i++){
        temp=create_node(i);
        insert_at_head(&head, temp);
    }

    printf("Before\n");
    printList(head);

    sortList(head);
    printf("After sorting:\n");
    printList(head);
    return 0;
}
```
結果:![](https://i.imgur.com/8NUMtyy.png)

---
#### 陣列存取:
malloc一段連續記憶體空間，將其存為陣列輸出，並且直接透過指標傳回在main()中，陣列的長度。
```c=
int *list_to_array(node *head, int *returnSize){
    node *temp=head;
    int *array=malloc(sizeof(node)*number_of_node(head));
    *returnSize=0;
    while(temp!=NULL){
        array[*returnSize]=temp->value;
        *returnSize+=1;
        temp=temp->next;
    }
    return array;
}
```
Driven code:
```c=
int main(){
    node *head=NULL; 
    node *temp;

    for(int i=0;i<20;i++){
        temp=create_node(i);
        insert_at_head(&head, temp);
    }

    printList(head);
    int length;
    int *array=list_to_array(head, &length);

    printf("Array:\n");
    for(int i=0;i<length;i++){
        printf("%d ", array[i]);
    }

    return 0;
}
```
結果:![](https://i.imgur.com/q3Vo38u.png)

---
#### 尋找串列中間的節點:
這是在Leetcode上面看到的題目，想要在串列中找到正中間的節點，並回傳他的位址。採用雙指標的方法，將比較慢的指標設為head，而較快的指標設為head的下一個，如此一來，快的走兩步，慢的走一步，當快的抵達結尾(NULL)的時候，慢的剛好就在中點了。
```c=
node *middleNode(node *head){
    node *slow_pointer=head;
    node *fast_pointer=head->next;
    while(fast_pointer!=NULL){
        //fast pointer move one step
        fast_pointer=fast_pointer->next;
        if(fast_pointer!=NULL){
            //slow pointer move one step
            slow_pointer=slow_pointer->next;
            //fast pointer move second step
            fast_pointer=fast_pointer->next;
        }
    }
    return slow_pointer;
}
```
Driven code:
```c=
int main(){
    node *head=NULL; 
    node *temp;

    for(int i=0;i<20;i++){
        temp=create_node(i);
        insert_at_head(&head, temp);
    }

    printList(head);

    printf("The middle node of the linkedlist is %d\n", middleNode(head)->value);

    return 0;
}
```
結果:![](https://i.imgur.com/ACPJoBK.png)

whole C code:  
https://github.com/coherent17/C-data-structure/blob/main/Linked%20List/linkedlist_functional_optimal.c

### 實作project:
有了上面的這些知識後，我便動手開始自己寫一個project，並且增加各種功能，讓我不僅對串列，更對指標有了更進一步的認識。那這次的struct就訂得複雜一點，有字串，整數，浮點數，及重要的指標變數以存取下一個元素的位址。如下:
```c=
struct data{
    char name[15];
    int age;
    float height;
    float weight;
    struct data *next;
};
```
為了將這這個linkedlist練習得好，我在這個project裡面要做到以下11件事:
*    1. 可以新增個人的資料(預設插入在尾部)
*    2. 可以印出所有的linkedlist
*    3. 能夠插入資料，不管是插在頭、尾，抑或是插在特定的人之後
*    4. 能夠刪除資料
*    5. 能夠查看資料
*    6. 能夠修改已在串列中的資料屬性
*    7. 能夠計算在linkedlist中有多少人
*    8. 以年齡排序
*    9. 以身高排序
*    10. 以體重排序
*    11. 將linkedlist匯出成txt檔

#### menu:
製作一個使育者介面，告知使用者如何使用這個系統，日後放在EOF的迴圈中，因此以Ctrl+z結束:
```c=
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
```
執行後看起來格式如右圖:
![](https://i.imgur.com/8hLVWzo.png)

#### 可以新增個人的資料(預設插入在尾部):
這邊讓使用者新增人員資料進入串列，並且預設插入在尾部，因此先寫一個函式，讀取該人的資料，並回傳他的位址，再將其插入陣列的尾部即可，那這邊要注意的是，假如是第一次新增這個資料，會需要更動head所指向的位址，因此使用pointer to pointer來更改他的值:
```c=
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
```

#### 可以印出所有的linkedlist:
就簡單的從頭到NULL掃一次，並且印出所有人的所有屬性，包括名字，年齡，身高，體重，這邊要注意的點是，假如使用者還未新增任何人進入linkedlist，必須要先告知其使用上面第一步來新增人員資料進入串列。
```c=
void print_personal_data(person *temp){
    printf("%-8s: %s\n","Name",temp->name);
    printf("%-8s: %d\n","Age",temp->age);
    printf("%-8s: %.1f\n","Height",temp->height);
    printf("%-8s: %.1f\n","Weight",temp->weight);
    printf("\n");
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
```
執行後看起來如右圖:
![](https://i.imgur.com/rPM0z3h.png)

#### 能夠插入資料，不管是插在頭、尾，抑或是插在特定的人之後:
就分別寫三個函式，分別是插在頭、尾，抑或是插在特定的人之後，再用一個函式將其包起來，給使用者決定要使用何種插入法。也要注意，若此linkedlist還是空的，必須先請使用者加入資料，再進行插入。
```c=
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
```

#### 能夠刪除資料:
這個功能讓使用者輸入名字，以刪除在串列中該人的資料，在這個函式中，要注意的重點比較多:  
*    1. 若為空串列，先請使用者新增資料進入。
*    2. 若被刪除的人為head所指向的人，那麼head將要指向下一個人，也就是說在這個情況，head的值可能會更改，因使使用pointer to pointer以更改head的值。
*    3. 因為前面是用malloc要求記憶體空間的，因此刪除後，要使用free()，以釋放該節點的記憶體空間。
```c=
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
```

#### 能夠查看資料:
能夠用名字去查詢該人的屬性。
```c=
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
```

#### 能夠修改已在串列中的資料屬性:
透過名字定位到該人，將其所有屬性全部從新讀進一遍，更新屬性的資料。
```c=
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
```

#### 能夠計算在linkedlist中有多少人:
單純從head走到NULL，計算該串列中存放了多少筆的資料:
```c=
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
```

#### 以年齡,身高,體重排序:
先寫三種型態(int, float, char)的交換函式，再使用bubblesort來針對特定得屬性排序
```c=
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
```

#### 將linkedlist匯出成txt檔:
以pointer to file的形式，並用fprintf寫入檔案，將其匯出。
```c=
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
```

#### driven code:
最後在main中，用switch case使用上面寫好的函式。
```c=
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
```
完整的程式碼(C code):https://github.com/coherent17/C-data-structure/blob/main/Linked%20List/personal_data_linkedlist_project.c

## 雜湊表(Hash table):
若要在陣列中搜尋該數值所對應的索引，以$linear\ search$的時間複雜度為$O(n)$，若是改用$binary\ search$則可以降至$O(logN)$，但是當$N$很大時，$O(logN)$仍然很可觀，因此可以用空間換取時間的$Hash\ Table$的方法，便可以將時間複雜度降至$O(1)$。

### 實作方式:
大致上需要一個$hash\ function$將$input$轉為$index$，將其存進$array[index]$中，舉例說明，假如有一個$struct$如下:  
```c=
typedef struct{
    char name[MAX_NAME];
    int age;
}person;
```
目的是要讀取$person$的名字，透過$hash\ function$將其轉為一個數字$index$，存進名為$hash\_table$的陣列中索引為$index$的地方。  

---
### Hash function:
*    對於一樣的$input$需要永遠返回同樣的索引
*    $Hash\ function$需很快，目的為減少時間複雜度，可直接在$hash\_table[hash(intput)]$找到值
*    $Hash\ function$的運算結果要是很隨機的

#### 建立Hash function:
前情提要:
```c=
//回傳str不包括'\0'的長度，若長度大於max_length，則回傳max_length
int strnlen(char *str, int max_length)
```
使用名字每個字母的$ACSII$碼進行運算，再$mod\ Hash\_Table$的大小(確保回傳值是在$Hash\_table$的大小內)當成$Hash\ function$的回傳值，剛好在看絕命毒師，就借用一下主角的名字了。
```c=
#include <stdio.h>
#include <string.h>
#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct{
    char name[MAX_NAME];
    int age;
}person;

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

int main(){
    printf("Walt -> %u\n",hash("Walt"));
    printf("Skyler -> %u\n",hash("Skyler"));
    printf("Saul -> %u\n",hash("Saul"));
    printf("Mike -> %u\n",hash("Mike"));
    printf("Hank -> %u\n",hash("Hank"));
    printf("Mary -> %u\n",hash("Mary"));
    return 0;
}
```
![](https://i.imgur.com/cDVVCLo.png)


編譯後可以看到這6個名字都可以分別對應到不重複的index，且每次的執行結果皆相同，但是倘若以更多人呢?可能會發生不同名字經過$Hash\ function$計算後卻得到相同的$index$，如"Mary"及"Holy"這兩個名字，那麼便會出現衝突，我們稍後再來談論解決方式。

---
### 建立Hash Table:
```c=
person *hash_table[TABLE_SIZE];
```
為甚麼要用指標陣列呢?  
*    不需要完整的空間，除非這個陣列是被填滿的。
*    可以透過指標去確認該位置是否有東西，可以初始化這個陣列為NULL，可以方便日後去確認此記憶體位址是否有東西佔據了。

#### 初始化指標陣列為NULL及印出hash table:
```c=
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
        //something in the hash table
        else printf("\t%d\t%s\n",i,hash_table[i]->name);
    }
    printf("---End-----\n");
}
```
在main中呼叫這兩個函式:
```c=
int main(){
    init_hash_table();
    print_table();
    return 0;
}
```
![](https://i.imgur.com/L6yY60c.png)
從編譯結果可以看出在初始化$Hash\_table$為NULL後，可以看到內部記憶體位址是尚未被佔領的。

---
### 將元素放入Hash Table:
```c=
//insert the element into the hash_table
bool hash_table_insert(person *p){
    //make sure not call this function with null ptr
    if(p==NULL) return false;

    //insert the person into the index return by hash_function
    int index=hash(p->name);
    //check the pointer at that index in the table is null or not
    if(hash_table[index]!=NULL) return false; //collision, somebody had occupied there already
    
    //if no one occupied there, then occupied the address
    hash_table[index]=p;
    return true;
}
```
在main使用這個函式，將$person$的位址傳入$hash\_table$
```c=
int main(){

    init_hash_table();

    person Walt={.name="Walt",.age=26};
    person Skyler={.name="Skyler",.age=27};
    person Saul={.name="Saul",.age=28};
    person Mike={.name="Mike",.age=29};
    person Hank={.name="Hank",.age=30};
    person Mary={.name="Mary",.age=31};

    //add person into hash_table
    hash_table_insert(&Walt);
    hash_table_insert(&Skyler);
    hash_table_insert(&Saul);
    hash_table_insert(&Mike);
    hash_table_insert(&Hank);
    hash_table_insert(&Mary);

    print_table();
    return 0;
}
```
![](https://i.imgur.com/PLyvnJV.png)
從編譯結果可以看到這6個名字經過$hash\ function$計算後，都得到不同的$index$，因此他們各在$hash\_table$中占據了他們的記憶體位址。

---
### 查看名字是否出現在Hash_Table:
想要快速的查看名字是否出現在$hash\_table$中，若有出現，則回傳指向那個人的指標，若沒有，則回傳NULL。
前情提要:
```c=
//string s1 compare with string s2 in length of n
//if return 0, means s1 equal to s2
int strncmp(char *s1, char *s2, int n);
```
```c=
//want to look up whether the person is in hash_table
//if not, return null, if yes, return the pointer to the person
person *hash_table_lookup(char *name){
    int index=hash(name);
    if(hash_table[index]!=NULL && strncmp(name,hash_table[index]->name,MAX_NAME)==0){
        return hash_table[index];
    } 
    else return NULL;
}
```
在main使用這個函式，看看該人是否在$hash\_table$中。
```c=
int main(){

    init_hash_table();

    person Walt={.name="Walt",.age=26};
    person Skyler={.name="Skyler",.age=27};
    person Saul={.name="Saul",.age=28};
    person Mike={.name="Mike",.age=29};
    person Hank={.name="Hank",.age=30};
    person Mary={.name="Mary",.age=31};

    
    //add person into hash_table
    hash_table_insert(&Walt);
    hash_table_insert(&Skyler);
    hash_table_insert(&Saul);
    hash_table_insert(&Mike);
    hash_table_insert(&Hank);
    hash_table_insert(&Mary);

    //check whether the person is in the hash_table
    person *tmp=hash_table_lookup("Walt");
    if(tmp==NULL) printf("Not Found!\n");
    else printf("Found %s at %p\n",tmp->name,tmp);

    tmp=hash_table_lookup("Junior");
    if(tmp==NULL) printf("Not Found!\n");
    else printf("Found %s at %p\n",tmp->name,tmp);

    return 0;
}
```
![](https://i.imgur.com/N2LXuLd.png)
從編譯結果可以看到Walt有在$hash\_table$中，而Junior則沒有。另外在$hash\_table\_lookup$這個函式中可以發現並沒有使用迴圈去找該名字是否出現在$hash\_table$中，而是直接透過$hash\ function$的計算後，直接尋找$hash\_table$的那個$index$是否為該人，因此不論放了多少人進$hash\_table$中，其運算速度都是一樣的，因此其時間複雜度為$O(1)$，

---
### 刪除在Hash_Table的人:
想要將已經在$hash\_table$內的人移除，將其位址改為NULL即可
```c=
//want to delete the person in the hash_table
//if delete, return the address of that guy, and let that pointer become NULL
person *hash_table_delete(char *name){
    int index=hash(name);
    if(hash_table[index]!=NULL && strncmp(name,hash_table[index]->name,MAX_NAME)==0){
        person *tmp=hash_table[index];
        hash_table[index]=NULL;
        return tmp;
    } 
    else return NULL;
}
```
在main使用這個函式，看看該人是否消失在$hash\_table$中。
```c=
int main(){

    init_hash_table();

    person Walt={.name="Walt",.age=26};
    person Skyler={.name="Skyler",.age=27};
    person Saul={.name="Saul",.age=28};
    person Mike={.name="Mike",.age=29};
    person Hank={.name="Hank",.age=30};
    person Mary={.name="Mary",.age=31};

    
    //add person into hash_table
    hash_table_insert(&Walt);
    hash_table_insert(&Skyler);
    hash_table_insert(&Saul);
    hash_table_insert(&Mike);
    hash_table_insert(&Hank);
    hash_table_insert(&Mary);

    //check whether the person is deleted
    print_table();
    printf("\n");
    hash_table_delete("Walt");
    print_table();

    return 0;
}
```
![](https://i.imgur.com/uuBo8WS.png)$\qquad \qquad\qquad\qquad\qquad$![](https://i.imgur.com/LeO0X2E.png)
透過編譯結果可以看到Walt已經從$hash\_table$中移除了，在$index=6$的地方已經沒有Walt了。

---
### 處理hash到同一個index的問題:
但是到目前為止，我們都還沒處理當不同名字透過$hash\ function$計算後得到相同$index$的案子。
我們多加一些人，製造衝突，看看結果會怎樣?
```c=
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

    return 0;
}
```
![](https://i.imgur.com/WniY8A9.png)$\qquad \qquad\qquad\qquad\qquad$![](https://i.imgur.com/jGqnNcJ.png)
從編譯結果可以看出Mike和Todd經過$hash\ function$之後皆得到0，而Mary及Holy經過$hash\ function$之後皆得到5，因此在插入$hash\_table$的時候，發現Todd及Holy沒有被插入，造成資料沒有成功儲存的錯誤。
#### **Solution I: linear probing**
另外，我們可以看到其實$hash\_table$還有部分空間沒有填滿，何不利用這些位置放置那些尚未被放入的$person$呢?若該名字經過$hash\ function$之後所得到的位址已經被別人所佔據，則我們直接檢查隔壁的位址是否被佔據，一直檢查隔壁的，直到找到空的記憶體位址可以插入該$person$。但是有可能找遍了整個$hash\_table$發現全部都被填滿了，那就沒辦法了。

這邊特別定義一個位址讓被刪除過後的pointer指向他，與尚未被放置過$person$位址的NULL有所區別:  
example: 若hash("d")=2，但在$index=2$的地方已經被c所佔據，且c被刪除過，此時記憶體位置會被紀錄為(0xFFFFFUL)所以d可能會出現在2以外的位子。但是當遇到NULL的話，表示d一定不會出現在$hash\_table$裡面。
```bash=
0 -> a
1 -> b
2 -> (0XFFFFFUL)
3 -> d
```
```c=
//define address of the pointer if the element has been deleted
#define DELETED_NODE (person *)(0xFFFFFUL) 
```
##### Open addressing-Linear probing C code:
```c=
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
```
經過$hash\ function$後所計算出來的$index$:$\qquad$![](https://i.imgur.com/vxBhQ7m.png)
經過$hash\_table\_insert$($linear\ probing$)之後，都被放到$hash\_table$了:$\qquad$![](https://i.imgur.com/sMNpJPy.png)

把Walt透過$hash\_table\_delete$前後使用$hash\_table\_lookup$的結果:

![](https://i.imgur.com/RdKoeEZ.png)

將Walt刪除後，以$print\_table$印出整個$hash\_table$，可以發現原本在$index=6$的Walt被刪除了:

$\qquad\qquad\qquad\qquad\qquad\qquad$![](https://i.imgur.com/fKpr4T3.png)

##### 小結論:
對於使用linear probing這種方式處理collision的問題，可以發現:
*    $table\_size$並不會改變，一個位址存放一個$person$的位址
*    $hash\_table$的優點:效率高不再成立了，因為使用許多迴圈去尋找該$person$，而非直接透過$hash\ function$直接鎖定該$person$位址存放的$index$
*    若$hash\ function$產生的$index$不夠隨機，那使用這種方法效率極差

#### **Solution II: external chain**
為了要解決$hash\ function$ $hash$到同一個$index$的問題，我們可以將其改為$linkedlist$以解決這個問題，從頭部新增該節點。因為$hash\_table$為指標陣列，可以將其內部所有的指標當成$linkedlist$的起始點，若$hash$到同一個$index$則串接該$index$上的$linkedlist$。
```c=
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
```
code: https://github.com/coherent17/C-data-structure/blob/main/Hash%20Table/hashtable_external_chain.c

