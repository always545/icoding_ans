#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100          //假设非零元个数的最大值为100
typedef struct {
    int i,j;									//非零元的行下标和列下标，i 和 j 从 1 开始计数，与数学中矩阵元素的编号一致
    ElemType e;						//非零元的值
}Triple;

typedef struct {
    Triple data[MAXSIZE];			// 非零元三元组表
    int    m, n, len;							// 矩阵的行数、列数和非零元个数
}TSMatrix;
bool add_matrix(const TSMatrix *pM, const TSMatrix *pN, TSMatrix *pQ){
    if(pM->m!=pN->m||pM->n!=pN->n){
        return false;
    }
    int pM_len=0,pN_len = 0,i=0,count=0;
    int flag=0;
    /*
    flag == 0 ------> 将pN放入
    flag == 1 ------> 将pM放入
    flag == 2 ------> 相加后放入
    */
    while (1)
    {   if(pM_len == pM->len&&pN_len == pN->len){
        break;
        }
        if(pM_len == pM->len){
            flag = 0;
        }
        else if(pN_len == pN->len){
            flag = 1
        }
        else{
            if(pM->data[pM_len].i == pN->data[pN_len].i){
                if(pM->data[pM_len].j == pN->data[pN_len].j){
                    flag = 2;
                }
                else if(pM->data[pM_len].j < pN->data[pN_len].j){
                    flag = 1;
                }
                else{
                    flag = 0;
                }
            }
            else{
                if(pM->data[pM_len].i<pN->data[pN_len].i){
                    flag = 1;
                }
                else{
                    flag = 0;
                }
            }
        }
        switch (flag)
        {
        case 0:
            pQ->data[count].i = pN->data[pN_len].i;
            pQ->data[count].j = pN->data[pN_len].j;
            pQ->data[count].e = pN->data[pN_len].e;
            count++;
            pN_len++;
            break;

        case 1:
            pQ->data[count].i = pM->data[pM_len].i;
            pQ->data[count].j = pM->data[pM_len].j;
            pQ->data[count].e = pM->data[pM_len].e;
            count++;
            pM_len++;
            break;
        
        case 2:
            pQ->data[count].i = pN->data[pN_len].i;
            pQ->data[count].j = pN->data[pN_len].j;
            pQ->data[count].e = pN->data[pN_len].e + pM->data[pM_len].e;
            count++;
            pN_len++;
            pM_len++;
            break;
        default:
            return false;
            break;
        }
    }
    pQ->len = count;
    for (int q = 0; q < pQ->len; q++) {
        if (pQ->data[q].e == 0) {
            for (int i = q; i < pQ->len; i++) {
                pQ->data[i] = pQ->data[i + 1];
            }
            q--;
            pQ->len--;
        }
    }
    return true;
    
}