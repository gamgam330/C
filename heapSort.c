#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 20

typedef struct {
    int value;
}element;

typedef struct {
    element heap[MAX_SIZE];
    int heap_size;
}HeapType;

HeapType* create() {
    return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h) {
    h->heap_size = 0;
}

void printArray(int* arr, int start, int end) {
    int len = end;
    for (int i = 1; i <= len; i++) {
        if (i == start && i == end)
            printf("[ %d ]", arr[i]);
        else if (i == start)
            printf("[ %d ", arr[i]);
        else if (i == len)
            printf(" %d ] ", arr[i]);
        else
            printf("%d ", arr[i]);
    }
    printf("\n");
}

void heapify(int* arr, int k, int len) {
    int left = 2 * k, right = (2 * k) + 1;                              //자식
    int larger;
    if (right <= len) {                                             //오른쪽에 자식이 있으면
        if (arr[left] > arr[right]) {                                 //더 큰값 찾기
            larger = left;
        }
        else larger = right;
    }
    else if (left <= len) {                                          //오른쪽 자식 없고 왼쪽자식만 잇으면
        larger = left;
    }
    else return;                                                //자식없을때

    if (arr[larger] > arr[k]) {                                       //초기힙 만들거나 값 이동할때 완전이진트리 만들어주기위해
        printf("[%d, %d] swap\n", arr[k], arr[larger]);                     //스왑하는 구간.
        int tmp = arr[larger];
        arr[larger] = arr[k];
        arr[k] = tmp;
        heapify(arr, larger, len);                                    //만약 스왑이 있으면 그 아래 자식과도 한번 더 비교해봐야함
    }
}

void buildHeap(int* arr, int len) {
    printf("<<<<<<<<<<초기힙>>>>>>>>>>\n");
    for (int i = len / 2; i >= 1; i--) {                              //절반부터 시작해서 자식을 가진 제일 밑 부모노드부터 시작
        heapify(arr, i, len);
    }
    printArray(arr, 1, len);
    printf("\n");
}

void heapSort(int* arr, int len) {
    buildHeap(arr, len);                                          //초기힙 만들기
    for (int i = len; i >= 2; i--) {
        printf("[%d, %d] swap\n", arr[1], arr[i]);                        //우선순위가 제일 높은 1번과 마지막 스왑                  
        int tmp = arr[1];
        arr[1] = arr[i];
        arr[i] = tmp;
        printf("정렬>>\n");
        printArray(arr, i, len);

        printf("=============================\n");
        heapify(arr, 1, i - 1);                                       //힙 마지막에 우선순위 제일 높은 노드 배치
        printf("힙상태>>\n");                                       //사이즈 줄이고 1~n-1 확인하기위해
        printArray(arr, i, len);
        printf("\n");
    }
    printf("=============================\n");
    printf("최종 힙 정렬 :");
    printArray(arr, 1, len);
}

void insert_max_heap(HeapType* h) {
    element e1;
    printf("수를 입력하세요 : ");
    scanf("%d", &e1.value);
    //삽입시작
    int i;
    i = ++(h->heap_size);

    while ((i != 1) && (e1.value > h->heap[i / 2].value)) {					//마지막부터 쭉올라오는거라 최상위 root까지 올라오거나
        h->heap[i] = h->heap[i / 2];									//추가하고자 하는 우선순위 값이 추가된 노드 부모노드의 우선순위보다 클때까지
        i /= 2;															//추가하고자 하는 것이 부모가됨
    }
    h->heap[i] = e1;													//while에서 하나라도 걸려 나오게 된다면 i 즉 현재자리에 추가하고자하는 값 추가.
}

element delete_max_heap(HeapType* h) {
    int parent, child;
    element item, temp;
    element null1 = { NULL };

    if (h->heap_size <= 0) {
        printf("더이상 삭제할 노드가 없습니다.");
        return null1;
    }

    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;

    //위에서 부터 보는거라 맥스사이즈가 1번까지 작아지면 그냥 출력하면됨.
    while (child <= h->heap_size) {
        //만약 child가 현재노드의 갯수보다 작거나 형제중 오른쪽값이 더 크면 if문으로 진입
        if ((child < h->heap_size) && (h->heap[child].value < h->heap[child + 1].value))
            //오른쪽 형제가 더 크니까 오른쪽과 비교를 해야함. 그래서 child + 1을 해줘야 그 큰값을 기준으로 계산할수있음.
            child++;
        //delete라 사이즈를 하나 줄였음. 완전이진트리라 마지막 값을 들고 비교할것임.
        //마지막 노드가 맨처음 root노드가 됐으니 그 root노드의 자식중 우선순위가 가장 컸던 노드와 우선순위를 비교할것임.
        //마지막 노드의 우선순위가 컸다면 그자리가 맞기 때문에 종료.
        if (temp.value >= h->heap[child].value) break;

        //우선순위가 자식보다 작았다면 우선순위가 큰 자식 노드와 부모노드의 자리 체인지.
        h->heap[parent] = h->heap[child];
        //이제 내가 옮겨야 할 값인 parent는 child의 자리에 있기때문에 parent에 child를 대입 이렇게 parent를 마지막 노드의 위치라 생각해 parent를 현재 비교하고자 하는 위치라고 이야기 해야함.
        parent = child;
        //이제부턴 child자리에서 그 아래 자식을 봐야하므로 child *= 2를 해주어야함
        child *= 2;
    }

    //위에서 비교가 모두 끝나고 자기자리를 찾았다면 제일 마지막에있던 노드는 parent자리로 이동하게됨.
    h->heap[parent] = temp;
    //우선순위 제일높은 값. 출력을 위해 return
    return item;
}

