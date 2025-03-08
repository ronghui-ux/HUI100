#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <iostream>

#define OK 1;
#define ERROR 0;
#define OK 1;
typedef int Status;
typedef char vexType;
typedef char ElemType;

// ����LNode�ṹ��
typedef struct LNode {
    char** result;        // �洢�ַ��������ָ��
    struct LNode* next;   // ָ����һ���ڵ��ָ��
} LNode, * LinkList;

typedef struct AdjVexNode {
    char Adjvex[4];//���ڴ�����λ�ַ������ַ��������ǡ�/0��
    struct  AdjVexNode* next;
}AdjVexNode, * AdjVexNodeP;

typedef struct VexNode {
    vexType data[4];//����ǰ��λ���ڴ�����λ�ַ������ַ��������ǡ�/0��
    int point;//���ڴ���γ�ѧ��
    struct AdjVexNode* firstArc;
}VexNode;

typedef struct {
    VexNode* vexs;//��������
    int n;//�������
    int* tags;//���ڱ���Ƿ񱻷��ʹ�
}ALGraph;

typedef struct LQNode {
    ElemType data[4];
    struct LQNode* next;
} LQNode, * QueuePtr;//��㼰��ָ������

typedef struct {
    QueuePtr front;
    QueuePtr rear;
} LQueue;

char MenuText[4][30] = {
"[A] ÿѧ�ھ��⸺������",
"[B] �γ�ǰ�ڼ��в���",
"[C] ��ѧ�����޵ľ��⸺������",
"[D] Exit "
};
void displaymenu(int hilight) {
    int i;
    printf("\n=========�γ̱���ϵͳ=========\n");
    for (i = 0; i < 4; i++) {
        if (i == hilight - 1)
            printf("<<%s>>\n", MenuText[i]);
        else
            printf(" %s\n", MenuText[i]);
    }
    printf("==============================\n");
}




void clearscreen() {
    // ��ȡ����̨��������
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // ��ȡ����̨����Ļ��������Ϣ
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        // ������Ļ��������ʼ��
        COORD coord = { 0, 0 };
        DWORD dwWritten;

        // ��ȡ��Ļ�������Ĵ�С
        DWORD dwSize = csbi.dwSize.X * csbi.dwSize.Y;
        // �����Ļ������Ϊ�ո��൱�������Ļ��
        FillConsoleOutputCharacter(hConsole, ' ', dwSize, coord, &dwWritten);
        // �ָ���Ļ����������ɫ����
        FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwSize, coord, &dwWritten);
        // ��������õ���Ļ����ʼλ��
        SetConsoleCursorPosition(hConsole, coord);
    }
}



// ����һ���µ�����ڵ�
LNode* CreateNode(char** result) {
    LNode* newNode = (LNode*)malloc(sizeof(LNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newNode->result = result;
    newNode->next = NULL;
    return newNode;
}

//����һ���½ڵ㵽�����ͷ��
void InsertHead(LinkList& L, char** result, int num) {

    // �����½ڵ�
    LNode* newNode = (LNode*)malloc(sizeof(LNode));
    if (newNode == NULL) {
        printf("�½ڵ����ʧ��");
        return;  // �������ʧ�ܣ�ֱ�ӷ���
    }

    // �����ڴ�� newNode->result
    newNode->result = (char**)malloc(num * sizeof(char*));  // Ϊ result ��������ڴ�

    if (newNode->result == NULL) {
        free(newNode);  // �������ʧ�ܣ��ͷ� newNode ������
        return;
    }
    // Ϊÿ�� result[i] �����ڴ�
    for (int i = 0; i < num; i++) {
        newNode->result[i] = (char*)malloc(4 * sizeof(char));  // ÿ���ַ�������Ϊ 4
        if (newNode->result[i] == NULL) {
            // ����ڴ����ʧ�ܣ��ͷ��ѷ�����ڴ沢����
            for (int j = 0; j < i; j++) {
                free(newNode->result[j]);
            }
            free(newNode->result);
            free(newNode);
            return;
        }
    }
    // �� result ���ݸ��Ƶ� newNode->result ��
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < 3; j++) {
            newNode->result[i][j] = result[i][j];  // �����ַ�
        }
        newNode->result[i][3] = '\0';  // ������
    }


    // ���뵽����ͷ��
    newNode->next = L;
    L = newNode;
}




