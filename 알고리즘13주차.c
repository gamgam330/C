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
        fprintf(stderr, "그래프: 정점의 개수 초과");
        return;
    }
    g->n++;
}

void insert_edge(GraphType1* g, int u, int v) {
    GraphNode* node;
    if (u >= g->n || v >= g->n) {
        fprintf(stderr, "그래프: 정점 번호 초과");
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

// 초기화 함수
void init(StackType* s)
{
    s->top = -1;
}
// 공백 상태 검출 함수
int is_empty(StackType* s)
{
    return (s->top == -1);
}
// 포화 상태 검출 함수
int is_full(StackType* s)
{
    return (s->top == (MAX_STACK_SIZE - 1));
}
// 삽입 함수
void push(StackType* s, element item)
{
    if (is_full(s)) {
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    else s->stack[++(s->top)] = item;
}
// 삭제 함수
element pop(StackType* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        return;
    }
    else return s->stack[(s->top--)];
}

// 위상정렬
void topo_sort(GraphType1* g) {
    int i;
    StackType s;
    GraphNode* node;

    int* in_degree = (int*)malloc(g->n * sizeof(int));          //각 정점에게 향하는 간선의 수
    for (i = 0; i < g->n; i++) {
        in_degree[i] = 0;
    }
    for (i = 0; i < g->n; i++) {
        GraphNode* node = g->adj_list[i];
        while (node != NULL) {
            in_degree[node->vertex]++;                          //0번부터 ~ n번까지 연결한 노드를 ++해주는 방법.
            node = node->link;                                  //각 정점에 연결된 간선의 수 확인
        }
    }

    init(&s);
    for (i = 0; i < g->n; i++) {
        if (in_degree[i] == 0) push(&s, i);                     //연결된 간선이 0개라면 push
    }

    while (!is_empty(&s)) {
        int w;
        w = pop(&s);
        printf("정점 %d ->", w);
        node = g->adj_list[w];
        while (node != NULL) {
            int u = node->vertex;                               //방금 확인한 node가 삭제 되기때문에 간선 하나 삭제시켜줘야함.
            in_degree[u]--;
            if (in_degree[u] == 0) push(&s, u);                 //이역시 0이면 push
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

    printf("\n\n시작할 정점 입력하세요 : ");
    scanf("%d", &start);

    for (int i = 0; i < g->n; i++) {
        visited[i] = 0;
    }

    DFS_TS(g, start);
    printList(g);
    for (int i = 0; i < g->n; i++) {
        if (!visited[i]) {
            printf("\n처음으로 돌아갑니다\n");
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
            min = distance[i];                          //제일 작은 가중치 찾기
            minpos = i;                                 //제일 작은 가중치의 정점번호
        }
    return minpos;
}

int level = 1;
void printStep(GraphType2* g) {
    printf("[%d단계]\n", level++);
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
        distance[i] = g->weight[start][i];                      //가중치와 방문 여부 초기화
        visited2[i] = 0;
        prev[i] = g->PREV[start][i];
    }

    visited2[start] = 1;
    distance[start] = 0;                                        //시작점 초기화

    for (int i = 0; i < g->n - 1; i++) {
        printStep(g);
        u = nextVertex(g->n);
        visited2[u] = 1;


        for (w = 0; w < g->n; w++)
            if (!visited2[w]) {
                if (distance[u] + g->weight[u][w] < distance[w]) {          //지나쳐온 노드의 가중치와 현재 간선의 가중치의 합이 현재 저장되어있는 distance보다 작으면
                    distance[w] = distance[u] + g->weight[u][w];            //대입
                    prev[w] = u;                                            //지나온 간선 초기화
                }
            }
    }

    printf("\n");
    for (int i = 0; i < g->n; i++)
        if (distance[i] == INF) {
            printf("%d의 최단경로 INF\n", i);
        }
        else {
            printf("%d의 최단경로 %3d\n", i, distance[i]);
        }
}

void Dijkstra_shortestPath2(GraphType2* g, int start) {
    int u, w;
    for (int i = 0; i < g->n; i++) {
        distance[i] = g->weight[start][i];                      //가중치와 방문 여부 초기화
        visited2[i] = 0;
        prev[i] = g->PREV[start][i];
    }

    visited2[start] = 1;
    distance[start] = 0;                                        //시작점 초기화

    

    for (int i = 0; i < g->n - 1; i++) {
        u = nextVertex(g->n);
        visited2[u] = 1;


        for (w = 0; w < g->n; w++)
            if (!visited2[w]) {
                if (distance[u] + g->weight[u][w] < distance[w]) {          //지나쳐온 노드의 가중치와 현재 간선의 가중치의 합이 현재 저장되어있는 distance보다 작으면
                    distance[w] = distance[u] + g->weight[u][w];            //대입
                    prev[w] = u;                                            //지나온 간선 초기화
                }
            }
    }
    printStep(g);
    printf("\n");
}

int main(void) {
    while (1) {
        int n;
        printf("0. 프로그램 종료\n");
        printf("1. 위상정렬\n");
        printf("2. 최단거리\n");
        printf("사용할 프로그램을 입력하세요 : ");
        scanf("%d", &n);
        printf("\n");

        switch (n)
        {
        case 0:{
            printf("프로그램을 종료합니다\n");
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
            printf("그래프를 결정해주세요 : ");
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

            printf("1. 위상정렬(1번)\n");
            printf("2. 위상정렬(2번)\n");
            printf("프로그램을 선택해 주세요 : ");
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
            int num; //시작할 정점 선택
            printf("시작할 정점 : ");
            scanf("%d", &num);
            int G;
            printf("그래프를 결정해주세요 : ");
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
            printf("2-3번문제를 실행 하시겠습니까? (0/1)");
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