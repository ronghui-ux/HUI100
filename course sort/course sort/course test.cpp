
#include"course.cpp"
typedef int Status;


int main() {
	printf("������ѧ��������ÿѧ��ѧ������");
	char str[100];
	int total, max, num;
	scanf_s("%d %d", &total, &max);
	//printf("%d %d",total,max);
	printf("������γ�����");
	scanf_s("%d", &num);
	printf("���������пγ̺�");
	getchar();

	VexNode vexs[99];

	fgets(str, sizeof(str), stdin);
	str[strcspn(str, "\n")] = '\0';

	//printf("%s",str);
	const char* delimiters = ", ";          // ���嶺�źͿո���Ϊ�ָ��� 
	char* token = nullptr; char* context = nullptr; // ���ڱ���������
	token = strtok_s(str, delimiters, &context);   // ��һ�ε��� strtok 

	for (int i = 0; token != nullptr && i < num; i++)
	{
		for (int j = 0; j < 3; j++) {
			vexs[i].data[j] = token[j];
		}
		vexs[i].data[3] = '\0';  // ȷ���� '\0' ��β
		token = strtok_s(nullptr, delimiters, &context); // ʹ�� strtok ��ȡ������ token 
	}

	printf("�밴˳������γ̶�Ӧ��ѧ��:\n");
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



	printf("������γ̵����޿γ̺�:\n");
	for (int k = 0; k < num; k++) { //�������γ̺�����
		printf("%s:", vexs[k].data);

		fgets(str, sizeof(str), stdin);
		str[strcspn(str, "\n")] = '\0';

		//printf("%s",str);
		const char* delimiters = ", ";          // ���嶺�źͿո���Ϊ�ָ��� 
		char* token = nullptr; char* context = nullptr; // ���ڱ���������

		token = strtok_s(str, delimiters, &context);   // ��һ�ε��� strtok_s

		while (token != nullptr) {
			AdjVexNode* p;
			if (p = (AdjVexNode*)malloc(sizeof(AdjVexNode)))
			{
				for (int j = 0; j < 3; j++) {
					p->Adjvex[j] = token[j];
				}
				p->Adjvex[3] = '\0';  // ȷ���� '\0' ��β
			}
			p->next = NULL;
			int x = search(vexs, token, num);   //���Ҳ����ؿγ̺Ŷ�Ӧ���±�
			if (vexs[x].firstArc = NULL)     //����ڵ�
			{
				vexs[x].firstArc = p;
			}
			else {
				p->next = vexs[x].firstArc;
				vexs[x].firstArc = p;
			}
			token = strtok_s(nullptr, delimiters, &context); // ʹ�� strtok ��ȡ������ token 
		}
	}













}