// ����һ���½ڵ㵽�����β��
void InsertTail(LinkList* L, char** result) {
    LNode* newNode = CreateNode(result);


    if (newNode == NULL) {
        return;
    }
    if (*L == NULL) {
        *L = newNode;
    }
    else {
        LNode* temp = *L;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// ɾ������ͷ���ڵ�
void DeleteHead(LinkList* L) {
    if (*L == NULL) {
        return;
    }
    LNode* temp = *L;
    *L = (*L)->next;
    free(temp);
}

// ɾ������β���ڵ�
void DeleteTail(LinkList* L) {
    if (*L == NULL) {
        return;
    }
    if ((*L)->next == NULL) {
        free(*L);
        *L = NULL;
        return;
    }
    LNode* temp = *L;
    while (temp->next && temp->next->next != NULL) {
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
}

// ��ӡ����
void PrintList(LinkList L, int num) {
    LNode* temp = L;
    if (temp == NULL)
    {
        printf("tempΪ��\n");
    }
    while (temp != NULL) {
        if (temp->result != NULL) {
            // result ��һ���ַ������飬��ӡ������
            int i = 0;
            while (i < num && temp->result[i] != NULL) {  // ����Խ�粢ȷ�������� num
                printf("%s ", temp->result[i]);
                i++;
            }
            printf("\n");
        }
        temp = temp->next;
    }
}




// �ͷ��������нڵ�
void FreeList(LinkList* L) {
    LNode* temp;
    while (*L != NULL) {
        temp = *L;
        *L = (*L)->next;
        // ���� result �е��ַ����Ƕ�̬������ڴ棬�ͷ�����
        if (temp->result != NULL) {
            int i = 0;
            while (temp->result[i] != NULL) {
                free(temp->result[i]);
                i++;
            }
            free(temp->result);
        }
        free(temp);
    }
}


Status search(VexNode* vexs, char* token, int num) {      // ���Ҳ����ؿγ̺Ŷ�Ӧ���±�
    for (int a = 0; a < num; a++) {
        if (strncmp(vexs[a].data, token, 3) == 0) { // ʹ��strncmp�����ַ����Ƚ�
            return a;
        }
    }
    printf("����Ŀγ̺Ų�����\n");
    return -1;  // ����-1��ʾû���ҵ�
}

// ��ʼ������
Status InitQueue(LQueue* Q) {
    Q->front = Q->rear = (LQNode*)malloc(sizeof(LQNode));
    if (!Q->front) {
        return ERROR;
    }
    Q->front->next = NULL;
    return OK;
}

// ��Ӳ���
Status EnQueue(LQueue* Q, ElemType e[]) {
    LQNode* p = (LQNode*)malloc(sizeof(LQNode));
    if (!p) {
        return ERROR;
    }
    // ��ȷ����Ԫ�صķ�Χ��������� ElemType ���͵����鳤��Ϊ4���ϸ�������Ƚ��и���
    strncpy_s(p->data, e, 4);

    //p->data[4] = '\0';
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
    return OK;
}

// ���Ӳ���
Status DeQueue(LQueue* Q, ElemType e[]) {
    if (Q->front == Q->rear) {
        return ERROR;
    }
    LQNode* p = Q->front->next;
    for (int i = 0; i < 4; i++) {
        e[i] = p->data[i];
    }

    Q->front->next = p->next;
    if (Q->rear == p) {
        Q->rear = Q->front;
    }
    free(p);
    return OK;
}

// �ж϶����Ƿ�Ϊ��
Status QueueEmpty(LQueue* Q) {
    return Q->front == Q->rear;
}

// ���ҽڵ�����
int FindIndegree(ALGraph G, char course[]) {
    int indegree = 0;
    for (int i = 0; i < G.n; i++) {
        AdjVexNode* p = G.vexs[i].firstArc;
        while (p) {
            if (strncmp(p->Adjvex, course, 3) == 0) {
                indegree++;
            }
            p = p->next;
        }
    }
    return indegree;
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
    str[strcspn(str, "\n")] = '\0'; // ȥ�����з�

    const char* delimiters = ", ";  // ���嶺�źͿո���Ϊ�ָ��� 
    char* token = nullptr;
    char* context = nullptr; // ���ڱ���������

    token = strtok_s(str, delimiters, &context); // ��һ�ε��� strtok_s

    // ����γ�����
    for (int i = 0; token != nullptr && i < num; i++) {
        for (int j = 0; j < 3; j++) {
            G.vexs[i].data[j] = token[j];
        }
        G.vexs[i].data[3] = '\0'; // ȷ���� '\0' ��β
        token = strtok_s(nullptr, delimiters, &context); // ��ȡ��һ���γ�����
    }

    // ����γ�ѧ��
    printf("�밴˳������γ̶�Ӧ��ѧ��:\n");
    for (int k = 0; k < num; k++) {
        printf("%s:", G.vexs[k].data);
        scanf_s("%d", &G.vexs[k].point);
        getchar(); // ���Ķ���Ļ��з�
        G.vexs[k].firstArc = NULL; // ��ʼ���ÿγ̵����޿γ�����Ϊ��
    }

    // ����γ̵����޿γ̺�
    printf("������γ̵����޿γ̺�:\n");
    for (int k = 0; k < num; k++) { // �������γ̵����޿γ�

        printf("%s:", G.vexs[k].data);
        char str1[100];
        // ��ȡ���޿γ̺�
        fgets(str1, sizeof(str1), stdin);
        str1[strcspn(str1, "\n")] = '\0'; // ȥ�����з�

        token = strtok_s(str1, delimiters, &context); // ��ȡ��һ�����޿γ�

        // ����ÿ�����޿γ�
        while (token != nullptr) {
            AdjVexNode* p = (AdjVexNode*)malloc(sizeof(AdjVexNode));
            if (p != NULL) {
                // ����ǰ�γ̵ı�Ÿ�ֵ���ڽӽڵ�
                for (int j = 0; j < 3; j++) {
                    p->Adjvex[j] = G.vexs[k].data[j];
                }
                p->Adjvex[3] = '\0'; // ȷ���� '\0' ��β
                p->next = NULL; // ��ʼ��Ϊû����һ�ڵ�
            }

            // �������޿γ̶�Ӧ���±�
            int x = search(G.vexs, token, num);
            if (x != -1) {  // ����ҵ����޿γ�
                // ����ڵ㵽���޿γ�����
                if (G.vexs[x].firstArc == NULL) {
                    G.vexs[x].firstArc = p;
                }
                else {
                    p->next = G.vexs[x].firstArc;
                    G.vexs[x].firstArc = p;
                }
            }

            token = strtok_s(nullptr, delimiters, &context); // ��ȡ��һ�����޿γ�
        }
    }

    // ����ͼ�ṹ��ָ��
    return &G;
}

#define MAX_NODES 100  // �������ڵ���Ϊ100


//���ݷ������������������
void Toplogical_all_Sort_recursive(ALGraph G, int* indegree, int* visited, char** result, int count, LinkList& L) {
    // �����ǰ������������������ڽڵ�����˵���Ѿ��ҵ���һ����������������
    if (count == G.n) {
        InsertHead(L, result, G.n);
        return;
    }

    // ����һ����ʱ���д洢�������Ϊ0��δ���ʵĽڵ�
    LQueue tempQ;
    InitQueue(&tempQ);

    // �����������Ϊ0��δ���ʵĽڵ�
    for (int i = 0; i < G.n; i++) {
        if (indegree[i] == 0 && !visited[i]) {
            visited[i] = 1;  // ���ýڵ���Ϊ�ѷ���
            EnQueue(&tempQ, G.vexs[i].data);  // ���
            // ���������е�����Ԫ��
            while (!QueueEmpty(&tempQ)) {
                char temp[4];
                DeQueue(&tempQ, temp);  // ����һ���ڵ�

                // ���ýڵ���뵽��ǰ��������Ľ��������
                for (int i = 0; i < 4; i++) {
                    result[count][i] = temp[i];
                }

                // ����ͼ���������ڽڵ�����
                for (int i = 0; i < G.n; i++) {
                    if (strncmp(G.vexs[i].data, temp, 3) == 0) {
                        AdjVexNode* p = G.vexs[i].firstArc;
                        while (p) {
                            int x = search(G.vexs, p->Adjvex, G.n); // �����ڽӽڵ�
                            indegree[x]--;  // �ýڵ����ȼ���
                            p = p->next;
                        }
                    }
                }

                // �ݹ������һ���㼶
                Toplogical_all_Sort_recursive(G, indegree, visited, result, count + 1, L);

                // ���ݣ��ָ�״̬��������ǰ�ڵ�Ĵ���
                for (int i = 0; i < G.n; i++) {
                    if (strncmp(G.vexs[i].data, temp, 3) == 0) {
                        AdjVexNode* p = G.vexs[i].firstArc;
                        while (p) {
                            int x = search(G.vexs, p->Adjvex, G.n);
                            indegree[x]++;  // �ָ����
                            p = p->next;
                        }
                    }
                }

                // �ָ�����״̬
                for (int i = 0; i < G.n; i++) {
                    if (strncmp(G.vexs[i].data, temp, 3) == 0) {
                        visited[i] = 0;  // �ָ�Ϊδ����״̬
                        break;
                    }
                }
            }
        }
    }
}

// �����ú�������ʼ����Ȳ���ʼ�ݹ����������������
Status Toplogical_all_Sort(ALGraph G, LinkList& L) {
    LQueue Q;
    if (InitQueue(&Q) == 0) {
        printf("���г�ʼ��ʧ��");
        return ERROR;  // ��ʼ������ʧ�ܣ����ش���
    }

    int* indegree = (int*)malloc(G.n * sizeof(int));  // ��̬�����ڴ棬�洢ÿ���ڵ�����
    if (!indegree) {
        printf("��������ڴ����ʧ��");
        return ERROR;  // �ڴ����ʧ�ܣ����ش���
    }

    // ��̬�����ά���飬�洢ÿ������Ľ����ÿ��������һ���ַ�����
    char** result = (char**)malloc(G.n * sizeof(char*));
    for (int i = 0; i < G.n; i++) {
        result[i] = (char*)malloc(4 * sizeof(char));  // ÿ���ڵ�γ���Ϊ4�ֽڣ�����'\0'��
    }

    // ����ÿ���ڵ�����
    for (int i = 0; i < G.n; i++) {
        indegree[i] = FindIndegree(G, G.vexs[i].data);  // ����ڵ�����

        if (indegree[i] == 0) {  // ������Ϊ0��˵���ýڵ���������
            EnQueue(&Q, G.vexs[i].data);  // �����Ϊ0�Ľڵ�������
        }
    }

    int* visited = (int*)malloc(G.n * sizeof(int));  // ���ÿ���ڵ��Ƿ��ѷ���

    memset(visited, 0, G.n * sizeof(int));  // ��ʼ�����ʱ�����飬Ĭ��δ����

    // ��ʼ�ݹ����������������
    Toplogical_all_Sort_recursive(G, indegree, visited, result, 0, L);

    // �ͷŶ�̬������ڴ�
    free(visited);  // �ͷŷ��ʱ������
    for (int i = 0; i < G.n; i++) {
        free(result[i]);  // �ͷ�ÿ������ַ������ڴ�
    }
    free(result);  // �ͷŽ��ָ��������ڴ�
    free(indegree);  // �ͷ����������ڴ�

    return OK;  // �ɹ�ִ�У�����OK
}



// ��������ڵ����ĺ���
int countNodes(LNode* head) {
    int count = 0;
    LNode* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

char* removeDuplicateSlashes(char* str) {
    if (str == NULL) {
        return NULL;
    }
    int len = strlen(str);
    char* result = (char*)malloc((len + 1) * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    int i = 0, j = 0;
    while (i < len) {
        result[j] = str[i];
        if (str[i] == '/') {
            while (str[i + 1] == '/' && i + 1 < len) {
                i++;
            }
        }
        i++;
        j++;
    }
    result[j] = '\0';
    return result;
}



//���������㷨
int Load_Balancing(ALGraph G, LinkList L, int num, int total, int max, FILE* file) {
    //��������Ƿ�Ϊ��
    if (L == NULL)
    {
        printf("ERROR������Ϊ��");
        return 0;
    }
    int avg_num = num / total;
    int yu = num % total;
    LNode* temp = L;
    int count = 0;
    int totalpiont = 0;
    int tempp = 0;
    int i = 0;
    int nodenum = countNodes(L);
    // ��̬�����ά���飬�洢ÿ������Ľ����ÿ��������һ���ַ�����
    char** final = (char**)malloc(G.n * sizeof(char*));
    for (int i = 0; i < nodenum; i++) {
        final[i] = (char*)malloc(5 * G.n * sizeof(char));
        final[i][0] = '\0';
    }
    int s = 0;
    while (temp != NULL) {
        if (temp->result != NULL) {
            // result ��һ���ַ������飬��ӡ������
            while (i < num && temp->result[i] != NULL) {  // ����Խ�粢ȷ�������� num

                if ((i <= ((1 + avg_num) * yu - 1) && count == avg_num + 1) || totalpiont > max)
                {
                    count = 0; totalpiont = 0; tempp = 0;
                    int m = strlen(final[s]);
                    final[s][m] = '/';
                    final[s][m + 1] = '\0';

                }
                if ((i > ((1 + avg_num) * yu - 1) && (count == avg_num || count == avg_num + 1)) || totalpiont > max)
                {
                    count = 0; totalpiont = 0; tempp = 0;
                    int n = strlen(final[s]);
                    final[s][n] = '/';
                    final[s][n + 1] = '\0';
                }

                int k; int j = 0;
                k = strlen(final[s]);
                for (j = 0; j < 3; j++, k++) {
                    final[s][k] = temp->result[i][j];  // �����ַ�
                }
                final[s][k + 1] = '��';
                final[s][k + 2] = '\0';  // ������־
                int x = search(G.vexs, temp->result[i], G.n); totalpiont = totalpiont + G.vexs[x].point;
                if (i < G.n - 1)
                {
                    int y = search(G.vexs, temp->result[i + 1], G.n);

                    if ((tempp = totalpiont + G.vexs[y].point) > max)
                    {

                        int a = strlen(final[s]);
                        final[s][a] = '/';
                        final[s][a + 1] = '\0';
                        tempp = 0;
                    }
                }
                i++;
                count++;

            }
            i = 0; count = 0; totalpiont = 0;
            int k = strlen(final[s]);
            final[s][k + 1] = '\0';
            s++;
        }
        temp = temp->next;
        i = 0; count = 0; totalpiont = 0;
    }
    for (int i = 0; i < nodenum; i++)
    {
        final[i] = removeDuplicateSlashes(final[i]);
    }
    int couns = 0;
    for (int i = 0; i < nodenum; i++)
    {
        for (int j = 0; final[i][j] != '\0'; j++) {
            if (final[i][j] == '/')
            {
                couns++;
            }
        }
        if (couns <= num - 1)
        {
            printf("%s\n", final[i]);
            fprintf(file, "%s\n", final[i]);
        }
        couns = 0;
    }
}


//�γ�ǰ�ڼ���
int Pre_concentrated(ALGraph G, LinkList L, int num, int total, int max, FILE* file) {
    //��������Ƿ�Ϊ��
    if (L == NULL)
    {
        printf("ERROR������Ϊ��");
        return 0;
    }
    LNode* temp = L;
    int totalpiont = 0;
    int tempp = 0;
    int i = 0;
    int nodenum = countNodes(L);
    // ��̬�����ά���飬�洢ÿ������Ľ����ÿ��������һ���ַ�����
    char** final = (char**)malloc(G.n * sizeof(char*));
    for (int i = 0; i < nodenum; i++) {
        final[i] = (char*)malloc(5 * G.n * sizeof(char));
        final[i][0] = '\0';
    }
    int s = 0;
    while (temp != NULL) {
        if (temp->result != NULL) {
            // result ��һ���ַ������飬��ӡ������
            while (i < num && temp->result[i] != NULL) {  // ����Խ�粢ȷ�������� num

                if (totalpiont > max)
                {

                    totalpiont = 0;
                    tempp = 0;

                    int m = strlen(final[s]);
                    final[s][m] = '/';
                    final[s][m + 1] = '\0';
                }

                int k; int j = 0;
                k = strlen(final[s]);
                for (j = 0; j < 3; j++, k++) {
                    final[s][k] = temp->result[i][j];  // �����ַ�
                }
                final[s][k + 1] = '��';
                final[s][k + 2] = '\0';  // ������־
                int x = search(G.vexs, temp->result[i], G.n); totalpiont = totalpiont + G.vexs[x].point;
                if (i < G.n - 1)
                {
                    int y = search(G.vexs, temp->result[i + 1], G.n);

                    if ((tempp = totalpiont + G.vexs[y].point) > max)
                    {

                        tempp = 0;
                        int a = strlen(final[s]);
                        final[s][a] = '/';
                        final[s][a + 1] = '\0';
                        tempp = 0;
                    }
                }
                i++;
            }
            i = 0;  totalpiont = 0; s++;
        }
        temp = temp->next;
        i = 0; totalpiont = 0;
    }
    for (int i = 0; i < nodenum; i++)
    {
        final[i] = removeDuplicateSlashes(final[i]);
    }
    int couns = 0;
    for (int i = 0; i < nodenum; i++)
    {
        for (int j = 0; final[i][j] != '\0'; j++) {
            if (final[i][j] == '/')
            {
                couns++;
            }
        }
        if (couns <= num - 1)
        {
            printf("%s\n", final[i]);
            fprintf(file, "%s\n", final[i]);
        }
        couns = 0;
    }
}

//��ѧ�����޵ĸ��������㷨
int Load_Balancing_without_limit(ALGraph G, LinkList L, int num, int total, FILE* file) {
    //��������Ƿ�Ϊ��
    if (L == NULL)
    {
        printf("ERROR������Ϊ��");
        return 0;
    }
    int avg_num = num / total;
    int yu = num % total;
    LNode* temp = L;
    int count = 0;
    int i = 0;

    int nodenum = countNodes(L);
    // ��̬�����ά���飬�洢ÿ������Ľ����ÿ��������һ���ַ�����
    char** final = (char**)malloc(G.n * sizeof(char*));
    for (int i = 0; i < nodenum; i++) {
        final[i] = (char*)malloc(5 * G.n * sizeof(char));
        final[i][0] = '\0';
    }
    int s = 0;
    int k;
    while (temp != NULL) {
        if (temp->result != NULL) {
            // result ��һ���ַ������飬��ӡ������
            while (i < num && temp->result[i] != NULL) {  // ����Խ�粢ȷ�������� num

                if ((i <= ((1 + avg_num) * yu - 1) && count == avg_num + 1))
                {
                    count = 0;

                    int m = strlen(final[s]);
                    final[s][m] = '/';
                    final[s][m + 1] = '\0';
                }
                if ((i > ((1 + avg_num) * yu - 1) && (count == avg_num || count == avg_num + 1)))
                {
                    count = 0;

                    int n = strlen(final[s]);
                    final[s][n] = '/';
                    final[s][n + 1] = '\0';
                }

                
                int j = 0;
                k = strlen(final[s]);
                for (j = 0; j < 3; j++, k++){
                    final[s][k] = temp->result[i][j];  // �����ַ�
            }
            final[s][k + 1] = ' ';  // ������־
            final[s][k + 2] = '\0';  // ������־
            i++;
            count++;

        }
        printf("\n"); i = 0; count = 0; s++;
    }
    temp = temp->next;
    i = 0; count = 0;
}
     for (int i = 0; i < nodenum; i++)
     {
          final[i] = removeDuplicateSlashes(final[i]);
     }
     for (int i = 0; i < nodenum; i++) {
         for (int j = 0; final[i][j] != '\0'; j++) {
             printf("%c", final[i][j]);
             }
         }


     int couns = 0;
      for (int i = 0; i < nodenum; i++){
        for (int j = 0; final[i][j] != '\0'; j++) {
        if (final[i][j] == '/')
        {
            couns++;
        }
    }
    if (couns <= num - 1)
    {
        printf("%s\n", final[i]);
        fprintf(file, "%s\n", final[i]);
    }
    couns = 0;
}
}

int main() {

    ALGraph G;
    LinkList L = NULL;
    FILE* file_ptr;
    errno_t err = fopen_s(&file_ptr, "coursesort.txt", "a");
    if (err != 0)
    {
        printf("\n���ļ�����\n");
        return 0;

    }
    printf("\n=========�γ̱���ϵͳ=========\n\n");
    fprintf(file_ptr, "\n=========�γ̱���ϵͳ=========\n\n");

    printf("������ѧ��������ÿѧ��ѧ������\n");
    char str[100];
    int total, max, num;
    scanf_s("%d %d", &total, &max);


    printf("������γ�����:\n");
    scanf_s("%d", &num);
    fprintf(file_ptr, "ѧ��������%d\nÿѧ��ѧ�����ޣ�%d\n�γ�������%d\n", total, max, num);
    InitialALGraph(G, num);

    printf("���������пγ̺�\n");
    getchar();
    fgets(str, sizeof(str), stdin);
    fprintf(file_ptr, "���пγ̺ţ�%s\n", str);
    makeALGraph(G, str, num);
    Toplogical_all_Sort(G, L);

    clearscreen();
    char c = 'E';
    int sel = 1;
    displaymenu(sel);
    while (c != 'D') {
        for (;;) {
            if (_kbhit()) {
                if (GetAsyncKeyState(VK_UP)) {
                    sel = (sel > 1) ? sel - 1 : sel;
                    clearscreen();
                    displaymenu(sel);
                }
                if (GetAsyncKeyState(VK_DOWN)) {
                    sel = (sel < 4) ? sel + 1 : sel;
                    clearscreen();
                    displaymenu(sel);
                }
                c = _getch();
                if (c <= 'z' && c >= 'a')c = c - ('a' - 'A');
                if (c <= 'D' && c >= 'A') {
                    sel = c - 'A' + 1;
                    clearscreen();
                    displaymenu(sel);
                    printf("command is [%c]", c);

                    break;
                }
                else if (c == '\r') {
                    if (sel == 4)return (0);
                    printf("command is [%c]\n", 'A' + sel - 1);
                    c = 'A' + sel - 1;
                    break;
                }
                else if (c == 'D')
                    return(0);
                Sleep(100);
            }
        }
        if (c == 'A')
        {
            printf("ÿѧ�ھ��⸺�����ԣ�\n");
            fprintf(file_ptr, "ÿѧ�ھ��⸺�����ԣ�\n");
            Load_Balancing(G, L, num, total, max, file_ptr);
            printf("\n");
            fprintf(file_ptr, "\n");
            printf("�����Լ����鿴�������Ե�������\n");
        }
        else if (c == 'B')
        {
            printf("�γ�ǰ�ڼ��в���:\n");
            fprintf(file_ptr, "�γ�ǰ�ڼ��в���:\n");
            Pre_concentrated(G, L, num, total, max, file_ptr);
            printf("\n");
            fprintf(file_ptr, "\n");
            printf("�����Լ����鿴�������Ե�������\n");
        }
        else if (c == 'C')
        {
            printf("��ѧ�����޵ľ��⸺�����ԣ�\n");
            fprintf(file_ptr, "��ѧ�����޵ľ��⸺�����ԣ�\n");
            Load_Balancing_without_limit(G, L, num, total, file_ptr);
            printf("\n");
            fprintf(file_ptr, "\n");
            printf("�����Լ����鿴�������Ե�������\n");
        }
        else if (c == 'D')
        {
            fclose(file_ptr);
            break;
            return 0;
        }
    }
}