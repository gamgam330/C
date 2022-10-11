#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
void PrintArray(int* arr, int left, int right, int len) {
    for (int i = 0; i < len; i++) {
        if (i == left)
            printf("[ %d ", arr[i]);
        else if (i == right)
            printf(" %d ] ", arr[i]);
        else
            printf("%d ", arr[i]);
    }
    printf("\n");
}

void Merge(int* arr, int left, int mid, int right, int len) {
    int i = left, j = mid + 1, t = 0;
    int* tmp = (int*)malloc(sizeof(int) * len);

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) tmp[t++] = arr[i++];
        else tmp[t++] = arr[j++];
    }

    while (i <= mid) tmp[t++] = arr[i++];
    while (j <= right) tmp[t++] = arr[j++];

    i = left, t = 0;
    while (i <= right) arr[i++] = tmp[t++];

    PrintArray(arr, left, right, len);
    free(tmp);
}

void MergeSort(int* arr, int left, int right, int len) {
    int mid;
    if (left < right) {
        mid = (left + right) / 2;
        MergeSort(arr, left, mid, len);
        MergeSort(arr, mid + 1, right, len);
        Merge(arr, left, mid, right, len);
    }
}

void MergeSort1(int* arr, int left, int right, int len) {
    int cnt = 1;
    for (int size = 1; size <= right; size += size) {                                       //size가 기준이 되는것임.
        printf("%d단계 >> \n", cnt);
        cnt++;
        for (int l = 0; l <= right - size; l += (2 * size)) {                               //한사이클 돌때마다 2 * n의 크기만큼 인덱스가 뛰어넘어야함.
            int first = l;
            int mid = l + size - 1;                                                         //size가 늘어나는 범위이기때문에 첫쨋값인 l + size - 1을해주면 중간값이 구해짐
            int last = min(l + (2 * size) - 1, right);                                      //한사이클 돌때마다 비교블록의 갯수는 2 * n개씩 늘어남 예를들어 10개일때 I + 2 * size는 언젠간 16이됨. 그렇게 되면 인덱스 범위에서 넘어감
            Merge(arr, first, mid, last, len);
        }
        printf("\n\n");
    }
}

int main(void) {
    while (1) {
        int N, n;
        printf("0. 프로그램 종료\n");
        printf("1. 병합정렬(순환호출)\n");
        printf("2. 병합정렬(반복문)\n");
        printf("사용할 프로그램을 선택하세요 : ");
        scanf("%d", &N);
        switch (N)
        {
        case 0: {
            printf("프로그램 종료\n");
            return 0;
        }
        case 1: {
            printf("사용할 배열의 크기를 입력하세요 : ");
            scanf("%d", &n);
            int* arr = (int*)malloc(sizeof(int) * n);
            for (int i = 0; i < n; i++) {
                arr[i] = rand() % 100 + 1;
            }
            printf("정렬할 원소 >> ");
            for (int i = 0; i < n; i++) {
                printf("%d  ", arr[i]);
            }
            printf("\n");
            printf("<<<<<<<<<< 병합 정렬 수행 >>>>>>>>>>\n");
            MergeSort(arr, 0, n - 1, n);
            printf("\n최종 병합정렬 ");
            PrintArray(arr, 0, n - 1, n);
            free(arr);
            break;
        }
        case 2: {
            printf("사용할 배열의 크기를 입력하세요 : ");
            scanf("%d", &n);
            int* arr = (int*)malloc(sizeof(int) * n);
            for (int i = 0; i < n; i++) {
                arr[i] = rand() % 100 + 1;
            }
            printf("정렬할 원소 >> ");
            for (int i = 0; i < n; i++) {
                printf("%d  ", arr[i]);
            }
            printf("\n");
            printf("<<<<<<<<<< 병합 정렬 수행 >>>>>>>>>>\n");
            MergeSort1(arr, 0, n - 1, n);

            free(arr);
            break;
        }
        default:
            break;
        }
    }
}