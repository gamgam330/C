#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_QUEUE_SIZE 20
#define MAX_VERTICES 10
#define TABLE_SIZE 11
//해싱
typedef struct {
    int key;
} element;

typedef struct list
{
    element item;
    struct list* link;
}list;

list* hash_table[TABLE_SIZE];

void initTable(int ht[], int size) {
    for (int i = 0; i < size; i++)
        ht[i] = 0;
}

int hashFunction(int key, int size) {
    return key % size;
}

void hashLpAdd(int item, int ht[], int size) {
    int i, hash_value, cnt = 1;
    hash_value = i = hashFunction(item, size);
    printf("hash_address=%d", i);
    while (!(ht[i] == 0)) {
        i = hashFunction(item + cnt, size);
        cnt++;
        printf("->%d", i);
    }
    ht[i] = item;
    printf("\n");
}

void hashQpAdd(int item, int ht[], int size) {
    int i, hash_value, cnt = 1;
    hash_value = i = hashFunction(item, size);
    printf("hash_address=%d", i);
    while (!(ht[i] == 0)) {
        i = hashFunction(hash_value + cnt * cnt, size);
        cnt++;
        printf("->%d", i);
    }
    ht[i] = item;
    printf("\n");
}

int hashFunction2(int key, int num1, int num2) {
    return (num1 - (key % num2));
}

void hashDhAdd(int item, int ht[], int size, int num1, int num2) {
    int i, hash_value, cnt;
    hash_value = i = hashFunction(item, size);
    cnt = hashFunction2(item, num1, num2);
    printf("hash_address=%d", i);
    while (!(ht[i] == 0)) {
        i = hashFunction((i + cnt), size);
        printf("->%d", i);
    }
    ht[i] = item;
    printf("\n");
}

void hashPrint(int ht[], int size) {
    for (int i = 0; i < size; i++)
        printf("[%2d] -> %d\n", i, ht[i]);
}

void hashPrintProcess(int ht[], int size) {
    for (int i = 0; i < size; i++)
        printf("[%2d] ", ht[i]);
    printf("\n--------------------\n");
}

void hashChainAdd(element item, struct list* ht[]) {
    int hash_value = hashFunction(item.key, TABLE_SIZE);
    list* ptr;
    list* node_before = NULL, * node = ht[hash_value];
    for (; node; node_before = node, node = node->link) {
        if (node->item.key == item.key) {
            fprintf(stderr, "이미 탐색키가 저장되어 있음\n");
            return;
        }
    }
    ptr = (list*)malloc(sizeof(list));
    ptr->item = item;
    ptr->link = NULL;
    if (node_before)
        node_before->link = ptr;
    else
        ht[hash_value] = ptr;
}

void hashChainPrint(list* ht[]) {
    list* node;
    int i;
    for (i = 0; i < TABLE_SIZE; i++) {
        printf("[%2d] -> ", i);
        for (node = ht[i]; node; node = node->link) {
            printf("%2d -> ", node->item.key);
        }
        printf("\n");
    }
}
//해싱함수 끝