void print_list(HeapType* h) {
    for (int i = 1; i <= h->heap_size; i++) {
        printf("%d ", h->heap[i].value);
    }
}

void print_array(int* arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d         ", arr[i]);
    }
    printf("\n");
}

int queue[MAX_SIZE];
int front, rear = 0;

int enqueue(int k) {
    if ((rear + 1) % MAX_SIZE == front) {
        return -1;
    }
    else {
        queue[rear] = k;
        rear = ++rear % MAX_SIZE;
        return 1;
    }
}

int dequeue() {
    int k;
    if (front == rear) {
        return -1;
    }
    else {
        k = queue[front];
        front = ++front % MAX_SIZE;
        return k;
    }
}

void  radixSort(int* arr, int len) {
    int bucket[8][MAX_SIZE] = { NULL, };
    int cnt = 1;

    for (int i = 0; i < 5; i++) {                               //5자리
        for (int j = 0; j < 8; j++) {                           //0~7
            int z = 0;
            for (int k = 0; k < len; k++) {
                if ((arr[k] / cnt) % 10 == j) {                //10개 데이터의 자리수별 비교
                    enqueue(arr[k]);
                }
            }
        }
        cnt *= 10;                                               //1의자리 10의자리 100의자리 보기(8진수용)
        for (int i = front; i != rear; i++) {
            arr[i] = dequeue();
        }
        printf("%d 단계>>\n", i + 1);
        print_array(arr, len);
        front = rear = 0;
    }
}


int main(void) {
    while (1) {
        int N;
        printf("\n0. 프로그램종료\n");
        printf("1. 힙정렬\n");
        printf("2. 우선순위 큐\n");
        printf("3. 기수정렬\n");
        printf("원하는 프로그램을 선택하세요 : ");
        scanf("%d", &N);
        switch (N) {
        case 0: {
            printf("프로그램을 종료합니다.\n");
            return 0;
        }
        case 1: {
            int n;
            printf("사용할 배열의 크기를 입력하세요 : ");
            scanf("%d", &n);
            int* arr = (int*)malloc(sizeof(int) * (n + 1));
            printf("\n초기 배열 : ");
            for (int i = 1; i <= n; i++) {
                arr[i] = rand() % 100 + 1;
                printf("%d  ", arr[i]);
            }
            printf("\n\n");
            heapSort(arr, n);
            free(arr);
            break;
        }
        case 2: {
            int n;
            HeapType* heap;
            heap = create();
            init(heap);
            while (1) {
                printf("\n0. 프로그램 종료\n");
                printf("1. 삽입\n");
                printf("2. 삭제\n");
                printf("원하는 프로그램을 입력하세요 : ");
                scanf("%d", &n);
                if (n == 1) {
                    insert_max_heap(heap);
                    printf("\n====================");
                    printf("\n대기중인 힙 >>\n");
                    print_list(heap);
                    printf("\n====================\n\n");
                }
                else if (n == 2) {
                    element e1;
                    e1 = delete_max_heap(heap);
                    printf("\n====================\n");
                    printf("최대힙 : %d\n", e1.value);
                    printf("====================\n\n");
                    printf("\n====================");
                    printf("\n대기중인 힙 >>\n");
                    print_list(heap);
                    printf("\n====================\n\n");
                }
                else if (n == 0) {
                    break;
                }
            }

        }
        case 3: {
            int arr[10] = { 12345, 21537, 32571, 24063, 76451, 60157, 40726, 54625, 54637, 23014 };
            printf("\n초기 배열 : ");
            for (int i = 0; i < 10; i++) {
                printf("%d  ", arr[i]);
            }
            printf("\n\n");
            radixSort(arr, 10);
        }
        }
    }
}