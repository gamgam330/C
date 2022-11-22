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
        fprintf(stderr, "큐가 포화상태입니다.");
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->queue[q->rear] = item;
}

int dequeue(QueueType* q) {
    if (isEmpty(q))
        fprintf(stderr, "큐가 공백상태입니다.");
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->queue[q->front];
}

//그래프

//인접행렬
typedef struct GraphType1 {
    int node;
    int adjMat[MAX_VERTICES][MAX_VERTICES];
    int weight[MAX_VERTICES][MAX_VERTICES];
}GraphType1;

//인접행렬 함수
void initArray(GraphType1* g) {                        //0으로 초기화
    g->node = 0;
    for (int r = 0; r < MAX_VERTICES; r++) {
        for (int c = 0; c < MAX_VERTICES; c++)
            g->adjMat[r][c] = 0;
    }
}

void insertVertexArray(GraphType1* g) {
    if ((g->node) + 1 > MAX_VERTICES) {
        fprintf(stderr, "그래프: 정점의 개수 초과");
        return;
    }
    g->node++;
}

void insertEdgeArray(GraphType1* g, int start, int end, int weight) {
    if (start >= g->node || end >= g->node) {
        fprintf(stderr, "그래프: 정점 번호 오류");
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

int bfsMat(GraphType1* g, int v, int* visited) {                              //너비우선탐색
    QueueType q;
    queueInit(&q);
    visited[v] = 1;
    printf("[정점 %d ->] ", v);
    enqueue(&q, v);
    while (!isEmpty(&q)) {
        v = dequeue(&q);
        for (int w = 0; w < g->node; w++) {
            if (g->adjMat[v][w] && !visited[w]) {
                visited[w] = 1;
                printf("[정점 %d ->] ", w);
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

//인접리스트
typedef struct GraphType2 {
    int node;
    int* adjList[MAX_VERTICES];
    int weight[MAX_VERTICES];
}GraphType2;

//인접리스트 함수
void initList(GraphType2* g) {
    g->node = 0;
    for (int v = 0; v < MAX_VERTICES; v++)
        g->adjList[v] = 0;
}

void insertVertexList(GraphType2* g) {
    if ((g->node) + 1 > MAX_VERTICES) {
        fprintf(stderr, "그래프: 정점의 개수 초과");
        return;
    }
    g->node++;
}

void insertEdgeList(GraphType2* g, int from, int to) {
    GraphNode* node = malloc(sizeof(GraphNode));
    if (from >= g->node || to >= g->node) {
        fprintf(stderr, "그래프: 정점 번호 오류");
        return;
    }
    node->vertex = to;
    node->link = g->adjList[from];
    g->adjList[from] = node;
}

void printAdjList(GraphType2* g) {
    for (int i = 0; i < g->node; i++) {
        GraphNode* p = g->adjList[i];
        printf("정점 %d의 인접 리스트 ", i);
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
    printf("정점 %d -> ", v);
    enqueue(&q, v);
    while (!isEmpty(&q)) {
        v = dequeue(&q);
        for (w = g->adjList[v]; w; w = w->link) {
            if (!visited2[w->vertex]) {
                visited2[w->vertex] = 1;
                printf("정점 %d -> ", w->vertex);
                enqueue(&q, w->vertex);
            }
        }
    }
}
//그래프 함수 끝
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
        if (!visited[i] && (dist[i] < dist[v]))                                    //가중치가 제일 작은 간선 찾기.
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
            printf("\n연결이 되어있지 않습니다.");                                 //간선 연결 안됐으면 종료
            return;
        }
        printf("==========정점 [%d] 추가 ==========\n", u);
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
            if (g->weight[u][v] != INF) {                                           //현재 보고있는 정점의 간선을 찾는 부분
                if (!visited[v] && g->weight[u][v] < dist[v]) {                     //그 간선을 연결하지 않았고, 간선의 가중치보다
                    dist[v] = g->weight[u][v];                                      //현재 저장된 dist가 크면 dist 수정
                }
                printf("\n");
            }
        }
        }
    printf("\n최종 dist값 >>>\n");
    for (i = 0; i < n; i++) {
        printf("%5d", dist[i]);
        sum += dist[i];
    }
    return sum;
}
//프림알고리즘 끝

int main(void) {
    srand(time(NULL));
    int N, n;
    while (1) {
        printf("\n\n0. 프로그램 종료\n");
        printf("1. 인접행렬\n");
        printf("2. 인접리스트\n");
        printf("3. 최소스패닝트리(인접행렬)\n");
        printf("원하는 프로그램을 입력하세요 : ");
        scanf("%d", &N);

        switch (N) {
        case 0: {
            printf("프로그램을 종료합니다.\n");
            return 0;
        }
        case 1: {
            int v, u;
            printf("정점과 간선의 갯수를 입력하세요 : ");
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

            printf("인접행렬 >>\n");
            printAdjArray(g, v);
            printf("\n\n");

            int start;
            printf("\n\nBFS를 시작할 정점 입력 : ");
            scanf("%d", &start);
            for (int i = 0; i < v; i++) {
                visited[i] = 0;
            }
            printf("\nBFS >>\n");
            int num = bfsMat(g, start, visited);
            for (int i = 0; i < v; i++) {
                int weight = rand() % 20 + 1;
                if (visited[i] == 0) {
                    printf("\n[%d] 정점에서 끊겼습니다.\n", num);
                    num = bfsMat(g, i, visited);
                }
            }
            free(g);

            break;
        }
        case 2: {
            int v, u;
            printf("정점과 간선의 갯수를 입력하세요 : ");
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
            printf("인접 리스트 >>\n");
            printAdjList(g);
            int start;
            printf("\n\nBFS를 시작할 정점 입력을 입력하세요 : ");
            scanf("%d", &start);
            printf("BFS >>\n");
            bfsList(g, start);
            for (int i = 0; i < v; i++) {
                if (visited2[i] == 0) {
                    printf("\n정점이 끊어졌습니다.\n");
                    bfsList(g, i);
                }
            }
            break;
        }
        case 3: {
            int v, u;
            printf("정점과 간선의 갯수를 입력하세요 : ");
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

            printf("인접행렬 >>\n");
            printAdjArray(g, v);
            printf("\n\n");

            int start;
            printf("시작할 정점을 입력하세요 : ");
            scanf("%d", &start);
            int num = bfsMat(g, start, visited);
            for (int i = 0; i < v; i++) {
                int weight = rand() % 20 + 1;
                if (visited[i] == 0) {
                    printf("\n=============================\n");
                    printf("\n\n[%d] 정점에서 끊겼습니다.\n", num);
                    printf("[%d]와 [%d] 정점을 연결합니다.\n", num, i);
                    printf("간선의 가중치는 [%d]입니다.\n", weight);
                    printf("\n=============================\n");
                    insertEdgeArray(g, num, i, weight);
                    num = bfsMat(g, i, visited);

                }
            }
            printf("\n=============================\n");
            printf("\n최종 그래프 >>>\n");
            printAdjArray(g, v);
            printf("\n\n");
            for (int i = 0; i < v; i++) {
                visited[i] = 0;
            }
            printf("\n=============================\n");
            int result = primMat(g, start, v, visited, dist);
            printf("\n최소비용 : %d\n", result);
            free(g);
            break;
        }
        }
    }
}