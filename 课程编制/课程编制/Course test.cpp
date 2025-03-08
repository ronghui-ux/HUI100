#include"Course.h"

Status search(VexNode* vexs, char* token, int num) {      // 查找并返回课程号对应的下标
	for (int a = 0; a < num; a++) {
		if (strncmp(vexs[a].data, token, 3) == 0) { // 使用strncmp进行字符串比较
			return a;
		}
	}
	printf("输入的课程号不存在\n");
	return -1;  // 返回-1表示没有找到
}

void InitQueue_LQ(LQueue& Q) {
	// 创建一个空的队列节点，并将其作为队列的头和尾
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(LQNode));

	if (Q.front == NULL) {  // 检查内存分配是否成功
		printf("Memory allocation failed.\n");
		exit(1);  // 如果内存分配失败，退出程序
	}

	Q.front->next = NULL;   // 初始化队列为空，头结点的 next 指向 NULL
}

Status EnQueue_LQ(LQueue& Q,ElemType &e) {//在队列Q的队尾插入元素e
	LQNode* p;
	p = (LQNode*)malloc(sizeof(LQNode));
	if (NULL == p) return OVERFLOW;
	p->data = e; p->next = NULL;
	if (NULL == Q.front)Q.front = p;//e插入空队列
	else Q.rear->next = p;//e插入非空队列
	Q.rear = p;//队尾指针指向新的队尾
	return OK;
}

Status DeQueue_LQ(LQueue& Q, char* vex) {//c
	LQNode* p;
	if (NULL==Q.front)
	{
		return ERROR;
	}
	p = Q.front;
	e= p->data; 
	Q.front = p->next;
	if (Q.rear==p)
	{
		Q.rear==NULL;
	}free(p);
	return OK;
}






Status InitialALGraph(ALGraph& G, int n) {
	// Step 1: 初始化图的基本信息
	G.n = n;       // 设置顶点数

	// Step 2: 分配顶点数组
	G.vexs = (VexNode*)malloc(n * sizeof(VexNode));
	if (G.vexs == NULL) {
		printf("内存分配失败!\n");
		return -1;
	}

	// Step 3: 初始化每个顶点
	for (int i = 0; i < n; i++) {
		memset(G.vexs[i].data, 0, sizeof(G.vexs[i].data)); // 初始化顶点标识符数组为空
		G.vexs[i].point = -1; // 假设默认的point值是-1
		G.vexs[i].firstArc = NULL; // 初始化为没有邻接边
	}
	return 0; // 成功初始化
}


ALGraph* makeALGraph(ALGraph& G, char str[100], int num) {

	str[strcspn(str, "\n")] = '\0';

	//printf("%s",str);
	const char* delimiters = ", ";          // 定义逗号和空格作为分隔符 
	char* token = nullptr; char* context = nullptr; // 用于保存上下文
	token = strtok_s(str, delimiters, &context);   // 第一次调用 strtok 

	for (int i = 0; token != nullptr && i < num; i++)
	{
		for (int j = 0; j < 3; j++) {
			G.vexs[i].data[j] = token[j];
		}
		G.vexs[i].data[3] = '\0';  // 确保以 '\0' 结尾
		token = strtok_s(nullptr, delimiters, &context); // 使用 strtok 获取后续的 token 
	}

	printf("请按顺序输入课程对应的学分:\n");
	for (int k = 0; k < num; k++) {
		printf("%s:", G.vexs[k].data);
		scanf_s("%d", &G.vexs[k].point);
		getchar();
		G.vexs[k].firstArc = NULL;
	}


	printf("请输入课程的先修课程号:\n");
	for (int k = 0; k < num; k++) { //按单个课程号输入
		printf("%s:", G.vexs[k].data);

		fgets(str, sizeof(str), stdin);
		str[strcspn(str, "\n")] = '\0';

		//printf("%s",str);
		const char* delimiters = ", ";          // 定义逗号和空格作为分隔符 
		char* token = nullptr; char* context = nullptr; // 用于保存上下文

		token = strtok_s(str, delimiters, &context);   // 第一次调用 strtok_s

		while (token != nullptr) {
			AdjVexNode* p = (AdjVexNode*)malloc(sizeof(AdjVexNode));
			if (p != NULL)
			{
				for (int j = 0; j < 3; j++) {
					p->Adjvex[j] = G.vexs[k].data[j];
				}
				p->Adjvex[3] = '\0';  // 确保以 '\0' 结尾
			}
			p->next = NULL;
			int x = search(G.vexs, token, num);   //查找并返回课程号对应的下标
			if (G.vexs[x].firstArc == NULL)     //插入节点
			{
				G.vexs[x].firstArc = p;
			}
			else {
				p->next = G.vexs[x].firstArc;
				G.vexs[x].firstArc = p;
			}
			token = strtok_s(nullptr, delimiters, &context); // 使用 strtok 获取后续的 token 
		}
	}

	ALGraph* q = &G;
	return q;
	/*for (int i = 0; i < num; i++)
	{
		for (AdjVexNode* q = vexs[i].firstArc; q != NULL;) {
			printf("%s  ", q->Adjvex);
			q = q->next;
		}
		printf("\n");
	}
	*/
}



Status ToplogicalSort(ALGraph G) {
	
	int i, count = 0, * indegree;
	AdjVexNodeP p;
	indegree = (int*)malloc(G.n * sizeof(int));
	LQueue Q; InitQueue_LQ(Q);//初始化链队列Q 
	for(i=0; i<G.n; i++) indegree[i] = 0;
	for (i = 0;i < G.n;i++)//计算每个顶点的入度
		for (p = G.vexs[i].firstArc; p != NULL; p = p->next) {
			int x=search(G.vexs, p->Adjvex,G.n);
            indegree[x]++;
		}
	printf("\n\n");
	for (i = 0; i < G.n; i++)
		if (0 == indegree[i])EnQueue_LQ(Q, i);//将入度为0的顶点入队
	while (DeQueue_LQ(Q, i)){
		printf("%s", G.vexs[i].data); count++;//输出顶点并计数
		for (p = G.vexs[i].firstArc; p != NULL; p = p->next) {//将主顶点的邻接顶点入度减1，若入度为0，则入队
			int n = search(G.vexs, p->Adjvex, G.n);
			if (0  == --indegree[n]) EnQueue_LQ(Q,n);
		}
	}
	free(indegree);
	if (count<G.n)
	{
		return ERROR;
	}
	else
	{
		return OK;
	}
} 



int main() {

	ALGraph G;
	printf("请输入学期总数和每学期学分上限");
	char str[100];
	int total, max,num;
	scanf_s("%d %d",&total,&max);

	printf("请输入课程总数");
	scanf_s("%d",  &num);
	InitialALGraph(G,num);
	printf("请输入所有课程号");
	getchar();
	VexNode vexs[99];
	fgets(str, sizeof(str), stdin);
	makeALGraph(G,str,num);
	ToplogicalSort(G);
}