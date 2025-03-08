#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
typedef int Status;
typedef char AtomType;


typedef enum {
	ATOM, LIST
}ElemTag;
typedef struct GLNode {
	ElemTag Tag;
	union {
		AtomType atom;
		struct {
			struct GLNode* hp;
			struct GLNode* tp;
		}ptr;
	}un;
}GLNode, * GList;


// 创建一个原子结点
GLNode* MakeAtom(AtomType e) {
	GLNode* node = (GLNode*)malloc(sizeof(GLNode));
	if (!node) return NULL;
	node->Tag = ATOM;
	node->un.atom = e;
	return node;
}


// 创建广义表的解析函数
GList parseGList(const char** s) {
	while (**s == ' ') (*s)++;  // 跳过空格

	if (**s == '(') {  // 创建子表
		(*s)++;
		GList L = (GLNode*)malloc(sizeof(GLNode));
		if (**s == ')')  L = NULL;
		else {
			L->Tag = LIST;
			L->un.ptr.hp = parseGList(s);  // 递归处理表头
			L->un.ptr.tp = NULL;
		}

		GList current = L;
		while (**s == ',') {
			(*s)++;
			current->un.ptr.tp = (GLNode*)malloc(sizeof(GLNode));
			current = current->un.ptr.tp;
			current->Tag = LIST;
			current->un.ptr.hp = parseGList(s);  // 递归处理后续元素
			current->un.ptr.tp = NULL;
		}

		if (**s == ')') (*s)++;  // 跳过 ')'
		return L;
	}
	else if ((**s >= 'a' && **s <= 'z') || (**s >= 'A' && **s <= 'Z')) {  // 创建原子结点
		AtomType atom = **s;
		(*s)++;
		return MakeAtom(atom);
	}
	return NULL;
}

//创建广义表
Status CreateGList(GList& L) {
	char input[100];
	//getchar();
	fgets(input, sizeof(input), stdin);

	const char* str = input;
	L = parseGList(&str);
	return (L != NULL) ? OK : ERROR;
}

// 打印函数，用于遍历时打印原子结点
Status visit(AtomType e) {
	printf("%c", e);
	return OK;
}


//遍历广义表的函数
Status GListTraverse(GList L, Status(*visit)(AtomType e)) {
	if (L == NULL)
	{
		printf("()");
		return OK;
	}

	if (L->Tag == ATOM) {  // 原子结点，调用visit打印
		visit(L->un.atom);
	}
	else {  // 表结点
		printf("(");
		GListTraverse(L->un.ptr.hp, visit);  // 遍历表头
		GList temp = L->un.ptr.tp;

		while (temp != NULL) {  // 遍历表尾的每个结点
			printf(",");
			GListTraverse(temp->un.ptr.hp, visit);
			temp = temp->un.ptr.tp;
		}
		printf(")");
	}
	return OK;
}

int main() {

	GList mylist;
	printf("请输入广义表：\n");
	CreateGList(mylist);
	printf("创建成功：\n");
	GListTraverse(mylist, visit);
	return 0;
}