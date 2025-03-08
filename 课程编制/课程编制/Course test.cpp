#include"Course.h"

Status search(VexNode* vexs, char* token, int num) {      // ���Ҳ����ؿγ̺Ŷ�Ӧ���±�
	for (int a = 0; a < num; a++) {
		if (strncmp(vexs[a].data, token, 3) == 0) { // ʹ��strncmp�����ַ����Ƚ�
			return a;
		}
	}
	printf("����Ŀγ̺Ų�����\n");
	return -1;  // ����-1��ʾû���ҵ�
}

void InitQueue_LQ(LQueue& Q) {
	// ����һ���յĶ��нڵ㣬��������Ϊ���е�ͷ��β
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(LQNode));

	if (Q.front == NULL) {  // ����ڴ�����Ƿ�ɹ�
		printf("Memory allocation failed.\n");
		exit(1);  // ����ڴ����ʧ�ܣ��˳�����
	}

	Q.front->next = NULL;   // ��ʼ������Ϊ�գ�ͷ���� next ָ�� NULL
}

Status EnQueue_LQ(LQueue& Q,ElemType &e) {//�ڶ���Q�Ķ�β����Ԫ��e
	LQNode* p;
	p = (LQNode*)malloc(sizeof(LQNode));
	if (NULL == p) return OVERFLOW;
	p->data = e; p->next = NULL;
	if (NULL == Q.front)Q.front = p;//e����ն���
	else Q.rear->next = p;//e����ǿն���
	Q.rear = p;//��βָ��ָ���µĶ�β
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
	// Step 1: ��ʼ��ͼ�Ļ�����Ϣ
	G.n = n;       // ���ö�����

	// Step 2: ���䶥������
	G.vexs = (VexNode*)malloc(n * sizeof(VexNode));
	if (G.vexs == NULL) {
		printf("�ڴ����ʧ��!\n");
		return -1;
	}

	// Step 3: ��ʼ��ÿ������
	for (int i = 0; i < n; i++) {
		memset(G.vexs[i].data, 0, sizeof(G.vexs[i].data)); // ��ʼ�������ʶ������Ϊ��
		G.vexs[i].point = -1; // ����Ĭ�ϵ�pointֵ��-1
		G.vexs[i].firstArc = NULL; // ��ʼ��Ϊû���ڽӱ�
	}
	return 0; // �ɹ���ʼ��
}


ALGraph* makeALGraph(ALGraph& G, char str[100], int num) {

	str[strcspn(str, "\n")] = '\0';

	//printf("%s",str);
	const char* delimiters = ", ";          // ���嶺�źͿո���Ϊ�ָ��� 
	char* token = nullptr; char* context = nullptr; // ���ڱ���������
	token = strtok_s(str, delimiters, &context);   // ��һ�ε��� strtok 

	for (int i = 0; token != nullptr && i < num; i++)
	{
		for (int j = 0; j < 3; j++) {
			G.vexs[i].data[j] = token[j];
		}
		G.vexs[i].data[3] = '\0';  // ȷ���� '\0' ��β
		token = strtok_s(nullptr, delimiters, &context); // ʹ�� strtok ��ȡ������ token 
	}

	printf("�밴˳������γ̶�Ӧ��ѧ��:\n");
	for (int k = 0; k < num; k++) {
		printf("%s:", G.vexs[k].data);
		scanf_s("%d", &G.vexs[k].point);
		getchar();
		G.vexs[k].firstArc = NULL;
	}


	printf("������γ̵����޿γ̺�:\n");
	for (int k = 0; k < num; k++) { //�������γ̺�����
		printf("%s:", G.vexs[k].data);

		fgets(str, sizeof(str), stdin);
		str[strcspn(str, "\n")] = '\0';

		//printf("%s",str);
		const char* delimiters = ", ";          // ���嶺�źͿո���Ϊ�ָ��� 
		char* token = nullptr; char* context = nullptr; // ���ڱ���������

		token = strtok_s(str, delimiters, &context);   // ��һ�ε��� strtok_s

		while (token != nullptr) {
			AdjVexNode* p = (AdjVexNode*)malloc(sizeof(AdjVexNode));
			if (p != NULL)
			{
				for (int j = 0; j < 3; j++) {
					p->Adjvex[j] = G.vexs[k].data[j];
				}
				p->Adjvex[3] = '\0';  // ȷ���� '\0' ��β
			}
			p->next = NULL;
			int x = search(G.vexs, token, num);   //���Ҳ����ؿγ̺Ŷ�Ӧ���±�
			if (G.vexs[x].firstArc == NULL)     //����ڵ�
			{
				G.vexs[x].firstArc = p;
			}
			else {
				p->next = G.vexs[x].firstArc;
				G.vexs[x].firstArc = p;
			}
			token = strtok_s(nullptr, delimiters, &context); // ʹ�� strtok ��ȡ������ token 
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
	LQueue Q; InitQueue_LQ(Q);//��ʼ��������Q 
	for(i=0; i<G.n; i++) indegree[i] = 0;
	for (i = 0;i < G.n;i++)//����ÿ����������
		for (p = G.vexs[i].firstArc; p != NULL; p = p->next) {
			int x=search(G.vexs, p->Adjvex,G.n);
            indegree[x]++;
		}
	printf("\n\n");
	for (i = 0; i < G.n; i++)
		if (0 == indegree[i])EnQueue_LQ(Q, i);//�����Ϊ0�Ķ������
	while (DeQueue_LQ(Q, i)){
		printf("%s", G.vexs[i].data); count++;//������㲢����
		for (p = G.vexs[i].firstArc; p != NULL; p = p->next) {//����������ڽӶ�����ȼ�1�������Ϊ0�������
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
	printf("������ѧ��������ÿѧ��ѧ������");
	char str[100];
	int total, max,num;
	scanf_s("%d %d",&total,&max);

	printf("������γ�����");
	scanf_s("%d",  &num);
	InitialALGraph(G,num);
	printf("���������пγ̺�");
	getchar();
	VexNode vexs[99];
	fgets(str, sizeof(str), stdin);
	makeALGraph(G,str,num);
	ToplogicalSort(G);
}