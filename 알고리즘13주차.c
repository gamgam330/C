#include<stdio.h>
#include<stdlib.h>
#include <limits.h>

#define MAX_VERTICES 50
#define MAX_VERTICES2 8
#define INF   10000

typedef struct GraphNode {
    int vertex;
    struct GraphNode* link;
}GraphNode;

typedef struct GraphType1 {
    int n;
    GraphNode* adj_list[MAX_VERTICES];
}GraphType1;

void graph_init(GraphType1* g) {
    g->n = 0;
    for (int v = 0; v < MAX_VERTICES; v++)
        g->adj_list[v] = NULL;
}

void insert_vertex(GraphType1* g, int v) {
    if ((g->n) + 1 > MAX_VERTICES) {
        fprintf(stderr, "�׷���: ������ ���� �ʰ�");
        return;
    }
    g->n++;
}

void insert_edge(GraphType1* g, int u, int v) {
    GraphNode* node;
    if (u >= g->n || v >= g->n) {
        fprintf(stderr, "�׷���: ���� ��ȣ �ʰ�");
        return;
    }
    node = (GraphNode*)malloc(sizeof(GraphNode));
    node->vertex = v;
    node->link = g->adj_list[u];
    g->adj_list[u] = node;
}

#define MAX_STACK_SIZE 100
typedef int element;
typedef struct {
    element  stack[MAX_STACK_SIZE];
    int top;
} StackType;

// �ʱ�ȭ �Լ�
void init(StackType* s)
{
    s->top = -1;
}
// ���� ���� ���� �Լ�
int is_empty(StackType* s)
{
    return (s->top == -1);
}
// ��ȭ ���� ���� �Լ�
int is_full(StackType* s)
{
    return (s->top == (MAX_STACK_SIZE - 1));
}
// ���� �Լ�
void push(StackType* s, element item)
{
    if (is_full(s)) {
        fprintf(stderr, "���� ��ȭ ����\n");
        return;
    }
    else s->stack[++(s->top)] = item;
}
// ���� �Լ�
element pop(StackType* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        return;
    }
    else return s->stack[(s->top--)];
}

// ��������
void topo_sort(GraphType1* g) {
    int i;
    StackType s;
    GraphNode* node;

    int* in_degree = (int*)malloc(g->n * sizeof(int));          //�� �������� ���ϴ� ������ ��
    for (i = 0; i < g->n; i++) {
        in_degree[i] = 0;
    }
    for (i = 0; i < g->n; i++) {
        GraphNode* node = g->adj_list[i];
        while (node != NULL) {
            in_degree[node->vertex]++;                          //0������ ~ n������ ������ ��带 ++���ִ� ���.
            node = node->link;                                  //�� ������ ����� ������ �� Ȯ��
        }
    }

    init(&s);
    for (i = 0; i < g->n; i++) {
        if (in_degree[i] == 0) push(&s, i);                     //����� ������ 0����� push
    }

    while (!is_empty(&s)) {
        int w;
        w = pop(&s);
        printf("���� %d ->", w);
        node = g->adj_list[w];
        while (node != NULL) {
            int u = node->vertex;                               //��� Ȯ���� node�� ���� �Ǳ⶧���� ���� �ϳ� �������������.
            in_degree[u]--;
            if (in_degree[u] == 0) push(&s, u);                 //�̿��� 0�̸� push
            node = node->link;
        }
    }

    free(in_degree);
    printf("\n");
}

GraphNode* node = NULL;
int visited[MAX_VERTICES2];
void printList(GraphType1* g) {
    GraphNode* p = node;
    while (p != NULL) {
        printf("-> %d ", p->vertex);
        p = p->link;
    }
    printf("\n");
}

void DFS_TS(GraphType1* g, int v) {
    GraphNode* w;
    GraphNode* newNode = malloc(sizeof(GraphNode));
    visited[v] = 1;
    for (w = g->adj_list[v]; w; w = w->link) {
        if (!visited[w->vertex])
            DFS_TS(g, w->vertex);
    }
    newNode->vertex = v;
    newNode->link = node;
    node = newNode;
}

void topologicalSort2(GraphType1* g) {
    int start;

    printf("\n\n������ ���� �Է��ϼ��� : ");
    scanf("%d", &start);

    for (int i = 0; i < g->n; i++) {
        visited[i] = 0;
    }

    DFS_TS(g, start);
    printList(g);
    for (int i = 0; i < g->n; i++) {
        if (!visited[i]) {
            printf("\nó������ ���ư��ϴ�\n");
            DFS_TS(g, i);
            printList(g);
        }
    }
}

