#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;
//icoding十字链表题目
// 非零元素结点结构
typedef struct OLNode
{
    int row,col;
    ElemType value;
    struct OLNode *right,*down;
}OLNode,*OLink;

// 十字链表结构
typedef struct
{
    OLink *rowhead,*colhead;
    int rows,cols,nums;
}CrossList, *PCrossList;
 int init_cross_list(PCrossList L, const ElemType *A, int m, int n);
// 其中 L 指向 CrossList 结构，且各成员已被初始化为0；
// A 为 ElemType 类型数组中第一个元素的地址，元素的个数为 m×n 个，按行优先存储（即A[0] 为十字链表第1行第1列的元素；
// A[1] 为第1行第2列的元素，A[n] 为第2行第1列的元素，A[n+1] 为第2行第2个元素）；
// m 表示十字链表的行数，n 表示十字链表的列数。
// init_cross_list 函数将 ElemType 数组中非0元素保存到十字链表中，函数返回非 0 元素的个数。
 int del_cross_list(PCrossList L, ElemType k);
// 其中 L 指向 要处理的 CrossList 结构，k 为要删除的元素；
// del_cross_list 函数删除十字链表中所有值为 k 的结点，并返回删除结点的个数。
int init_cross_list(PCrossList L, const ElemType *A, int m, int n){
        L->cols = n;
        L->rows = m;
        L->colhead = (OLink*)malloc(sizeof(OLink)*(n+1));
        if(L->colhead==NULL){
            exit(0);
        }  
        L->rowhead = (OLink*)malloc(sizeof(OLink)*(m+1));
        if(L->rowhead==NULL){
            exit(0);
        }
        for(int i =0;i<n+1;i++){
            L->colhead[i] = NULL;
        }
        for(int j=0;j<m+1;j++){
            L->rowhead[j] = NULL;
        }
        OLink row_p = NULL;
        OLink col_p = NULL;
        for(int i=0;i<m*n+1;i++){
            if(A[i]==0){
                continue;
            }
            L->nums++;
            OLink p = (OLink)malloc(sizeof(OLNode));
            p->down=NULL;
            p->right=NULL;
            p->value = A[i];
            p->col = i%n+1;
            p->row=i/n+1;
            if(L->rowhead[p->row]==NULL){
                L->rowhead[p->row] = p;
                row_p = L->rowhead[p->row];
            }
            else{
                row_p->right = p;
                row_p = p;
            }
            if(L->colhead[p->col]==NULL){
                L->colhead[p->col] = p;
                col_p = L->colhead[p->col];
            }
            else{
                col_p->down = p;
                col_p = p;
            }
        }
        return L->nums;
 }
int del_cross_list(PCrossList L, ElemType k){
    int cnt=0;
    OLink row_scanner,col_scanner;
    for(int row=1;row<=L->rows;row++){
        row_scanner = L->rowhead[row];
        while(row_scanner!=NULL){
            if(row_scanner->value==k){
                ++cnt;
                L->nums--;
                OLink pre = L->rowhead[row];
                while(pre->right!=row_scanner&&pre!=row_scanner){
                    pre = pre->right;
                }
                if(pre == row_scanner){
                    L->rowhead[row] = L->rowhead[row]->right;
                }
                else{
                    pre->right = row_scanner->right;
                }
                col_scanner = L->colhead[row_scanner->col];
                while(col_scanner->down!=row_scanner&&col_scanner!=row_scanner){
                    col_scanner = col_scanner->down;
                }
                if(col_scanner==row_scanner){
                    L->colhead[row_scanner->col] = L->colhead[row_scanner->col]->down;
                    row_scanner = row_scanner->right;
                }
                else{
                    col_scanner->down = row_scanner->down;
                    col_scanner = row_scanner;
                    row_scanner = row_scanner->right;
                }
                
                free(col_scanner);
                continue;
            }
            row_scanner = row_scanner->right;
        }
    }
    return cnt;

}
int main(){
    PCrossList L= (PCrossList)malloc(sizeof(CrossList));
    int A[11] = {1,2,3,4,5,6,7,8,8,8,8,0,0,0,0};
    printf("%d\n",init_cross_list(L,A,5,3));
    printf("%d",del_cross_list(L,8));
    return 0;
}