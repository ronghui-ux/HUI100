#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include <string.h>
#include<iostream>
#include<cstring>


#define OK 1;
#define ERROR 0;
#define OK 1;



typedef int Status;
typedef char vexType;
typedef char ElemType;

typedef enum {
	DG,DN,UDG,UDN
}GraphKind;

 typedef struct AdjVexNode {
	char Adjvex[4];
	struct  AdjVexNode* next;
	int info;
}AdjVexNode,*AdjVexNodeP;

 typedef struct VexNode {
	vexType data[4];
	int point;
	struct AdjVexNode* firstArc;
}VexNode;

 typedef struct {
	VexNode* vexs;
	int n;
	int e;
	GraphKind kind;
	int* tags;
}ALGraph;

 typedef struct LQNode {
	 ElemType data;
	 struct LQNode* next;
 } LQNode, * QueuePtr;//结点及其指针类型

 typedef struct {
	 QueuePtr front;
	 QueuePtr rear;
 } LQueue;

 Status InitialALGraph(ALGraph& G, int n);
 Status search(VexNode* vexs, char* token, int num);
 Status EnQueue_LQ(LQueue& Q, ElemType &e);
 Status DeQueue_LQ(LQueue& Q, ElemType &e);
 ALGraph* makeALGraph(ALGraph& G, char str[100], int num);
 

