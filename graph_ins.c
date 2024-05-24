#include<stdio.h>
#include<stdlib.h>
typedef int VertexType;

typedef enum{
    DG, UDG
}GraphType;

typedef struct ArcNode
{
    int adjvex;
    InfoPtr *info;
    struct ArcNode *nextarc;

}ArcNode;

typedef struct VNode
{
    VertexType data;
    ArcNode *firstarc;
}VNode;
typedef struct
{
    VNode vertex[MAX_VERTEX_NUM];
    int vexnum, arcnum;
    GraphType type;
}ListGraph;

int locate_vertex(ListGraph* G, VertexType v); //返回顶点 v 在vertex数组中的下标，如果v不存在，返回-1
bool insert_vertex(ListGraph *G, VertexType v){
    int index = locate_vertex(G,v);
    if(index!=-1){
        //点已经存在了
        return false;
    }
    if(G->vexnum==MAX_VERTEX_NUM){
        //不能加点了
        return false;
    }
    G->vexnum++;
    VNode p = {
        v,NULL
    };
    G->vertex[G->vexnum-1] = p;
    return true;
}
bool insert_arc(ListGraph *G, VertexType v, VertexType w){
   if(locate_vertex(G,v)==-1||locate_vertex(G,w)==-1){
        return false;
    }
    if(G->type == DG){
        
        int index_v = locate_vertex(G,v);
        int index_w = locate_vertex(G,w);
        ArcNode*p = G->vertex[index_v].firstarc;
        //没有解决节点本来无边的情况
        if(p==NULL){
            G->vertex[index_v].firstarc = (ArcNode*)malloc(sizeof(ArcNode));
            p = G->vertex[index_v].firstarc;
            p->adjvex = index_w;
            p->info = NULL;
            p->nextarc = NULL;
            G->arcnum++;
            return 1;
        }
        while(p!=NULL){
            if(p->adjvex==index_w){//已经存在
                return false;
            }
            if(p->nextarc==NULL){
                p->nextarc = (ArcNode*)malloc(sizeof(ArcNode));
                p->nextarc->adjvex = index_w;
                p->nextarc->nextarc = NULL;
              //  p->nextarc->info = NULL;
                break;
            }
            p = p->nextarc;
        }
        G->arcnum++;
    }
    else{
        int index_v = locate_vertex(G,v);
        int index_w = locate_vertex(G,w);
        ArcNode*p = G->vertex[index_v].firstarc;
        if(p==NULL){
            G->vertex[index_v].firstarc = (ArcNode*)malloc(sizeof(ArcNode));
            p = G->vertex[index_v].firstarc;
            p->adjvex = index_w;
            p->info = NULL;
            p->nextarc = NULL;
            goto end;
        }
        while(p!=NULL){
            if(p->adjvex==index_w){//已经存在
                return false;
            }
            if(p->nextarc==NULL){
                p->nextarc = (ArcNode*)malloc(sizeof(ArcNode));
                p->nextarc->adjvex = index_w;
                p->nextarc->nextarc = NULL;
                //p->nextarc->info = NULL;
                break;
            }
            p = p->nextarc;
        }
    end:    G->arcnum+=2;
        ArcNode*q = G->vertex[index_w].firstarc;
        if(q==NULL){
            G->vertex[index_w].firstarc = (ArcNode*)malloc(sizeof(ArcNode));
            q = G->vertex[index_w].firstarc;
            q->adjvex = index_v;
            q->info = NULL;
            q->nextarc = NULL;
            return 1;
        }
        while(q!=NULL){
            if(q->adjvex==index_v){//已经存在
                return false;
            }
            if(q->nextarc==NULL){
                q->nextarc = (ArcNode*)malloc(sizeof(ArcNode));
                q->nextarc->adjvex = index_v;
                q->nextarc->nextarc = NULL;
               // q->nextarc->info = NULL;
                break;
            }
            q = q->nextarc;
        }
    }
    return true;
}