#pragma once
#include"common.h"


// ����LNode�ṹ��
typedef struct LNode {
    char** result;        // �洢�ַ��������ָ��
    struct LNode* next;   // ָ����һ���ڵ��ָ��
} LNode, * LinkList;

typedef struct AdjVexNode {
    char Adjvex[4];//���ڴ�����λ�ַ������ַ��������ǡ�/0��
    struct  AdjVexNode* next;
}AdjVexNode, * AdjVexNodeP;

typedef struct VexNode {
    vexType data[4];//����ǰ��λ���ڴ�����λ�ַ������ַ��������ǡ�/0��
    int point;//���ڴ���γ�ѧ��
    struct AdjVexNode* firstArc;
}VexNode;

typedef struct {
    VexNode* vexs;//��������
    int n;//�������
    int* tags;//���ڱ���Ƿ񱻷��ʹ�
}ALGraph;

typedef struct LQNode {
    ElemType data[4];
    struct LQNode* next;
} LQNode, * QueuePtr;//��㼰��ָ������

typedef struct {
    QueuePtr front;
    QueuePtr rear;
} LQueue;

char MenuText[4][29] = {
"[A] ÿѧ�ھ��⸺������",
"[B] �γ�ǰ�ڼ��в���",
"[C] ��ѧ�����޵ľ��⸺������",
"[D] Exit "
};

void clearscreen();
LNode* CreateNode(char** result);// ����һ���µ�����ڵ�
void InsertHead(LinkList& L, char** result, int num);//����һ���½ڵ㵽�����ͷ��
void InsertTail(LinkList* L, char** result);// ����һ���½ڵ㵽�����β��
void DeleteHead(LinkList* L);// ɾ������ͷ���ڵ�
void DeleteTail(LinkList* L);// ɾ������β���ڵ�
void PrintList(LinkList L, int num);// ��ӡ����
void FreeList(LinkList* L); // �ͷ��������нڵ�
Status search(VexNode* vexs, char* token, int num);// ���Ҳ����ؿγ̺Ŷ�Ӧ���±�
Status InitQueue(LQueue* Q);// ��ʼ������
Status EnQueue(LQueue* Q, ElemType e[]);// ��Ӳ���
Status DeQueue(LQueue* Q, ElemType e[]);// ���Ӳ���
Status QueueEmpty(LQueue* Q);// �ж϶����Ƿ�Ϊ��
int FindIndegree(ALGraph G, char course[]);// ���ҽڵ�����
Status InitialALGraph(ALGraph& G, int n);//��ʼ��ͼ
ALGraph* makeALGraph(ALGraph& G, char str[100], int num);//�����ڽӹ�ϵ
void Toplogical_all_Sort_recursive(ALGraph G, int* indegree, int* visited, char** result, int count, LinkList& L);//���ݷ������������������
Status Toplogical_all_Sort(ALGraph G, LinkList& L);// �����ú�������ʼ����Ȳ���ʼ�ݹ����������������
int countNodes(LNode* head);// ��������ڵ����ĺ���
char* removeDuplicateSlashes(char* str);//ɾ������б��
int Load_Balancing(ALGraph G, LinkList L, int num, int total, int max, FILE* file);//���������㷨
int Pre_concentrated(ALGraph G, LinkList L, int num, int total, int max, FILE* file);//�γ�ǰ�ڼ���
int Load_Balancing_without_limit(ALGraph G, LinkList L, int num, int total, FILE* file);//��ѧ�����޵ĸ��������㷨