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

// 定义LNode结构体
typedef struct LNode {
    char** result;        // 存储字符串数组的指针
    struct LNode* next;   // 指向下一个节点的指针
} LNode, * LinkList;

typedef struct AdjVexNode {
    char Adjvex[4];//用于储存三位字符串，字符串后面是“/0”
    struct  AdjVexNode* next;
}AdjVexNode, * AdjVexNodeP;

typedef struct VexNode {
    vexType data[4];//数组前三位用于储存三位字符串，字符串后面是“/0”
    int point;//用于储存课程学分
    struct AdjVexNode* firstArc;
}VexNode;

typedef struct {
    VexNode* vexs;//顶点数组
    int n;//顶点个数
    int* tags;//用于标记是否被访问过
}ALGraph;

typedef struct LQNode {
    ElemType data[4];
    struct LQNode* next;
} LQNode, * QueuePtr;//结点及其指针类型

typedef struct {
    QueuePtr front;
    QueuePtr rear;
} LQueue;

char MenuText[4][30] = {
"[A] 每学期均衡负担策略",
"[B] 课程前期集中策略",
"[C] 无学分上限的均衡负担策略",
"[D] Exit "
};
void displaymenu(int hilight) {
    int i;
    printf("\n=========课程编制系统=========\n");
    for (i = 0; i < 4; i++) {
        if (i == hilight - 1)
            printf("<<%s>>\n", MenuText[i]);
        else
            printf(" %s\n", MenuText[i]);
    }
    printf("==============================\n");
}




void clearscreen() {
    // 获取控制台的输出句柄
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // 获取控制台的屏幕缓冲区信息
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        // 设置屏幕缓冲区起始点
        COORD coord = { 0, 0 };
        DWORD dwWritten;

        // 获取屏幕缓冲区的大小
        DWORD dwSize = csbi.dwSize.X * csbi.dwSize.Y;
        // 填充屏幕缓冲区为空格（相当于清空屏幕）
        FillConsoleOutputCharacter(hConsole, ' ', dwSize, coord, &dwWritten);
        // 恢复屏幕缓冲区的颜色属性
        FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwSize, coord, &dwWritten);
        // 将光标设置到屏幕的起始位置
        SetConsoleCursorPosition(hConsole, coord);
    }
}



// 创建一个新的链表节点
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

//插入一个新节点到链表的头部
void InsertHead(LinkList& L, char** result, int num) {

    // 创建新节点
    LNode* newNode = (LNode*)malloc(sizeof(LNode));
    if (newNode == NULL) {
        printf("新节点分配失败");
        return;  // 如果分配失败，直接返回
    }

    // 分配内存给 newNode->result
    newNode->result = (char**)malloc(num * sizeof(char*));  // 为 result 数组分配内存

    if (newNode->result == NULL) {
        free(newNode);  // 如果分配失败，释放 newNode 并返回
        return;
    }
    // 为每个 result[i] 分配内存
    for (int i = 0; i < num; i++) {
        newNode->result[i] = (char*)malloc(4 * sizeof(char));  // 每个字符串长度为 4
        if (newNode->result[i] == NULL) {
            // 如果内存分配失败，释放已分配的内存并返回
            for (int j = 0; j < i; j++) {
                free(newNode->result[j]);
            }
            free(newNode->result);
            free(newNode);
            return;
        }
    }
    // 将 result 内容复制到 newNode->result 中
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < 3; j++) {
            newNode->result[i][j] = result[i][j];  // 复制字符
        }
        newNode->result[i][3] = '\0';  // 结束符
    }


    // 插入到链表头部
    newNode->next = L;
    L = newNode;
}




// 插入一个新节点到链表的尾部
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

// 删除链表头部节点
void DeleteHead(LinkList* L) {
    if (*L == NULL) {
        return;
    }
    LNode* temp = *L;
    *L = (*L)->next;
    free(temp);
}

// 删除链表尾部节点
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

// 打印链表
void PrintList(LinkList L, int num) {
    LNode* temp = L;
    if (temp == NULL)
    {
        printf("temp为空\n");
    }
    while (temp != NULL) {
        if (temp->result != NULL) {
            // result 是一个字符串数组，打印其内容
            int i = 0;
            while (i < num && temp->result[i] != NULL) {  // 避免越界并确保不超过 num
                printf("%s ", temp->result[i]);
                i++;
            }
            printf("\n");
        }
        temp = temp->next;
    }
}




