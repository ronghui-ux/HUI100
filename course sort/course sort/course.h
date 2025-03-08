#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include <string.h>
#include<iostream>
#include<cstring>

typedef int Status;
typedef char vexType;

typedef enum {
	DG, DN, UDG, UDN
}GraphKind;

typedef struct AdjVexNode {
	char Adjvex[4];
	struct  AdjVexNode* next;
	int info;
}AdjVexNode, * AdjVexNodeP;

typedef struct VexNode {
	vexType data[4];
	int piont;
	struct AdjVexNode* firstArc;
}VexNode;

typedef struct {
	VexNode* vexs;
	int n;
	int e;
	GraphKind kind;
	int* tags;
}ALGraph;

Status search(VexNode* vexs, char* token, int num);