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
    int left = 2 * k, right = (2 * k) + 1;                              //�ڽ�
    int larger;
    if (right <= len) {                                             //�����ʿ� �ڽ��� ������
        if (arr[left] > arr[right]) {                                 //�� ū�� ã��
            larger = left;
        }
        else larger = right;
    }
    else if (left <= len) {                                          //������ �ڽ� ���� �����ڽĸ� ������
        larger = left;
    }
    else return;                                                //�ڽľ�����

    if (arr[larger] > arr[k]) {                                       //�ʱ��� ����ų� �� �̵��Ҷ� ��������Ʈ�� ������ֱ�����
        printf("[%d, %d] swap\n", arr[k], arr[larger]);                     //�����ϴ� ����.
        int tmp = arr[larger];
        arr[larger] = arr[k];
        arr[k] = tmp;
        heapify(arr, larger, len);                                    //���� ������ ������ �� �Ʒ� �ڽİ��� �ѹ� �� ���غ�����
    }
}

void buildHeap(int* arr, int len) {
    printf("<<<<<<<<<<�ʱ���>>>>>>>>>>\n");
    for (int i = len / 2; i >= 1; i--) {                              //���ݺ��� �����ؼ� �ڽ��� ���� ���� �� �θ������ ����
        heapify(arr, i, len);
    }
    printArray(arr, 1, len);
    printf("\n");
}

void heapSort(int* arr, int len) {
    buildHeap(arr, len);                                          //�ʱ��� �����
    for (int i = len; i >= 2; i--) {
        printf("[%d, %d] swap\n", arr[1], arr[i]);                        //�켱������ ���� ���� 1���� ������ ����                  
        int tmp = arr[1];
        arr[1] = arr[i];
        arr[i] = tmp;
        printf("����>>\n");
        printArray(arr, i, len);

        printf("=============================\n");
        heapify(arr, 1, i - 1);                                       //�� �������� �켱���� ���� ���� ��� ��ġ
        printf("������>>\n");                                       //������ ���̰� 1~n-1 Ȯ���ϱ�����
        printArray(arr, i, len);
        printf("\n");
    }
    printf("=============================\n");
    printf("���� �� ���� :");
    printArray(arr, 1, len);
}

void insert_max_heap(HeapType* h) {
    element e1;
    printf("���� �Է��ϼ��� : ");
    scanf("%d", &e1.value);
    //���Խ���
    int i;
    i = ++(h->heap_size);

    while ((i != 1) && (e1.value > h->heap[i / 2].value)) {					//���������� �߿ö���°Ŷ� �ֻ��� root���� �ö���ų�
        h->heap[i] = h->heap[i / 2];									//�߰��ϰ��� �ϴ� �켱���� ���� �߰��� ��� �θ����� �켱�������� Ŭ������
        i /= 2;															//�߰��ϰ��� �ϴ� ���� �θ𰡵�
    }
    h->heap[i] = e1;													//while���� �ϳ��� �ɷ� ������ �ȴٸ� i �� �����ڸ��� �߰��ϰ����ϴ� �� �߰�.
}

element delete_max_heap(HeapType* h) {
    int parent, child;
    element item, temp;
    element null1 = { NULL };

    if (h->heap_size <= 0) {
        printf("���̻� ������ ��尡 �����ϴ�.");
        return null1;
    }

    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;

    //������ ���� ���°Ŷ� �ƽ������ 1������ �۾����� �׳� ����ϸ��.
    while (child <= h->heap_size) {
        //���� child�� �������� �������� �۰ų� ������ �����ʰ��� �� ũ�� if������ ����
        if ((child < h->heap_size) && (h->heap[child].value < h->heap[child + 1].value))
            //������ ������ �� ũ�ϱ� �����ʰ� �񱳸� �ؾ���. �׷��� child + 1�� ����� �� ū���� �������� ����Ҽ�����.
            child++;
        //delete�� ����� �ϳ� �ٿ���. ��������Ʈ���� ������ ���� ��� ���Ұ���.
        //������ ��尡 ��ó�� root��尡 ������ �� root����� �ڽ��� �켱������ ���� �Ǵ� ���� �켱������ ���Ұ���.
        //������ ����� �켱������ �Ǵٸ� ���ڸ��� �±� ������ ����.
        if (temp.value >= h->heap[child].value) break;

        //�켱������ �ڽĺ��� �۾Ҵٸ� �켱������ ū �ڽ� ���� �θ����� �ڸ� ü����.
        h->heap[parent] = h->heap[child];
        //���� ���� �Űܾ� �� ���� parent�� child�� �ڸ��� �ֱ⶧���� parent�� child�� ���� �̷��� parent�� ������ ����� ��ġ�� ������ parent�� ���� ���ϰ��� �ϴ� ��ġ��� �̾߱� �ؾ���.
        parent = child;
        //�������� child�ڸ����� �� �Ʒ� �ڽ��� �����ϹǷ� child *= 2�� ���־����
        child *= 2;
    }

    //������ �񱳰� ��� ������ �ڱ��ڸ��� ã�Ҵٸ� ���� ���������ִ� ���� parent�ڸ��� �̵��ϰԵ�.
    h->heap[parent] = temp;
    //�켱���� ���ϳ��� ��. ����� ���� return
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

    for (int i = 0; i < 5; i++) {                               //5�ڸ�
        for (int j = 0; j < 8; j++) {                           //0~7
            int z = 0;
            for (int k = 0; k < len; k++) {
                if ((arr[k] / cnt) % 10 == j) {                //10�� �������� �ڸ����� ��
                    enqueue(arr[k]);
                }
            }
        }
        cnt *= 10;                                               //1���ڸ� 10���ڸ� 100���ڸ� ����(8������)
        for (int i = front; i != rear; i++) {
            arr[i] = dequeue();
        }
        printf("%d �ܰ�>>\n", i + 1);
        print_array(arr, len);
        front = rear = 0;
    }
}


int main(void) {
    while (1) {
        int N;
        printf("\n0. ���α׷�����\n");
        printf("1. ������\n");
        printf("2. �켱���� ť\n");
        printf("3. �������\n");
        printf("���ϴ� ���α׷��� �����ϼ��� : ");
        scanf("%d", &N);
        switch (N) {
        case 0: {
            printf("���α׷��� �����մϴ�.\n");
            return 0;
        }
        case 1: {
            int n;
            printf("����� �迭�� ũ�⸦ �Է��ϼ��� : ");
            scanf("%d", &n);
            int* arr = (int*)malloc(sizeof(int) * (n + 1));
            printf("\n�ʱ� �迭 : ");
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
                printf("\n0. ���α׷� ����\n");
                printf("1. ����\n");
                printf("2. ����\n");
                printf("���ϴ� ���α׷��� �Է��ϼ��� : ");
                scanf("%d", &n);
                if (n == 1) {
                    insert_max_heap(heap);
                    printf("\n====================");
                    printf("\n������� �� >>\n");
                    print_list(heap);
                    printf("\n====================\n\n");
                }
                else if (n == 2) {
                    element e1;
                    e1 = delete_max_heap(heap);
                    printf("\n====================\n");
                    printf("�ִ��� : %d\n", e1.value);
                    printf("====================\n\n");
                    printf("\n====================");
                    printf("\n������� �� >>\n");
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
            printf("\n�ʱ� �迭 : ");
            for (int i = 0; i < 10; i++) {
                printf("%d  ", arr[i]);
            }
            printf("\n\n");
            radixSort(arr, 10);
        }
        }
    }
}