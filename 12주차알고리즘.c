#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MAX_QUEUE_SIZE 20
#define MAX_VERTICES 10

typedef struct {
    int queue[MAX_QUEUE_SIZE];
    int front, rear;
}QueueType;

void queueInit(QueueType* q) {
    q->front = q->rear = 0;
}

int isEmpty(QueueType* q) {
    return (q->front == q->rear);
}

int isFull(QueueType* q) {
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType* q, int item) {
    if (isFull(q))
        fprintf(stderr, "ť�� ��ȭ�����Դϴ�.");
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->queue[q->rear] = item;
}

int dequeue(QueueType* q) {
    if (isEmpty(q))
        fprintf(stderr, "ť�� ��������Դϴ�.");
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->queue[q->front];
}

//�׷���

//�������
typedef struct GraphType1 {
    int node;
    int adjMat[MAX_VERTICES][MAX_VERTICES];
    int weight[MAX_VERTICES][MAX_VERTICES];
}GraphType1;

//������� �Լ�
void initArray(GraphType1* g) {                        //0���� �ʱ�ȭ
    g->node = 0;
    for (int r = 0; r < MAX_VERTICES; r++) {
        for (int c = 0; c < MAX_VERTICES; c++)
            g->adjMat[r][c] = 0;
    }
}

void insertVertexArray(GraphType1* g) {
    if ((g->node) + 1 > MAX_VERTICES) {
        fprintf(stderr, "�׷���: ������ ���� �ʰ�");
        return;
    }
    g->node++;
}

void insertEdgeArray(GraphType1* g, int start, int end, int weight) {
    if (start >= g->node || end >= g->node) {
        fprintf(stderr, "�׷���: ���� ��ȣ ����");
        return;
    }
    g->adjMat[start][end] = 1;
    g->adjMat[end][start] = 1;
    g->weight[start][end] = weight;
    g->weight[end][start] = weight;
}

void printAdjArray(GraphType1* g) {
    for (int i = 0; i < g->node; i++) {
        for (int j = 0; j < g->node; j++)
            printf("%2d ", g->adjMat[i][j]);
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < g->node; i++) {
        for (int j = 0; j < g->node; j++)
            printf("%4d ", g->weight[i][j]);
        printf("\n");
    }
}

int bfsMat(GraphType1* g, int v, int* visited) {                              //�ʺ�켱Ž��
    QueueType q;
    queueInit(&q);
    visited[v] = 1;
    printf("[���� %d ->] ", v);
    enqueue(&q, v);
    while (!isEmpty(&q)) {
        v = dequeue(&q);
        for (int w = 0; w < g->node; w++) {
            if (g->adjMat[v][w] && !visited[w]) {
                visited[w] = 1;
                printf("[���� %d ->] ", w);
                enqueue(&q, w);
            }
        }
    }
    return v;
}

//LinkedList
typedef struct GraphNode {
    int vertex;
    struct GraphNode* link;
}GraphNode;

//��������Ʈ
typedef struct GraphType2 {
    int node;
    int* adjList[MAX_VERTICES];
    int weight[MAX_VERTICES];
}GraphType2;

//��������Ʈ �Լ�
void initList(GraphType2* g) {
    g->node = 0;
    for (int v = 0; v < MAX_VERTICES; v++)
        g->adjList[v] = 0;
}

void insertVertexList(GraphType2* g) {
    if ((g->node) + 1 > MAX_VERTICES) {
        fprintf(stderr, "�׷���: ������ ���� �ʰ�");
        return;
    }
    g->node++;
}

void insertEdgeList(GraphType2* g, int from, int to) {
    GraphNode* node = malloc(sizeof(GraphNode));
    if (from >= g->node || to >= g->node) {
        fprintf(stderr, "�׷���: ���� ��ȣ ����");
        return;
    }
    node->vertex = to;
    node->link = g->adjList[from];
    g->adjList[from] = node;
}

void printAdjList(GraphType2* g) {
    for (int i = 0; i < g->node; i++) {
        GraphNode* p = g->adjList[i];
        printf("���� %d�� ���� ����Ʈ ", i);
        while (p != NULL) {
            printf("-> %d ", p->vertex);
            p = p->link;
        }
        printf("\n");
    }
}

