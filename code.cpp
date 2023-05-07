#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
int  Visited[20];
int  visited[20];
int  Visited1[20];

typedef struct ArcNode { //边（弧）结点的类型定义
    int  adjvex;   //边（弧）的另一顶点的在数组中的位置
    ArcNode* nextarc;//指向下一边（弧）结点的指针  
}ArcNode;
typedef struct Vnode {//顶点结点及其数组的类型定义
    string data;    //顶点信息
    ArcNode* firstarc;    //指向关联该顶点的边（弧）链表
} Vnode, AdjList[10];
typedef struct {
    AdjList  vertices;
    int  vexnum, arcnum;    //图的当前顶点数和弧数
} ALGraph;    //图邻接表类型
typedef struct
{
    int elem[20];
    int top;
}seqstack;
void initStack(seqstack& s)
{
    s.top = 0;
}
void push(seqstack& s, int e)
{
    s.elem[s.top] = e;
    s.top++;
}
int pop(seqstack& s, int& e)
{
    s.top--;
    return   e = s.elem[s.top];
}
int stackEmpty(seqstack s)
{
    if (s.top == 0)
        return 1;
    else return 0;
}

int  LocateVex(ALGraph& G, string vp)
{
    int  k = 0;
    for (k = 0; k < G.vexnum; k++)
    {
        if (G.vertices[k].data == vp)
            return(k);
    }
    return(-1);     /*  图中无此顶点  */
}
void CreatALGraph(ALGraph& G)//无向图的创建
{
    string v1, v2;
    int i, j, k;
    ArcNode* p1, * p2, * p, * q;
    printf("输入顶点数和边数\n");
    cin >> G.vexnum >> G.arcnum;
    for (i = 0; i < G.vexnum; i++)
    {
        printf("请输入顶点信息\n");
        cin >> G.vertices[i].data;
        G.vertices[i].firstarc = NULL;
    }
    for (k = 0; k < G.arcnum; k++)
    {
        printf("请输入连通的边\n");
        cin >> v1 >> v2;
        i = LocateVex(G, v1);
        j = LocateVex(G, v2);
        p1 = new ArcNode;
        p1->adjvex = j;
        p1->nextarc = NULL;
        p = G.vertices[i].firstarc;
        if (p == NULL)
            G.vertices[i].firstarc = p1;
        else
        {
            while (p->nextarc)
            {
                p = p->nextarc;
            }
            p->nextarc = p1;
        }
        p2 = new ArcNode;
        p2->adjvex = i;
        p2->nextarc = NULL;
        q = G.vertices[j].firstarc;
        if (q == NULL)
            G.vertices[j].firstarc = p2;
        else
        {
            while (q->nextarc)
            {
                q = q->nextarc;
            }
            q->nextarc = p2;
        }
    }
}


int FirstAdjvex(ALGraph G, int u)
{
    ArcNode* t;
    t = G.vertices[u].firstarc;
    if (t != NULL)
        return t->adjvex;
    else
        return -1;
}
int NextAdjvex(ALGraph G, int u, int w)
{
    ArcNode* t;
    t = G.vertices[u].firstarc;
    while (t != NULL)
    {
        if (t->adjvex != w)
            t = t->nextarc;
        else if (t->nextarc != NULL)
            return t->nextarc->adjvex;
        else
            return -1;
    }
    return -1;
}
void BFS(ALGraph G, int v)
{
    seqstack q;
    int u, w;
    cout << G.vertices[v].data << " ";
    Visited1[v] = true;
    initStack(q);
    push(q, v);
    while (!stackEmpty(q))
    {
        pop(q, u);
        for (w = FirstAdjvex(G, u); w >= 0; w = NextAdjvex(G, u, w))
            if (!Visited1[w])
            {
                cout << G.vertices[w].data << " ";
                Visited1[w] = true;
                push(q, w);
            }
    }
    cout << endl;
}

void DFS1(ALGraph G, int v)
{//深度优先搜索递归算法 
    ArcNode *p;
    visited[v] = 1;
    cout<<G.vertices[v].data<<" ";
    p = G.vertices[v].firstarc;
    while (p)
    {
        if (!visited[p->adjvex])
            DFS1(G, p->adjvex);
        p = p->nextarc;
    }
}




void DFS(ALGraph G, int v)
{
    seqstack s;
    int k, w;
    initStack(s);
    push(s, v);
    while (!stackEmpty(s))
    {
        pop(s, k);
        if (!Visited[k])
        {
            Visited[k] = true; cout << G.vertices[k].data << " ";
            for (w = FirstAdjvex(G, k); w >= 0; w = NextAdjvex(G, k, w))
            {
                if (!Visited[w])
                {
                    push(s, w);
                }
            }
        }
    }
    cout << endl;
}
int main()
{
    int  flag1 = 1;
    while (flag1)
    {
        ALGraph G;
        CreatALGraph(G);
        int flag = 1, i, j;
        printf("输入0，结束\n");
        printf("输入1，对图DFS\n");
        printf("输入2，对图BFS\n");
        while (flag)
        {
            printf("请输入0或1 或2\n");
            cin >> i;
            if (i == 1)   DFS(G, 0);
            if (i == 2)   BFS(G, 0);
            if (i == 0)   break;

        }
        printf("输入1重新构建无相连通图，或输入0结束进程\n");
        cin >> j;
        if (j == 0)  break;
    }
    return 0;
}
 