// 释放链表所有节点
void FreeList(LinkList* L) {
    LNode* temp;
    while (*L != NULL) {
        temp = *L;
        *L = (*L)->next;
        // 假设 result 中的字符串是动态分配的内存，释放它们
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


Status search(VexNode* vexs, char* token, int num) {      // 查找并返回课程号对应的下标
    for (int a = 0; a < num; a++) {
        if (strncmp(vexs[a].data, token, 3) == 0) { // 使用strncmp进行字符串比较
            return a;
        }
    }
    printf("输入的课程号不存在\n");
    return -1;  // 返回-1表示没有找到
}

// 初始化队列
Status InitQueue(LQueue* Q) {
    Q->front = Q->rear = (LQNode*)malloc(sizeof(LQNode));
    if (!Q->front) {
        return ERROR;
    }
    Q->front->next = NULL;
    return OK;
}

// 入队操作
Status EnQueue(LQueue* Q, ElemType e[]) {
    LQNode* p = (LQNode*)malloc(sizeof(LQNode));
    if (!p) {
        return ERROR;
    }
    // 明确复制元素的范围，这里假设 ElemType 类型的数组长度为4，严格按这个长度进行复制
    strncpy_s(p->data, e, 4);

    //p->data[4] = '\0';
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
    return OK;
}

// 出队操作
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

// 判断队列是否为空
Status QueueEmpty(LQueue* Q) {
    return Q->front == Q->rear;
}

// 查找节点的入度
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
    str[strcspn(str, "\n")] = '\0'; // 去除换行符

    const char* delimiters = ", ";  // 定义逗号和空格作为分隔符 
    char* token = nullptr;
    char* context = nullptr; // 用于保存上下文

    token = strtok_s(str, delimiters, &context); // 第一次调用 strtok_s

    // 处理课程名称
    for (int i = 0; token != nullptr && i < num; i++) {
        for (int j = 0; j < 3; j++) {
            G.vexs[i].data[j] = token[j];
        }
        G.vexs[i].data[3] = '\0'; // 确保以 '\0' 结尾
        token = strtok_s(nullptr, delimiters, &context); // 获取下一个课程名称
    }

    // 输入课程学分
    printf("请按顺序输入课程对应的学分:\n");
    for (int k = 0; k < num; k++) {
        printf("%s:", G.vexs[k].data);
        scanf_s("%d", &G.vexs[k].point);
        getchar(); // 消耗多余的换行符
        G.vexs[k].firstArc = NULL; // 初始化该课程的先修课程链表为空
    }

    // 输入课程的先修课程号
    printf("请输入课程的先修课程号:\n");
    for (int k = 0; k < num; k++) { // 逐个输入课程的先修课程

        printf("%s:", G.vexs[k].data);
        char str1[100];
        // 获取先修课程号
        fgets(str1, sizeof(str1), stdin);
        str1[strcspn(str1, "\n")] = '\0'; // 去除换行符

        token = strtok_s(str1, delimiters, &context); // 获取第一个先修课程

        // 处理每个先修课程
        while (token != nullptr) {
            AdjVexNode* p = (AdjVexNode*)malloc(sizeof(AdjVexNode));
            if (p != NULL) {
                // 将当前课程的编号赋值给邻接节点
                for (int j = 0; j < 3; j++) {
                    p->Adjvex[j] = G.vexs[k].data[j];
                }
                p->Adjvex[3] = '\0'; // 确保以 '\0' 结尾
                p->next = NULL; // 初始化为没有下一节点
            }

            // 查找先修课程对应的下标
            int x = search(G.vexs, token, num);
            if (x != -1) {  // 如果找到先修课程
                // 插入节点到先修课程链表
                if (G.vexs[x].firstArc == NULL) {
                    G.vexs[x].firstArc = p;
                }
                else {
                    p->next = G.vexs[x].firstArc;
                    G.vexs[x].firstArc = p;
                }
            }

            token = strtok_s(nullptr, delimiters, &context); // 获取下一个先修课程
        }
    }

    // 返回图结构的指针
    return &G;
}

#define MAX_NODES 100  // 假设最大节点数为100


//回溯法输出所有拓扑排序结果
void Toplogical_all_Sort_recursive(ALGraph G, int* indegree, int* visited, char** result, int count, LinkList& L) {
    // 如果当前排序结果数组的索引等于节点数，说明已经找到了一个完整的拓扑排序
    if (count == G.n) {
        InsertHead(L, result, G.n);
        return;
    }

    // 创建一个临时队列存储所有入度为0且未访问的节点
    LQueue tempQ;
    InitQueue(&tempQ);

    // 发现所有入度为0且未访问的节点
    for (int i = 0; i < G.n; i++) {
        if (indegree[i] == 0 && !visited[i]) {
            visited[i] = 1;  // 将该节点标记为已访问
            EnQueue(&tempQ, G.vexs[i].data);  // 入队
            // 遍历队列中的所有元素
            while (!QueueEmpty(&tempQ)) {
                char temp[4];
                DeQueue(&tempQ, temp);  // 出队一个节点

                // 将该节点加入到当前拓扑排序的结果数组中
                for (int i = 0; i < 4; i++) {
                    result[count][i] = temp[i];
                }

                // 更新图中所有相邻节点的入度
                for (int i = 0; i < G.n; i++) {
                    if (strncmp(G.vexs[i].data, temp, 3) == 0) {
                        AdjVexNode* p = G.vexs[i].firstArc;
                        while (p) {
                            int x = search(G.vexs, p->Adjvex, G.n); // 查找邻接节点
                            indegree[x]--;  // 该节点的入度减少
                            p = p->next;
                        }
                    }
                }

                // 递归进入下一个层级
                Toplogical_all_Sort_recursive(G, indegree, visited, result, count + 1, L);

                // 回溯：恢复状态，撤销当前节点的处理
                for (int i = 0; i < G.n; i++) {
                    if (strncmp(G.vexs[i].data, temp, 3) == 0) {
                        AdjVexNode* p = G.vexs[i].firstArc;
                        while (p) {
                            int x = search(G.vexs, p->Adjvex, G.n);
                            indegree[x]++;  // 恢复入度
                            p = p->next;
                        }
                    }
                }

                // 恢复访问状态
                for (int i = 0; i < G.n; i++) {
                    if (strncmp(G.vexs[i].data, temp, 3) == 0) {
                        visited[i] = 0;  // 恢复为未访问状态
                        break;
                    }
                }
            }
        }
    }
}

// 主调用函数，初始化入度并开始递归查找所有拓扑排序
Status Toplogical_all_Sort(ALGraph G, LinkList& L) {
    LQueue Q;
    if (InitQueue(&Q) == 0) {
        printf("队列初始化失败");
        return ERROR;  // 初始化队列失败，返回错误
    }

    int* indegree = (int*)malloc(G.n * sizeof(int));  // 动态分配内存，存储每个节点的入度
    if (!indegree) {
        printf("入度数组内存分配失败");
        return ERROR;  // 内存分配失败，返回错误
    }

    // 动态分配二维数组，存储每个排序的结果（每个排序是一个字符串）
    char** result = (char**)malloc(G.n * sizeof(char*));
    for (int i = 0; i < G.n; i++) {
        result[i] = (char*)malloc(4 * sizeof(char));  // 每个节点课程名为4字节（包括'\0'）
    }

    // 计算每个节点的入度
    for (int i = 0; i < G.n; i++) {
        indegree[i] = FindIndegree(G, G.vexs[i].data);  // 计算节点的入度

        if (indegree[i] == 0) {  // 如果入度为0，说明该节点可以入队列
            EnQueue(&Q, G.vexs[i].data);  // 将入度为0的节点加入队列
        }
    }

    int* visited = (int*)malloc(G.n * sizeof(int));  // 标记每个节点是否已访问

    memset(visited, 0, G.n * sizeof(int));  // 初始化访问标记数组，默认未访问

    // 开始递归查找所有拓扑排序
    Toplogical_all_Sort_recursive(G, indegree, visited, result, 0, L);

    // 释放动态分配的内存
    free(visited);  // 释放访问标记数组
    for (int i = 0; i < G.n; i++) {
        free(result[i]);  // 释放每个结果字符串的内存
    }
    free(result);  // 释放结果指针数组的内存
    free(indegree);  // 释放入度数组的内存

    return OK;  // 成功执行，返回OK
}



// 计算链表节点数的函数
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



//负担均匀算法
int Load_Balancing(ALGraph G, LinkList L, int num, int total, int max, FILE* file) {
    //检查链表是否为空
    if (L == NULL)
    {
        printf("ERROR：链表为空");
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
    // 动态分配二维数组，存储每个排序的结果（每个排序是一个字符串）
    char** final = (char**)malloc(G.n * sizeof(char*));
    for (int i = 0; i < nodenum; i++) {
        final[i] = (char*)malloc(5 * G.n * sizeof(char));
        final[i][0] = '\0';
    }
    int s = 0;
    while (temp != NULL) {
        if (temp->result != NULL) {
            // result 是一个字符串数组，打印其内容
            while (i < num && temp->result[i] != NULL) {  // 避免越界并确保不超过 num

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
                    final[s][k] = temp->result[i][j];  // 复制字符
                }
                final[s][k + 1] = '和';
                final[s][k + 2] = '\0';  // 结束标志
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


//课程前期集中
int Pre_concentrated(ALGraph G, LinkList L, int num, int total, int max, FILE* file) {
    //检查链表是否为空
    if (L == NULL)
    {
        printf("ERROR：链表为空");
        return 0;
    }
    LNode* temp = L;
    int totalpiont = 0;
    int tempp = 0;
    int i = 0;
    int nodenum = countNodes(L);
    // 动态分配二维数组，存储每个排序的结果（每个排序是一个字符串）
    char** final = (char**)malloc(G.n * sizeof(char*));
    for (int i = 0; i < nodenum; i++) {
        final[i] = (char*)malloc(5 * G.n * sizeof(char));
        final[i][0] = '\0';
    }
    int s = 0;
    while (temp != NULL) {
        if (temp->result != NULL) {
            // result 是一个字符串数组，打印其内容
            while (i < num && temp->result[i] != NULL) {  // 避免越界并确保不超过 num

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
                    final[s][k] = temp->result[i][j];  // 复制字符
                }
                final[s][k + 1] = '和';
                final[s][k + 2] = '\0';  // 结束标志
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

//无学分上限的负担均匀算法
int Load_Balancing_without_limit(ALGraph G, LinkList L, int num, int total, FILE* file) {
    //检查链表是否为空
    if (L == NULL)
    {
        printf("ERROR：链表为空");
        return 0;
    }
    int avg_num = num / total;
    int yu = num % total;
    LNode* temp = L;
    int count = 0;
    int i = 0;

    int nodenum = countNodes(L);
    // 动态分配二维数组，存储每个排序的结果（每个排序是一个字符串）
    char** final = (char**)malloc(G.n * sizeof(char*));
    for (int i = 0; i < nodenum; i++) {
        final[i] = (char*)malloc(5 * G.n * sizeof(char));
        final[i][0] = '\0';
    }
    int s = 0;
    int k;
    while (temp != NULL) {
        if (temp->result != NULL) {
            // result 是一个字符串数组，打印其内容
            while (i < num && temp->result[i] != NULL) {  // 避免越界并确保不超过 num

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
                    final[s][k] = temp->result[i][j];  // 复制字符
            }
            final[s][k + 1] = ' ';  // 结束标志
            final[s][k + 2] = '\0';  // 结束标志
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
        printf("\n打开文件出错\n");
        return 0;

    }
    printf("\n=========课程编制系统=========\n\n");
    fprintf(file_ptr, "\n=========课程编制系统=========\n\n");

    printf("请输入学期总数和每学期学分上限\n");
    char str[100];
    int total, max, num;
    scanf_s("%d %d", &total, &max);


    printf("请输入课程总数:\n");
    scanf_s("%d", &num);
    fprintf(file_ptr, "学期总数：%d\n每学期学分上限：%d\n课程总数：%d\n", total, max, num);
    InitialALGraph(G, num);

    printf("请输入所有课程号\n");
    getchar();
    fgets(str, sizeof(str), stdin);
    fprintf(file_ptr, "所有课程号：%s\n", str);
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
            printf("每学期均衡负担策略：\n");
            fprintf(file_ptr, "每学期均衡负担策略：\n");
            Load_Balancing(G, L, num, total, max, file_ptr);
            printf("\n");
            fprintf(file_ptr, "\n");
            printf("您可以继续查看其他策略的排序结果\n");
        }
        else if (c == 'B')
        {
            printf("课程前期集中策略:\n");
            fprintf(file_ptr, "课程前期集中策略:\n");
            Pre_concentrated(G, L, num, total, max, file_ptr);
            printf("\n");
            fprintf(file_ptr, "\n");
            printf("您可以继续查看其他策略的排序结果\n");
        }
        else if (c == 'C')
        {
            printf("无学分上限的均衡负担策略：\n");
            fprintf(file_ptr, "无学分上限的均衡负担策略：\n");
            Load_Balancing_without_limit(G, L, num, total, file_ptr);
            printf("\n");
            fprintf(file_ptr, "\n");
            printf("您可以继续查看其他策略的排序结果\n");
        }
        else if (c == 'D')
        {
            fclose(file_ptr);
            break;
            return 0;
        }
    }
}