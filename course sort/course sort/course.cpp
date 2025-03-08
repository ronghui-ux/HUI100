
#include"Course.h"
typedef int Status;

Status search(VexNode* vexs, char* token, int num) {      //查找并返回课程号对应的下标
	for (int a = 0; a < num; a++) {
		for (int b = 0; b < 3; b++)
		{
			if (vexs[a].data[b] == token[b]) { printf("%d", a); return a; }
		}
	}
	printf("输入的课程号不存在");
}