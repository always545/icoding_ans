//块链串题目
#include<stdio.h>
#include<stdlib.h>
#define BLOCK_SIZE 4    // 可由用户定义的块大小
#define BLS_BLANK '#'   // 用于空白处的补齐字符

typedef struct _block {
    char ch[BLOCK_SIZE];    //块的数据域
    struct _block *next;    //块的指针域
} Block;

typedef struct {
    Block *head;        // 串的头指针
    Block *tail;        // 串的尾指针
    int len;            // 串的当前长度
} BLString;

//字符串初始化函数：
void blstr_init(BLString *T) {
    T->len = 0;
    T->head = NULL;
    T->tail = NULL;
}
// src为要查找的字符串
// pos为子串开始的下标
// len为子串的长度
// sub在函数调用运行前指向一个已经初始化好的空串，在函数返回时，sub指向串src从第pos个字符起长度为len的子串
// 函数查找成功返回true，参数不正确返回 false
bool blstr_substr(BLString src, int pos, int len, BLString *sub){
    if (pos < 0 || pos >= src.len || len < 1 || sub == NULL) {
        return false;
    }
    sub->head = (Block*)malloc(sizeof(Block));
    if (sub->head == NULL) {
        return false;
    }
    int sub_index=0,count=0,src_index=0;
    Block*cur_block=sub->head,*src_block=src.head;
    while(count <= pos + len - 1 && src_block != NULL && src_block->ch[src_index] != BLS_BLANK){
        if(count<pos){
            if(src_index<BLOCK_SIZE-1){
                src_index++;
            }
            else{
                src_block = src_block->next;
                src_index=0;
            }
            count++;
            continue;
        }
        else{
            cur_block->ch[sub_index] = src_block->ch[src_index];
            if(sub_index<BLOCK_SIZE-1){
                sub_index++;
            }
            else{
                sub_index = 0;
                cur_block->next = (Block*)malloc(sizeof(Block));
                cur_block = cur_block->next;
                cur_block->next=NULL;
            }
            if(src_index<BLOCK_SIZE-1){
                src_index++;
            }
            else{
                src_index = 0;
                src_block = src_block->next;
            }
            count++;
            sub->len++;
        }
    }
    
    if(sub_index%4!=0){
        sub->tail = cur_block;
        while(sub_index%4!=0){
            sub->tail->ch[sub_index%4] = BLS_BLANK;
            sub_index++;
        }
    }
    else{
        while(sub->tail->next!=cur_block){
            sub->tail = sub->tail->next;
        }
        sub->tail->next = NULL;
        free(cur_block);
    }
    return true;
}