
#include"course.cpp"
typedef int Status;


int main() {
	printf("请输入学期总数和每学期学分上限");
	char str[100];
	int total, max, num;
	scanf_s("%d %d", &total, &max);
	//printf("%d %d",total,max);
	printf("请输入课程总数");
	scanf_s("%d", &num);
	printf("请输入所有课程号");
	getchar();

	VexNode vexs[99];

	fgets(str, sizeof(str), stdin);
	str[strcspn(str, "\n")] = '\0';

	//printf("%s",str);
	const char* delimiters = ", ";          // 定义逗号和空格作为分隔符 
	char* token = nullptr; char* context = nullptr; // 用于保存上下文
	token = strtok_s(str, delimiters, &context);   // 第一次调用 strtok 

	for (int i = 0; token != nullptr && i < num; i++)
	{
		for (int j = 0; j < 3; j++) {
			vexs[i].data[j] = token[j];
		}
		vexs[i].data[3] = '\0';  // 确保以 '\0' 结尾
		token = strtok_s(nullptr, delimiters, &context); // 使用 strtok 获取后续的 token 
	}

	printf("请按顺序输入课程对应的学分:\n");
	for (int k = 0; k < num; k++) {
		printf("%s:", vexs[k].data);
		scanf_s("%d", &vexs[k].piont);
		getchar();
		vexs[k].firstArc = NULL;
	}

	for (int k = 0; k < num; k++) {
		printf("%s:", vexs[k].data);
		printf("%d", vexs[k].piont);
		printf("\n");
	}



	printf("请输入课程的先修课程号:\n");
	for (int k = 0; k < num; k++) { //按单个课程号输入
		printf("%s:", vexs[k].data);

		fgets(str, sizeof(str), stdin);
		str[strcspn(str, "\n")] = '\0';

		//printf("%s",str);
		const char* delimiters = ", ";          // 定义逗号和空格作为分隔符 
		char* token = nullptr; char* context = nullptr; // 用于保存上下文

		token = strtok_s(str, delimiters, &context);   // 第一次调用 strtok_s

		while (token != nullptr) {
			AdjVexNode* p;
			if (p = (AdjVexNode*)malloc(sizeof(AdjVexNode)))
			{
				for (int j = 0; j < 3; j++) {
					p->Adjvex[j] = token[j];
				}
				p->Adjvex[3] = '\0';  // 确保以 '\0' 结尾
			}
			p->next = NULL;
			int x = search(vexs, token, num);   //查找并返回课程号对应的下标
			if (vexs[x].firstArc = NULL)     //插入节点
			{
				vexs[x].firstArc = p;
			}
			else {
				p->next = vexs[x].firstArc;
				vexs[x].firstArc = p;
			}
			token = strtok_s(nullptr, delimiters, &context); // 使用 strtok 获取后续的 token 
		}
	}













}