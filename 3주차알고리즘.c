#include <stdio.h>
#include <stdlib.h>

void SelectionSort(int* arr, int len) {                        //작은값부터 맨앞에 집어넣기
    int cnt = 0, result = 0, k;
    for (int i = 0; i < len - 1; i++) {
        printf("%d단계 : ", i + 1);
        int min = i;
        cnt = 0;
        for (int j = i + 1; j < len; j++) {
            cnt++;
            if (arr[min] > arr[j]) {
                min = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
        printf("[");
        for (k = 0; k < i + 1; k++) {
            printf("%4d", arr[k]);
        }
        printf("   ]");
        for (; k < len; k++) {
            printf("%4d", arr[k]);
        }
        result += cnt;
        printf("   /   [%d]번 비교했습니다.\n", cnt);
    }
    printf("정렬된 배열 : ");
    for (int i = 0; i < len; i++) {
        printf("%d  ", arr[i]);
    }
    printf("\n\n");
    printf("총 비교한 횟수 : %d\n\n", result);
}

void InsertionSort(int* arr, int len) {                        //계속해서 한깐씩 밀어내다 자기자리 찾으면 들어가기
    int cnt = 0, result = 0, front, j, k;
    for (int i = 1; i < len; i++) {
        front = arr[i];
        printf("%d단계 : ", i);
        cnt = 0;
        for (j = i - 1; j >= 0 && arr[j] > front; j--) {            //전값이 없거나(인덱스0) 앞에값보다 현재값이 크다면 종료
            cnt++;
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = front;
        printf("[");
        for (k = 0; k <= i; k++) {
            printf("%4d", arr[k]);
        }
        printf("  ]");
        for (; k < len; k++) {
            printf("%4d", arr[k]);
        }
        cnt += 1;
        printf("   /   [%d]번 비교했습니다.\n", cnt);
        result += cnt;
    }
    printf("정렬된 배열 : ");
    for (int i = 0; i < len; i++) {
        printf("%3d", arr[i]);
    }
    printf("\n\n");
    printf("총 비교한 횟수 : %d\n\n", result);
}

void BubbleSort(int* arr, int len) {                        //앞에서부터 두개씩 비교 후 스왑
    int cnt = 0, result = 0, tip = 0, N;
    printf("1. 교환이 일어나지 않는다면 종료\n");
    printf("2. 종료 사용X\n");
    printf("종료 옵션을 선택해주세요 : ");
    scanf("%d", &N);
    for (int i = 0; i < len - 1; i++) {
        printf("\n%d단계>>>\n", i + 1);
        cnt = 0;
        tip = 0;
        for (int j = 0; j < len - i - 1; j++) {
            cnt++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                tip++;
            }
            for (int k = 0; k < len; k++) {
                printf("%4d", arr[k]);
            }
            printf("\n");
        }
        if (N == 1) {
            if (tip == 0) {
                result += cnt;
                printf("           [%d]번 비교했습니다.\n", cnt);
                printf("정렬이 끝났습니다. \n");
                break;
            }
            result += cnt;
            printf("           [%d]번 비교했습니다.\n", cnt);
        }
        else if (N == 2) {
            result += cnt;
            printf("           [%d]번 비교했습니다.\n", cnt);
        }
    }
    printf("정렬된 배열 : ");
    for (int i = 0; i < len; i++) {
        printf("%d  ", arr[i]);
    }
    printf("\n\n");
    printf("총 비교한 횟수 : %d\n\n", result);
}

int main(void) {
    int N, n;
    while (1) {
        printf("0. 프로그램종료\n");
        printf("1. 선택정렬\n");
        printf("2. 삽입정렬\n");
        printf("3. 버블정렬\n");
        printf("원하는 프로그램을 입력하세요 : ");
        scanf("%d", &N);
        //int arr[10] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
        switch (N)
        {
        case 0: {
            printf("프로그램을 종료합니다.");
            return 0;
        }
        case 1: {
            printf("사용할 배열의 크기를 입력하세요 : ");
            scanf("%d", &n);
            int* arr = (int*)malloc(sizeof(int) * n);
            for (int i = 0; i < n; i++) {
                arr[i] = rand() % 100 + 1;
            }
            printf("정렬할 배열 : ");
            for (int i = 0; i < n; i++) {
                printf("%d  ", arr[i]);
            }
            printf("\n");
            printf("        <<<<<<<<<<선택 정렬 수행>>>>>>>>>>\n");
            SelectionSort(arr, n);
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
            printf("정렬할 배열 : ");
            for (int i = 0; i < n; i++) {
                printf("%d  ", arr[i]);
            }
            printf("\n");
            printf("        <<<<<<<<<<삽입 정렬 수행>>>>>>>>>>\n");
            InsertionSort(arr, n);
            free(arr);
            break;
        }
        case 3: {
            printf("사용할 배열의 크기를 입력하세요 : ");
            scanf("%d", &n);
            int* arr = (int*)malloc(sizeof(int) * n);
            for (int i = 0; i < n; i++) {
                arr[i] = rand() % 100 + 1;
            }
            printf("정렬할 배열 : ");
            for (int i = 0; i < n; i++) {
                printf("%d  ", arr[i]);
            }
            printf("\n");
            printf("    <<<<<<<<<<버블 정렬 수행>>>>>>>>>>\n");
            BubbleSort(arr, n);
            free(arr);
            break;
        }
        default:
            break;
        }
    }
}