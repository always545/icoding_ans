#include<stdio.h>
#include<stdlib.h>
typedef int VertexType;

typedef enum{
    DG, UDG
}GraphType;

typedef struct ArcNode{
    int adjvex;
    InfoPtr *info;
    struct ArcNode *nextarc;
}ArcNode;

typedef struct VNode{
    VertexType data;
    ArcNode *firstarc;
}VNode;
typedef struct{
    VNode vertex[MAX_VERTEX_NUM];
    int vexnum, arcnum;
    GraphType type;
}ListGraph;

int locate_vertex(ListGraph *G, VertexType v); //返回顶点 v 在vertex数组中的下标，如果v不存在，返回-1
bool del_vertex(ListGraph *G, VertexType v){ //删除顶点 v
    int index = locate_vertex(G,v);
    for(int i=0;i<MAX_VERTEX_NUM;i++){
        //删除以v为起点的边
        if(i==index){
            ArcNode* a = G->vertex[i].firstarc;
            while(a!=NULL){
                ArcNode* recycle = a;
                a = a->nextarc;
                free(recycle);
                --G->arcnum;
            }
            continue;
        }
        //起点不是v的情况下
        ArcNode* p = G->vertex[i].firstarc;
        while(p!=NULL){
            //如果链接的是v
            if(p->adjvex == index){
                if(p==G->vertex[i].firstarc){
                    G->vertex[i].firstarc = p->nextarc;
                    ArcNode* recycle = p;
                    p = p->nextarc;
                    --G->arcnum;
                    free(recycle);
                }
                else{
                    ArcNode* pre = G->vertex[i].firstarc;
                    while(pre->nextarc!=p){
                        pre = pre->nextarc;
                    }
                    pre->nextarc = p->nextarc;
                    ArcNode* recycle = p;
                    p = p->nextarc;
                    --G->arcnum;
                    free(recycle);
                }
                break;//每个节点到v最多有一条边
            }
            else{
                p = p->nextarc;
            }
        }
    }
    //还需要从表中删除v这个结点
    for(int i = index+1;i<MAX_VERTEX_NUM;i++){
        G->vertex[i-1] = G->vertex[i];
    }
    G->vexnum--;
    return true;
}
