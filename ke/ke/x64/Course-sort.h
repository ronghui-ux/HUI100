#pragma once
#include"common.h"


// 定义LNode结构体
typedef struct LNode {
    char** result;        // 存储字符串数组的指针
    struct LNode* next;   // 指向下一个节点的指针
} LNode, * LinkList;

typedef struct AdjVexNode {
    char Adjvex[4];//用于储存三位字符串，字符串后面是“/0”
    struct  AdjVexNode* next;
}AdjVexNode, * AdjVexNodeP;

typedef struct VexNode {
    vexType data[4];//数组前三位用于储存三位字符串，字符串后面是“/0”
    int point;//用于储存课程学分
    struct AdjVexNode* firstArc;
}VexNode;

typedef struct {
    VexNode* vexs;//顶点数组
    int n;//顶点个数
    int* tags;//用于标记是否被访问过
}ALGraph;

typedef struct LQNode {
    ElemType data[4];
    struct LQNode* next;
} LQNode, * QueuePtr;//结点及其指针类型

typedef struct {
    QueuePtr front;
    QueuePtr rear;
} LQueue;

char MenuText[4][29] = {
"[A] 每学期均衡负担策略",
"[B] 课程前期集中策略",
"[C] 无学分上限的均衡负担策略",
"[D] Exit "
};

void clearscreen();
LNode* CreateNode(char** result);// 创建一个新的链表节点
void InsertHead(LinkList& L, char** result, int num);//插入一个新节点到链表的头部
void InsertTail(LinkList* L, char** result);// 插入一个新节点到链表的尾部
void DeleteHead(LinkList* L);// 删除链表头部节点
void DeleteTail(LinkList* L);// 删除链表尾部节点
void PrintList(LinkList L, int num);// 打印链表
void FreeList(LinkList* L); // 释放链表所有节点
Status search(VexNode* vexs, char* token, int num);// 查找并返回课程号对应的下标
Status InitQueue(LQueue* Q);// 初始化队列
Status EnQueue(LQueue* Q, ElemType e[]);// 入队操作
Status DeQueue(LQueue* Q, ElemType e[]);// 出队操作
Status QueueEmpty(LQueue* Q);// 判断队列是否为空
int FindIndegree(ALGraph G, char course[]);// 查找节点的入度
Status InitialALGraph(ALGraph& G, int n);//初始化图
ALGraph* makeALGraph(ALGraph& G, char str[100], int num);//生成邻接关系
void Toplogical_all_Sort_recursive(ALGraph G, int* indegree, int* visited, char** result, int count, LinkList& L);//回溯法输出所有拓扑排序结果
Status Toplogical_all_Sort(ALGraph G, LinkList& L);// 主调用函数，初始化入度并开始递归查找所有拓扑排序
int countNodes(LNode* head);// 计算链表节点数的函数
char* removeDuplicateSlashes(char* str);//删除多余斜杠
int Load_Balancing(ALGraph G, LinkList L, int num, int total, int max, FILE* file);//负担均匀算法
int Pre_concentrated(ALGraph G, LinkList L, int num, int total, int max, FILE* file);//课程前期集中
int Load_Balancing_without_limit(ALGraph G, LinkList L, int num, int total, FILE* file);//无学分上限的负担均匀算法