
#include"Course.h"
typedef int Status;

Status search(VexNode* vexs, char* token, int num) {      //���Ҳ����ؿγ̺Ŷ�Ӧ���±�
	for (int a = 0; a < num; a++) {
		for (int b = 0; b < 3; b++)
		{
			if (vexs[a].data[b] == token[b]) { printf("%d", a); return a; }
		}
	}
	printf("����Ŀγ̺Ų�����");
}