typedef struct GraphType2 {
    int n;
    int weight[MAX_VERTICES2][MAX_VERTICES2];
    int PREV[MAX_VERTICES2][MAX_VERTICES2];
}GraphType2;

int distance[MAX_VERTICES2];
int visited2[MAX_VERTICES2];
int prev[MAX_VERTICES2];

int nextVertex(int n) {
    int min, minpos;
    min = INT_MAX;
    minpos = -1;
    for (int i = 0; i < n; i++)
        if (distance[i] < min && !visited2[i]) {
            min = distance[i];                          //���� ���� ����ġ ã��
            minpos = i;                                 //���� ���� ����ġ�� ������ȣ
        }
    return minpos;
}

int level = 1;
void printStep(GraphType2* g) {
    printf("[%d�ܰ�]\n", level++);
    printf("distance : ");
    for (int i = 0; i < g->n; i++) {
        if (distance[i] == INF)
            printf(" * ");
        else
            printf("%2d ", distance[i]);
    }
    printf("\n");
    printf(" visited : ");
    for (int i = 0; i < g->n; i++)
        if (distance[i] == INF) {
            printf(" 0 ");
        }
        else {
            printf("%2d ", visited2[i]);
        }
    printf("\n");
    printf("    Prev : ");
    for (int i = 0; i < g->n; i++) {
        if (prev[i] == -1) printf(" X ");
        else if (prev[i] == -2) printf(" - ");
        else printf("%2d ", prev[i]);
    }
    printf("\n==================================\n");
}

void Dijkstra_shortestPath(GraphType2* g, int start) {
    int u, w;

    for (int i = 0; i < g->n; i++) {
        distance[i] = g->weight[start][i];                      //����ġ�� �湮 ���� �ʱ�ȭ
        visited2[i] = 0;
        prev[i] = g->PREV[start][i];
    }

    visited2[start] = 1;
    distance[start] = 0;                                        //������ �ʱ�ȭ

    for (int i = 0; i < g->n - 1; i++) {
        printStep(g);
        u = nextVertex(g->n);
        visited2[u] = 1;


        for (w = 0; w < g->n; w++)
            if (!visited2[w]) {
                if (distance[u] + g->weight[u][w] < distance[w]) {          //�����Ŀ� ����� ����ġ�� ���� ������ ����ġ�� ���� ���� ����Ǿ��ִ� distance���� ������
                    distance[w] = distance[u] + g->weight[u][w];            //����
                    prev[w] = u;                                            //������ ���� �ʱ�ȭ
                }
            }
    }

    printf("\n");
    for (int i = 0; i < g->n; i++)
        if (distance[i] == INF) {
            printf("%d�� �ִܰ�� INF\n", i);
        }
        else {
            printf("%d�� �ִܰ�� %3d\n", i, distance[i]);
        }
}

void Dijkstra_shortestPath2(GraphType2* g, int start) {
    int u, w;
    for (int i = 0; i < g->n; i++) {
        distance[i] = g->weight[start][i];                      //����ġ�� �湮 ���� �ʱ�ȭ
        visited2[i] = 0;
        prev[i] = g->PREV[start][i];
    }

    visited2[start] = 1;
    distance[start] = 0;                                        //������ �ʱ�ȭ

    

    for (int i = 0; i < g->n - 1; i++) {
        u = nextVertex(g->n);
        visited2[u] = 1;


        for (w = 0; w < g->n; w++)
            if (!visited2[w]) {
                if (distance[u] + g->weight[u][w] < distance[w]) {          //�����Ŀ� ����� ����ġ�� ���� ������ ����ġ�� ���� ���� ����Ǿ��ִ� distance���� ������
                    distance[w] = distance[u] + g->weight[u][w];            //����
                    prev[w] = u;                                            //������ ���� �ʱ�ȭ
                }
            }
    }
    printStep(g);
    printf("\n");
}

