#include <stdio.h>
#include "stdlib.h"
#include "hash.h"
#include <string.h>
typedef enum{
    HASH_OK,
    HASH_ERROR,
    HASH_ADDED,
    HASH_REPLACED_VALUE,
    HASH_ALREADY_ADDED,
    HASH_DELETED,
    HASH_NOT_FOUND,
} HASH_RESULT;

typedef struct __HashEntry HashEntry;
struct __HashEntry{
    union{
        char  *str_value;
        double dbl_value;
        int       int_value;
    } key;
    union{
        char  *str_value;
        double dbl_value;
        int       int_value;
        long   long_value;
        void  *ptr_value;
    } value;
    HashEntry *next;
};

struct __HashTable{
    HashEntry **bucket;        
    int size;
    HASH_RESULT last_error;
};
typedef struct __HashTable HashTable;

// 向哈希表中添加元素，其中键类型为char*， 元素类型为int。
HASH_RESULT hash_add_int(HashTable * table, const char * key, int value);

// 哈希表相关说明：

// HASH_RESULT 类型为相关函数的返回类型
// HashEntry 为哈希表所保存元素（即键值对 《key, value》）类型
// HashTable 为哈希表，其中 bucket 指向大小为size的、元素类型为 HashEntry*的指针数组
// 哈希表采用链地址法处理冲突
// 请实现 hash_add_int 函数，向哈希表中添加元素，其中键类型为char*， 元素类型为int。在添加过程中，如果要添加的键值key已在哈希表中，
//且对应的值value也已存在，
// 则函数返回 HASH_ALREADY_ADDED；如果要添加的键值key已在哈希表中，但对应的值value不同，
// 则函数将value值更新到哈希表中，之后返回 HASH_REPLACED_VALUE；如果要添加的键值key不在哈希表中，
// 则函数创建 HashEntry 类型，并将其加入到哈希表中，且函数返回 HASH_ADDED。本题所用的哈希函数如下：

long hash_string(const char *str)
{
    long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    if(hash < 0)
        hash *= -1;
    return hash;
}
HASH_RESULT hash_add_int(HashTable *table, const char *key, int value ){
    int index = hash_string(key)%table->size;
    HashEntry* scanner = table->bucket[index];
    while(scanner!=NULL){
        if(strcmp(scanner->key.str_value,key)==0){
            if(scanner->value.int_value == value){
                return HASH_ALREADY_ADDED;
            }
            else{
                scanner->value.int_value = value;
                return HASH_REPLACED_VALUE;
            }
        }
        scanner = scanner->next;
    }
    HashEntry* new = (HashEntry*)malloc(sizeof(HashEntry));
    if(new == NULL){
        return HASH_ERROR;
    }
    new->key.str_value = (char*)malloc(sizeof(char)*(strlen(key)+1));
    strcpy(new->key.str_value,key);
    new->value.int_value = value;
    new->next = table->bucket[index];
    table->bucket[index] = new;
    return HASH_ADDED;
}
HASH_RESULT hash_add_int_re(HashTable *table, const char *key, int value){
    int index = hash_string(key)%table->size;
    HashEntry* scanner = table->bucket[index];
    while(scanner!=NULL){
        if(strcmp(scanner->key.str_value,key)==0){
            if(scanner->value.int_value == value){
                return HASH_ALREADY_ADDED;
            }
            else{
                scanner->value.int_value = value;
                return HASH_REPLACED_VALUE;
            }
        }
        scanner = scanner->next;
    }
    HashEntry new;
    /*
    之所以不能这样写是因为new的生命周期只存在于整个程序运行时，运行结束后new就会被销毁，所以还是要使用malloc分配内存*/
    new.key.str_value = (char*)malloc(sizeof(char)*(strlen(key)+1))
    strcpy(new.key.str_value,key);
    new.value.int_value = value;
    new.next = table->bucket[index];
    table->bucket[index] = &new;
    return HASH_ADDED;
}
 