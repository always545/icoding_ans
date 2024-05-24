#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef int DataType;

typedef struct Node{
    DataType data;
    struct Node* left;
    struct Node* right;
}BiTNode, *BiTree;
//普通树节点的定义如下：

#define MAX_CHILDREN_NUM 5
struct _CSNode
{
    DataType data;
    struct _CSNode *children[MAX_CHILDREN_NUM];
};
typedef struct _CSNode CSNode;


struct __Queue
{
    int i, j; //指向数组内元素的游标
    void **array;
};
typedef struct __Queue Queue;

Queue* create_queue(); //创建队列
bool is_empty_queue(Queue *tree); //队为空返回true,不为空时返回false
void* del_queue(Queue *tree); //结点指针出队
void add_queue(Queue *tree, void *node); //结点指针入队
void free_queue(Queue *tree); //释放队列
// transform函数定义如下：
//BFS算法
BiTNode* transform(CSNode *root){
    Queue *q = create_queue;
    if(root == NULL){
        return NULL;  
    }
    BiTNode *bitree = (BiTNode*)malloc(sizeof(BiTNode));
    bitree->data = root->data;
    bitree->left =  bitree->right = NULL;
    add_queue(q,root);
    add_queue(q,bitree);
    while(!is_empty_queue(q)){
        CSNode *curcsnode = (CSNode*)del_queue(q);
        BiTNode *curnode = (BiTNode*)del_queue(q);
        BiTNode *pre = NULL;
        for(int i=0;curcsnode->children[i]!=NULL;i++){
            BiTNode* Newnode = (BiTNode*)malloc(sizeof(Newnode));
            Newnode->data = curcsnode->children[i]->data;
            Newnode->left = Newnode->right = NULL;
            if(i == 0){
                curnode->left = Newnode;
                pre = Newnode;
            }
            else{
                pre->right = Newnode;
                pre = pre->right;
            }
            add_queue(q,curcsnode->children[i]);
            add_queue(q,Newnode);
        }
    }
    free_queue(q);
    return bitree;
}