int main(void) {
    while (1) {
        int n;
        printf("0. ���α׷� ����\n");
        printf("1. ��������\n");
        printf("2. �ִܰŸ�\n");
        printf("����� ���α׷��� �Է��ϼ��� : ");
        scanf("%d", &n);
        printf("\n");

        switch (n)
        {
        case 0:{
            printf("���α׷��� �����մϴ�\n");
            return 0;
        }
        case 1: {
            GraphType1 g;
            node = NULL;
            graph_init(&g);
            insert_vertex(&g, 0);
            insert_vertex(&g, 1);
            insert_vertex(&g, 2);
            insert_vertex(&g, 3);
            insert_vertex(&g, 4);
            insert_vertex(&g, 5);
            insert_vertex(&g, 6);
            insert_vertex(&g, 7);
            printf("�׷����� �������ּ��� : ");
            int G;
            scanf("%d", &G);
            if (G == 1) {
                insert_edge(&g, 0, 1);
                insert_edge(&g, 0, 3);
                insert_edge(&g, 1, 2);
                insert_edge(&g, 1, 5);
                insert_edge(&g, 2, 5);
                insert_edge(&g, 2, 6);
                insert_edge(&g, 3, 4);
                insert_edge(&g, 5, 6);
                insert_edge(&g, 5, 7);
            }
            else if (G == 2) {
                insert_edge(&g, 0, 1);
                insert_edge(&g, 0, 3);
                insert_edge(&g, 1, 2);
                insert_edge(&g, 1, 3);
                insert_edge(&g, 1, 4);
                insert_edge(&g, 2, 4);
                insert_edge(&g, 2, 7);
                insert_edge(&g, 3, 4);
                insert_edge(&g, 3, 6);
                insert_edge(&g, 4, 5);
                insert_edge(&g, 4, 6);
                insert_edge(&g, 5, 7);
                insert_edge(&g, 6, 7);
            }

            printf("1. ��������(1��)\n");
            printf("2. ��������(2��)\n");
            printf("���α׷��� ������ �ּ��� : ");
            int N;
            scanf("%d", &N);
            if (N == 1) {
                topo_sort(&g);
            }
            else {
                topologicalSort2(&g);
            }
            break;
        }
        case 2: {
            int num; //������ ���� ����
            printf("������ ���� : ");
            scanf("%d", &num);
            int G;
            printf("�׷����� �������ּ��� : ");
            scanf("%d", &G);
            GraphType2 g;
            GraphType2 g1 = { 8,
            {{ 0, 11, 9, 8, INF, INF, INF, INF },
            { INF, 0, INF, INF, INF, 8, 8,INF },
            { INF, INF, 0, INF, 10, INF, INF,INF },
            { INF, 3, 6,  0, 1,  INF, INF, INF },
            { INF, INF, INF, INF, 0, INF, INF, 12 },
            { INF, INF, INF, INF, INF, 0, 7, INF },
            { INF, INF, INF, 12, INF, INF, 0, 5},
            { INF, INF, INF, INF, INF, 4, INF, 0}},
            {{ -2, num, num, num, -1, -1, -1, -1 },
            { -1, -2, -1, -1, -1, num, num,-1 },
            { -1, -1, -2, -1, num, -1, -1, -1 },
            { -1, num, num, -2, num,  -1, -1, -1 },
            { -1, -1, -1, -1, -2, -1, -1, num },
            { -1, -1, -1, -1, -1, -2, num, -1 },
            { -1, -1, -1, num, -1, -1, -2, num},
            { -1, -1, -1, -1, -1, num, -1, -2}} };

            GraphType2 g2 = { 8,
                {{ 0, 4, 7, 10, INF, INF, INF, INF },
                { INF, 0, INF, INF, INF, 20, 8,INF },
                { INF, INF, 0, INF, 8, INF, INF,INF },
                { INF, 2, 2,  0, 8,  INF, INF, INF },
                { INF, INF, INF, INF, 0, INF, INF, 12 },
                { INF, INF, INF, INF, INF, 0, 3, INF },
                { INF, INF, INF, 12, INF, INF, 0, 7},
                { INF, INF, INF, INF, INF, 4, INF, 0}},
                {{ -2, num, num, num, -1, -1, -1, -1 },
                { -1, -2, -1, -1, -1, num, num,-1 },
                { -1, -1, -2, -1, num, -1, -1, -1 },
                { -1, num, num, -2, num,  -1, -1, -1 },
                { -1, -1, -1, -1, -2, -1, -1, num },
                { -1, -1, -1, -1, -1, -2, num, -1 },
                { -1, -1, -1, num, -1, -1, -2, num},
                { -1, -1, -1, -1, -1, num, -1, -2}} };
            if (G == 1) {
                g = g1;
            }
            else {
                g = g2;
            }
            printf("\n");
            level = 1;
            Dijkstra_shortestPath(&g, num);
            printf("\n");

            int u;
            printf("2-3�������� ���� �Ͻðڽ��ϱ�? (0/1)");
            scanf("%d", &u);
            if (u == 0) {
                break;
            }
            else {
                level = 0;
                for (int i = 0; i < g.n; i++) {
                    Dijkstra_shortestPath2(&g, i);
                }
            }
            break;
        }
        default:
            break;
        }
    }
}