//그래프
int visited[MAX_VERTICES];
//인접행렬
typedef struct GraphType1 {
    int node;
    int adjMat[MAX_VERTICES][MAX_VERTICES];
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

void insertEdgeArray(GraphType1* g, int start, int end) {
    if (start >= g->node || end >= g->node) {
        fprintf(stderr, "그래프: 정점 번호 오류");
        return;
    }
    g->adjMat[start][end] = 1;
    g->adjMat[end][start] = 1;
}

void printAdjArray(GraphType1* g) {
    for (int i = 0; i < g->node; i++) {
        for (int j = 0; j < g->node; j++)
            printf("%2d ", g->adjMat[i][j]);
        printf("\n");
    }
}

void dfsMat(GraphType1* g, int v) {                              //깊이우선탐색
    visited[v] = 1;
    printf("[정점 %d ->] ", v);
    for (int w = 0; w < g->node; w++) {
        if (g->adjMat[v][w] && !visited[w])
            dfsMat(g, w);
    }
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

void dfsList(GraphType2* g, int v) {
    GraphNode* w;
    visited[v] = 1;
    printf("[정점 %d ->] ", v);
    for (w = g->adjList[v]; w; w = w->link) {
        if (!visited[w->vertex])
            dfsList(g, w->vertex);
    }
}
//그래프 함수 끝

int main(void) {
    int N, n;
    int elements[] = { 12, 44, 13, 88, 23, 94, 11, 39, 20, 16, 5 };
    int elementsSize = sizeof(elements) / sizeof(int);
    int hashTable[11] = { 0, };
    element e;
    while (1) {
        printf("\n\n0. 프로그램 종료\n");
        printf("1. 해싱\n");
        printf("2. 그래프\n");
        printf("원하는 프로그램을 입력하세요 : ");
        scanf("%d", &N);

        switch (N) {
        case 0: {
            printf("프로그램을 종료합니다.\n");
            return 0;
        }
        case 1:
            printf("\n\n0. 프로그램 종료\n");
            printf("1. 선형조사\n");
            printf("2. 이차원조사\n");
            printf("3. 더블해싱\n");
            printf("4. 체이닝\n");
            printf("원하는 프로그램을 선택하세요 : ");
            scanf("%d", &n);
            printf("\n");
            if (n == 1) {
                printf("\n----------선형조사----------\n\n");
                for (int i = 0; i < elementsSize; i++) {
                    hashLpAdd(elements[i], hashTable, 11);
                    printf("insert %2d  ", elements[i]);
                    hashPrintProcess(hashTable, 11);
                }
                printf("\n최종 >>\n");
                hashPrint(hashTable, 11);
                initTable(hashTable, 11);
                continue;
            }
            else if (n == 2) {
                printf("\n----------이차원조사----------\n\n");
                for (int i = 0; i < elementsSize; i++) {
                    hashQpAdd(elements[i], hashTable, 11);
                    printf("insert %2d  ", elements[i]);
                    hashPrintProcess(hashTable, 11);
                }
                printf("\n최종 >>\n");
                hashPrint(hashTable, 11);
                initTable(hashTable, 11);
                continue;
            }
            else if (n == 3) {
                printf("\n----------더블해싱----------\n\n");
                for (int i = 0; i < elementsSize; i++) {
                    hashDhAdd(elements[i], hashTable, 11, 7, 7);
                    printf("insert %2d  ", elements[i]);
                    hashPrintProcess(hashTable, 11);
                }
                printf("\n최종 >>\n");
                hashPrint(hashTable, 11);
                initTable(hashTable, 11);
                continue;
            }
            else if (n == 4) {
                printf("\n----------체이닝----------\n\n");
                for (int i = 0; i < 11; i++) {
                    e.key = elements[i];
                    hashChainAdd(e, hash_table);
                }
                hashChainPrint(hash_table);
            }
            else if (n == 0) {
                printf("프로그램을 종료합니다\n");
                break;
            }

        case 2: {
            for (int i = 0; i < MAX_VERTICES; i++) {
                visited[i] = 0;
            }
            printf("\n\n0. 프로그램 종료\n");
            printf("1. G1\n");
            printf("2. G2\n");
            printf("3. G3\n");
            printf("그래프를 선택하세요 : ");
            scanf("%d", &n);
            if (n == 1) {
                GraphType1* g = malloc(sizeof(GraphType1));
                initArray(g);
                for (int i = 0; i < 10; i++)
                    insertVertexArray(g);

                insertEdgeArray(g, 0, 1);
                insertEdgeArray(g, 0, 4);
                insertEdgeArray(g, 1, 3);
                insertEdgeArray(g, 1, 6);
                insertEdgeArray(g, 2, 6);
                insertEdgeArray(g, 2, 8);
                insertEdgeArray(g, 2, 9);
                insertEdgeArray(g, 3, 7);
                insertEdgeArray(g, 3, 8);
                insertEdgeArray(g, 4, 5);
                insertEdgeArray(g, 4, 6);
                insertEdgeArray(g, 5, 9);
                insertEdgeArray(g, 7, 9);

                printf("인접행렬 >>\n");
                printAdjArray(g);

                int start;
                printf("\n\nDFS를 시작할 정점을 입력하세요 : ");
                scanf("%d", &start);
                printf("\nDFS >>\n");
                dfsMat(g, start);
                free(g);
                continue;
            }
            else if (n == 2) {
                GraphType2* g = malloc(sizeof(GraphType2));
                initList(g);

                for (int i = 0; i < 10; i++)
                    insertVertexList(g);

                insertEdgeList(g, 0, 4);
                insertEdgeList(g, 0, 1);
                insertEdgeList(g, 1, 6);
                insertEdgeList(g, 1, 0);
                insertEdgeList(g, 2, 9);
                insertEdgeList(g, 2, 6);
                insertEdgeList(g, 3, 8);
                insertEdgeList(g, 3, 7);
                insertEdgeList(g, 4, 6);
                insertEdgeList(g, 4, 5);
                insertEdgeList(g, 4, 0);
                insertEdgeList(g, 5, 9);
                insertEdgeList(g, 5, 4);
                insertEdgeList(g, 6, 4);
                insertEdgeList(g, 6, 2);
                insertEdgeList(g, 6, 1);
                insertEdgeList(g, 7, 3);
                insertEdgeList(g, 8, 3);
                insertEdgeList(g, 9, 5);
                insertEdgeList(g, 9, 2);

                printf("인접 리스트 >>\n");
                printAdjList(g);

                int start;
                printf("\n\nDFS를 시작할 정점 입력을 입력하세요 : ");
                scanf("%d", &start);
                printf("DFS >>\n");
                dfsList(g, start);
                printf("\n정점이 끊어졌습니다.\n");
                for (int i = 0; i < MAX_VERTICES; i++) {
                    if (visited[i] == 0)
                        dfsList(g, i);
                }
                continue;
            }
            else if (n == 3) {
                GraphType2* g;
                g = malloc(sizeof(GraphType2));
                initList(g);

                for (int i = 0; i < 10; i++)
                    insertVertexList(g);

                insertEdgeList(g, 0, 4);
                insertEdgeList(g, 0, 1);
                insertEdgeList(g, 1, 6);
                insertEdgeList(g, 1, 0);
                insertEdgeList(g, 2, 9);
                insertEdgeList(g, 2, 6);
                insertEdgeList(g, 3, 8);
                insertEdgeList(g, 3, 7);
                insertEdgeList(g, 3, 1);
                insertEdgeList(g, 4, 6);
                insertEdgeList(g, 4, 5);
                insertEdgeList(g, 4, 0);
                insertEdgeList(g, 5, 9);
                insertEdgeList(g, 5, 4);
                insertEdgeList(g, 6, 4);
                insertEdgeList(g, 6, 2);
                insertEdgeList(g, 6, 1);
                insertEdgeList(g, 7, 9);
                insertEdgeList(g, 7, 3);
                insertEdgeList(g, 8, 3);
                insertEdgeList(g, 8, 2);
                insertEdgeList(g, 9, 5);
                insertEdgeList(g, 9, 2);

                printf("인접 리스트 >>\n");
                printAdjList(g);

                int start;
                printf("\n\nDFS를 시작할 정점 입력을 입력하세요 : ");
                scanf("%d", &start);
                printf("\nDFS >>\n");
                dfsList(g, start);
                printf("\n");
                for (int i = 0; i < MAX_VERTICES; i++) {
                    if (visited[i] == 0)
                        dfsList(g, i);
                }
                printf("\n");
                continue;
            }
            else if (n == 0) {
                printf("프로그램을 종료합니다.\n");
                break;
            }
        }
        }
        return 0;
    }
}