int visited2[MAX_VERTICES];
void bfsList(GraphType2* g, int v) {
    GraphNode* w;
    QueueType q;
    queueInit(&q);
    visited2[v] = 1;
    printf("���� %d -> ", v);
    enqueue(&q, v);
    while (!isEmpty(&q)) {
        v = dequeue(&q);
        for (w = g->adjList[v]; w; w = w->link) {
            if (!visited2[w->vertex]) {
                visited2[w->vertex] = 1;
                printf("���� %d -> ", w->vertex);
                enqueue(&q, w->vertex);
            }
        }
    }
}
//�׷��� �Լ� ��
#define INF 999
int extractMin(int n, int* visited, int* dist) {
    int v = -1;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            v = i;
            break;
        }
    }
    for (int i = 0; i < n; i++) {
        if (!visited[i] && (dist[i] < dist[v]))                                    //����ġ�� ���� ���� ���� ã��.
            v = i;
    }
    return v;
}

int primMat(GraphType1* g, int s, int n, int* visited, int* dist) {
    int i, v, sum = 0;
    for (int u = 0; u < n; u++) {
        dist[u] = INF;
        visited[u] = 0;
    }
    dist[s] = 0;
    for (int i = 0; i < n; i++) {
        int u = extractMin(n, visited, dist);
        visited[u] = 1;

        if (dist[u] == INF) {
            printf("\n������ �Ǿ����� �ʽ��ϴ�.");                                 //���� ���� �ȵ����� ����
            return;
        }
        printf("==========���� [%d] �߰� ==========\n", u);
        printf("\ndist");
        for (int j = 0; j < n; j++) {
            printf("   [%d]", j);
        }
        printf("\n\n");

        printf("select  ");
        for (int j = 0; j < n; j++) {
            if (visited[j]) printf("O     ");
            else printf("X     ");
        }
        printf("\n\n   ");
        for (int j = 0; j < n; j++) {
            if (dist[j] != INF) printf("%6d", dist[j]);
            else printf("   INF");
        }
        printf("\n");
        for (v = 0; v < n; v++) {
            if (g->weight[u][v] != INF) {                                           //���� �����ִ� ������ ������ ã�� �κ�
                if (!visited[v] && g->weight[u][v] < dist[v]) {                     //�� ������ �������� �ʾҰ�, ������ ����ġ����
                    dist[v] = g->weight[u][v];                                      //���� ����� dist�� ũ�� dist ����
                }
                printf("\n");
            }
        }
        }
    printf("\n���� dist�� >>>\n");
    for (i = 0; i < n; i++) {
        printf("%5d", dist[i]);
        sum += dist[i];
    }
    return sum;
}
//�����˰��� ��

