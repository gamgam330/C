#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode {
    int data;
    struct ListNode* link;
}ListNode;

ListNode* insert(ListNode* head, int value) {
    ListNode* p = malloc(sizeof(ListNode));
    p->data = value;
    p->link = head;
    head = p;
    return head;
}

void BubleSort(int* arr, int len) {
    int temp;
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
int max1 = 0;
int BinarySearch(int* arr, int key, int end) {
    int len = 1, start = 0;
    while (start <= end) {
        int mid = (start + end) / 2;
        printf("인덱스[%d] ~ 인덱스[%d]의 탐색\n", start, end);
        printf("중간값 [%d]와 찾고자하는수 [%d] 비교 중\n", arr[mid], key);
        if (arr[mid] == key) {
            printf("!!!찾았습니다!!!\n[%d]번 비교 / [%d]는 [%d]번째 인덱스에 존재합니다.\n", len, key, mid);
            if (max1 < len) {
                max1 = len;
            }
            return len;
        }
        else if (arr[mid] < key) {
            printf("[%d]가 [%d]보다 작습니다. \n오른쪽으로 이동하겠습니다.\n\n", arr[mid], key);
            start = mid + 1;
            len++;
        }
        else {
            printf("[%d]가 [%d]보다 큽니다.\n왼쪽으로 이동하겠습니다.\n\n", arr[mid], key);
            end = mid - 1;
            len++;
        }
    }
    printf("[%d]번 비교 / %d는 배열에 없습니다.\n", len - 1, key);
    if (max1 < len) {
        max1 = len - 1;
    }
    return len - 1;
}

int* marge(int* arr1, int* arr2, int len1, int len2) {
    int* arr = (int*)malloc(sizeof(int) * (len1 + len2));
    int i = 0, j = 0, k = 0;

    while (i < len1 && j < len2) {
        if (arr1[i] < arr2[j]) {
            arr[k++] = arr1[i++];
        }
        else
            arr[k++] = arr2[j++];
    }
    while (i < len1) arr[k++] = arr1[i++];
    while (j < len2) arr[k++] = arr2[j++];

    return arr;
}

ListNode* MergeList(ListNode* list1, ListNode* list2) {
    ListNode* list3 = NULL;                      //저장시킬 값
    ListNode* tmp = NULL;                        //이동시킬 값

    if (list1->data < list2->data) {
        list3 = list1;                            //list1(head)값을 똑같이 받음
        tmp = list3;                              //동일
        list1 = list1->link;                      //list1->link를 연결해 다음값을 유지해줌.
    }
    else {
        list3 = list2;
        tmp = list3;
        list2 = list2->link;
    }

    while (list1 != NULL && list2 != NULL) {     //첫값이 아니면 마지막 값에 넣어줘야함
        if (list1->data <= list2->data) {
            tmp->link = list1;                     //tmp를 이용해 이동
            tmp = list1;                           //현재 위치 이동
            list1 = list1->link;                   //다음위치 이동
        }
        else {
            tmp->link = list2;
            tmp = list2;
            list2 = list2->link;
        }
    }
    if (list1 == NULL) tmp->link = list2;        //나머지 남은값
    else tmp->link = list1;
    return list3;
}

void PrintList(ListNode* head) {
    for (ListNode* p = head; p != NULL; p = p->link)
        printf("%d ", p->data);
    printf("\n");
}

int cnt = 0;
int hanoi(int n, char from, char tmp, char to) {

    if (n == 1) {
        cnt++;
        printf("<1> 원판을 <%c>에서 <%c>로 옮깁니다.\n", from, to);
    }
    else {
        hanoi(n - 1, from, to, tmp);
        cnt++;
        printf("<%d> 원판을 <%c>에서 <%c>로 옮깁니다.\n", n, from, to);
        hanoi(n - 1, tmp, from, to);
    }
    return cnt;
}

int main(void) {
    int N;
    while (1) {
        printf("\n0. 프로그램종료\n");
        printf("1. 이진탐색\n");
        printf("2. 병합\n");
        printf("3. 하노이 탑\n");
        printf("원하는 프로그램 선택 : ");
        scanf("%d", &N);
        int arr1[] = { 5,7,24,56 };
        int arr2[] = { 19,45,61,79,92 };
        int len1 = sizeof(arr1) / sizeof(int);
        int len2 = sizeof(arr2) / sizeof(int);
        switch (N)
        {
        case 1: {
            max1 = 0;
            int n;
            int y;
            printf("1. 모두 찾기\n");
            printf("2. 모두 틀리기\n");
            printf("옵션을 선택하세요 : ");
            scanf("%d", &y);
            if (y == 1) {
                printf("배열의 크기를 입력하세요 : ");
                scanf("%d", &n);
                int* arr3 = (int*)malloc(sizeof(int) * n);
                for (int i = 0; i < n; i++) {
                    arr3[i] = rand() % 100 + 1;
                }
                int find;
                double total = 0;
                BubleSort(arr3, n);
                printf("현재 배열 : ");
                for (int i = 0; i < n; i++) {
                    printf("%d  ", arr3[i]);
                }
                for (int i = 0; i < n; i++) {
                    printf("\n찾고자 하는 수를 입력하세요 : ");
                    scanf("%d", &find);
                    printf("===================================================================\n");
                    total += BinarySearch(arr3, find, n - 1);
                    printf("===================================================================\n");
                }
                printf("최악의 경우 : %d\n", max1);
                printf("탐색 평균 : %lf\n", total / n);
                break;
            }
            else if (y == 2) {
                max1 = 0;
                printf("배열의 크기를 입력하세요 : ");
                scanf("%d", &n);
                int* arr3 = (int*)malloc(sizeof(int) * n);
                for (int i = 0; i < n; i++) {
                    arr3[i] = rand() % 100 + 1;
                }
                int find;
                double total = 0;
                BubleSort(arr3, n);
                printf("현재 배열 : ");
                for (int i = 0; i < n; i++) {
                    printf("%d  ", arr3[i]);
                }
                for (int i = 0; i < n + 1; i++) {
                    printf("\n찾고자 하는 수를 입력하세요 : ");
                    scanf("%d", &find);
                    printf("===================================================================\n");
                    total += BinarySearch(arr3, find, n - 1);
                    printf("===================================================================\n");
                }
                printf("최악의 경우 : %d\n", max1);
                printf("탐색 평균 : %lf\n", total / (n + 1));
                break;
            }
        }
        case 2: {
            int n;
            printf("\n1. 배열이용\n");
            printf("\n2. 연결리스트 이용\n");
            printf("원하는 옵션을 선택하세요 :");
            scanf("%d", &n);
            if (n == 1) {
                int* arr3 = marge(arr1, arr2, len1, len2);
                printf("===================================================================\n");
                printf("첫 번째 배열 : ");
                for (int i = 0; i < len1; i++) {
                    printf("%d  ", arr1[i]);
                }
                printf("\n두 번째 배열 : ");
                for (int i = 0; i < len2; i++) {
                    printf("%d  ", arr2[i]);
                }
                printf("\n병합된 배열 : ");
                for (int i = 0; i < (len1 + len2); i++) {
                    printf("%d  ", arr3[i]);
                }
                printf("\n===================================================================\n");
                break;
            }
            else if (n == 2) {
                ListNode* list1 = NULL;
                ListNode* list2 = NULL;

                for (int i = len1 - 1; i >= 0; i--) list1 = insert(list1, arr1[i]);
                for (int i = len2 - 1; i >= 0; i--) list2 = insert(list2, arr2[i]);
                printf("===================================================================\n");
                printf("첫 번째 리스트 : ");
                PrintList(list1);
                printf("두 번째 리스트 : ");
                PrintList(list2);
                printf("병합된 리스트 : ");
                PrintList(MergeList(list1, list2));
                printf("===================================================================\n");
                break;
            }
        }
        case 3: {
            int n;
            cnt = 0;
            printf("하노이탑의 높이를 입력하세요 : ");
            scanf("%d", &n);
            printf("===================================================================\n");
            int num = hanoi(n, 'A', 'B', 'C');
            printf("이동한 횟수 : %d\n", num);
            printf("===================================================================\n");
        }
        default:
            break;
        }
    }

}