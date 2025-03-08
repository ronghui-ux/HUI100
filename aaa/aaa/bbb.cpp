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


// ����һ��ԭ�ӽ��
GLNode* MakeAtom(AtomType e) {
	GLNode* node = (GLNode*)malloc(sizeof(GLNode));
	if (!node) return NULL;
	node->Tag = ATOM;
	node->un.atom = e;
	return node;
}


// ���������Ľ�������
GList parseGList(const char** s) {
	while (**s == ' ') (*s)++;  // �����ո�

	if (**s == '(') {  // �����ӱ�
		(*s)++;
		GList L = (GLNode*)malloc(sizeof(GLNode));
		if (**s == ')')  L = NULL;
		else {
			L->Tag = LIST;
			L->un.ptr.hp = parseGList(s);  // �ݹ鴦���ͷ
			L->un.ptr.tp = NULL;
		}

		GList current = L;
		while (**s == ',') {
			(*s)++;
			current->un.ptr.tp = (GLNode*)malloc(sizeof(GLNode));
			current = current->un.ptr.tp;
			current->Tag = LIST;
			current->un.ptr.hp = parseGList(s);  // �ݹ鴦�����Ԫ��
			current->un.ptr.tp = NULL;
		}

		if (**s == ')') (*s)++;  // ���� ')'
		return L;
	}
	else if ((**s >= 'a' && **s <= 'z') || (**s >= 'A' && **s <= 'Z')) {  // ����ԭ�ӽ��
		AtomType atom = **s;
		(*s)++;
		return MakeAtom(atom);
	}
	return NULL;
}

//���������
Status CreateGList(GList& L) {
	char input[100];
	//getchar();
	fgets(input, sizeof(input), stdin);

	const char* str = input;
	L = parseGList(&str);
	return (L != NULL) ? OK : ERROR;
}

// ��ӡ���������ڱ���ʱ��ӡԭ�ӽ��
Status visit(AtomType e) {
	printf("%c", e);
	return OK;
}


//���������ĺ���
Status GListTraverse(GList L, Status(*visit)(AtomType e)) {
	if (L == NULL)
	{
		printf("()");
		return OK;
	}

	if (L->Tag == ATOM) {  // ԭ�ӽ�㣬����visit��ӡ
		visit(L->un.atom);
	}
	else {  // ����
		printf("(");
		GListTraverse(L->un.ptr.hp, visit);  // ������ͷ
		GList temp = L->un.ptr.tp;

		while (temp != NULL) {  // ������β��ÿ�����
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
	printf("����������\n");
	CreateGList(mylist);
	printf("�����ɹ���\n");
	GListTraverse(mylist, visit);
	return 0;
}