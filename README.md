# 資料結構筆記in C
---
*    連結串列(Linked list)
*    雜湊表(Hash table)

## 連結串列(Linked list):

### Why linked list?
若現在有一個陣列如下:

| index | 0   | 1   |  2  | 3   | 4   | 5   |  6  |
|:-----:| --- | --- |:---:| --- | --- | --- |:---:|
| value | 15  | 28  | 24  | 18  | 3   | 45  | 98  |

若想要在陣列的尾端新增元素是蠻輕鬆簡單的，但是倘若要在$index=4$跟$5$之間插入新的元素，那就變難了，要將原本陣列中$index=5$跟$6$的元素都往後移才能插入，因此這樣效率會變得很差，若資料數有很多筆，那麼將會花很多時間在做這類的copy和paste的動作，因此我們引入連結串列(Linked list)這種資料結構，來解決這個問題。簡略上來說，就是宣告記憶體來存我需要存的變數，並且給予一個指標，指向下一個元素，如此一來，便能輕鬆的插入變數或是更改元素間的順序了!

### 實作想法:
假設現在有三個數字:1、2、4，分別存在不連續的記憶體位址，但是若要將其變為陣列，他們的記憶體位址將是連續的，因此我們可以先宣告一個$struct$存放元素的數值，及指標。而這個指標是指向將要放在陣列中下一個元素的記憶體位址，如此一來，我們便串接了3個原本各自存放在不同記憶體位址的元素了。假如我現在想要增加一個新的元素3在2與4之間，我只需要將2這個元素的下一個指標指向3這個記憶體位址，再將3這個記憶體指標指向4這個元素的記憶體位址，因此可以省去不少copy和paste動作的時間。

### 建立struct:
對於每個元素，我們都需要存放它的數值及存放下一個數值的記憶體位址，因此我們需要宣告一個struct如下:
```c=
struct node{
    int value;
    struct node *next;
};

//avoid typing struct many times
typedef struct node node_t;
```

### 實作串接:
```c=
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

int main(){
    node_t n1, n2, n3;
    node_t *head; //where the linkedlist start

    n1.value=1;
    n2.value=2;
    n3.value=4;

    //link them up: n1 -> n2 -> n3
    head=&n1;
    n1.next=&n2;
    n2.next=&n3;
    n3.next=NULL; // when to stop

    printlist(head);

    return 0;
}
```
結果: ![](https://i.imgur.com/Ay4xfuw.png)，

### 實作插入:
假如我們想要在2跟4裡面加入新的節點為3，那要如何做呢?我們可以宣告一個新的節點，而其數值為3，將2號節點指向他，而將自己的節點指向元素4的節點即可。
```c=
node_t new;
new.value=3;
n2.next=&new;
new.next=&n3;
```
full code:https://github.com/coherent17/C-data-structure/blob/main/Linked%20List/linkedlist_no_malloc.c
結果: ![](https://i.imgur.com/NjDTKt9.png)


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