int main(void) {
    srand(time(NULL));
    int N, n;
    while (1) {
        printf("\n\n0. ���α׷� ����\n");
        printf("1. �������\n");
        printf("2. ��������Ʈ\n");
        printf("3. �ּҽ��д�Ʈ��(�������)\n");
        printf("���ϴ� ���α׷��� �Է��ϼ��� : ");
        scanf("%d", &N);

        switch (N) {
        case 0: {
            printf("���α׷��� �����մϴ�.\n");
            return 0;
        }
        case 1: {
            int v, u;
            printf("������ ������ ������ �Է��ϼ��� : ");
            scanf("%d %d", &v, &u);
            GraphType1* g = malloc(sizeof(GraphType1));
            initArray(g);
            int* visited = (int*)malloc(sizeof(int) * v);
            int* dist = (int*)malloc(sizeof(int) * v);
            for (int i = 0; i < v; i++) {
                visited[i] = 0;
                for (int j = 0; j < v; j++) {
                    if (i == j) {
                        g->weight[i][j] = 0;
                    }
                    else {
                        g->weight[i][j] = INF;
                    }
                }
            }
            for (int i = 0; i < v; i++)
                insertVertexArray(g);

            for (int i = 0; i < u; i++) {
                int x = rand() % v;
                int y = rand() % v;
                while (x == y) y = rand() % v;
                int w = rand() % 20 + 1;
                insertEdgeArray(g, x, y, w);
            }

            printf("������� >>\n");
            printAdjArray(g, v);
            printf("\n\n");

            int start;
            printf("\n\nBFS�� ������ ���� �Է� : ");
            scanf("%d", &start);
            for (int i = 0; i < v; i++) {
                visited[i] = 0;
            }
            printf("\nBFS >>\n");
            int num = bfsMat(g, start, visited);
            for (int i = 0; i < v; i++) {
                int weight = rand() % 20 + 1;
                if (visited[i] == 0) {
                    printf("\n[%d] �������� ������ϴ�.\n", num);
                    num = bfsMat(g, i, visited);
                }
            }
            free(g);

            break;
        }
        case 2: {
            int v, u;
            printf("������ ������ ������ �Է��ϼ��� : ");
            scanf("%d %d", &v, &u);
            GraphType2* g = malloc(sizeof(GraphType2));
            initList(g);

            for (int i = 0; i < v; i++)
                insertVertexList(g);

            for (int i = 0; i < u; i++) {
                int x = rand() % v;
                int y = rand() % v;
                while (x == y) y = rand() % v;
                int w = rand() % 30 + 1;
                insertEdgeList(g, x, y, w);
            }
            for (int i = 0; i < v; i++) {
                visited2[i] = 0;
            }
            printf("���� ����Ʈ >>\n");
            printAdjList(g);
            int start;
            printf("\n\nBFS�� ������ ���� �Է��� �Է��ϼ��� : ");
            scanf("%d", &start);
            printf("BFS >>\n");
            bfsList(g, start);
            for (int i = 0; i < v; i++) {
                if (visited2[i] == 0) {
                    printf("\n������ ���������ϴ�.\n");
                    bfsList(g, i);
                }
            }
            break;
        }
        case 3: {
            int v, u;
            printf("������ ������ ������ �Է��ϼ��� : ");
            scanf("%d %d", &v, &u);
            GraphType1* g = malloc(sizeof(GraphType1));
            initArray(g);
            int* visited = (int*)malloc(sizeof(int) * v);
            int* dist = (int*)malloc(sizeof(int) * v);
            for (int i = 0; i < v; i++) {
                visited[i] = 0;
                for (int j = 0; j < v; j++) {
                    if (i == j) {
                        g->weight[i][j] = 0;
                    }
                    else {
                        g->weight[i][j] = INF;
                    }
                }
            }
            for (int i = 0; i < v; i++)
                insertVertexArray(g);

            for (int i = 0; i < u; i++) {
                int x = rand() % v;
                int y = rand() % v;
                while (x == y) y = rand() % v;
                int w = rand() % 20 + 1;
                insertEdgeArray(g, x, y, w);
            }

            printf("������� >>\n");
            printAdjArray(g, v);
            printf("\n\n");

            int start;
            printf("������ ������ �Է��ϼ��� : ");
            scanf("%d", &start);
            int num = bfsMat(g, start, visited);
            for (int i = 0; i < v; i++) {
                int weight = rand() % 20 + 1;
                if (visited[i] == 0) {
                    printf("\n=============================\n");
                    printf("\n\n[%d] �������� ������ϴ�.\n", num);
                    printf("[%d]�� [%d] ������ �����մϴ�.\n", num, i);
                    printf("������ ����ġ�� [%d]�Դϴ�.\n", weight);
                    printf("\n=============================\n");
                    insertEdgeArray(g, num, i, weight);
                    num = bfsMat(g, i, visited);

                }
            }
            printf("\n=============================\n");
            printf("\n���� �׷��� >>>\n");
            printAdjArray(g, v);
            printf("\n\n");
            for (int i = 0; i < v; i++) {
                visited[i] = 0;
            }
            printf("\n=============================\n");
            int result = primMat(g, start, v, visited, dist);
            printf("\n�ּҺ�� : %d\n", result);
            free(g);
            break;
        }
        }
    }
}