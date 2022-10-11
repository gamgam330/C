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
    for (int size = 1; size <= right; size += size) {                                       //size�� ������ �Ǵ°���.
        printf("%d�ܰ� >> \n", cnt);
        cnt++;
        for (int l = 0; l <= right - size; l += (2 * size)) {                               //�ѻ���Ŭ �������� 2 * n�� ũ�⸸ŭ �ε����� �پ�Ѿ����.
            int first = l;
            int mid = l + size - 1;                                                         //size�� �þ�� �����̱⶧���� ù¶���� l + size - 1�����ָ� �߰����� ������
            int last = min(l + (2 * size) - 1, right);                                      //�ѻ���Ŭ �������� �񱳺���� ������ 2 * n���� �þ ������� 10���϶� I + 2 * size�� ������ 16�̵�. �׷��� �Ǹ� �ε��� �������� �Ѿ
            Merge(arr, first, mid, last, len);
        }
        printf("\n\n");
    }
}

int main(void) {
    while (1) {
        int N, n;
        printf("0. ���α׷� ����\n");
        printf("1. ��������(��ȯȣ��)\n");
        printf("2. ��������(�ݺ���)\n");
        printf("����� ���α׷��� �����ϼ��� : ");
        scanf("%d", &N);
        switch (N)
        {
        case 0: {
            printf("���α׷� ����\n");
            return 0;
        }
        case 1: {
            printf("����� �迭�� ũ�⸦ �Է��ϼ��� : ");
            scanf("%d", &n);
            int* arr = (int*)malloc(sizeof(int) * n);
            for (int i = 0; i < n; i++) {
                arr[i] = rand() % 100 + 1;
            }
            printf("������ ���� >> ");
            for (int i = 0; i < n; i++) {
                printf("%d  ", arr[i]);
            }
            printf("\n");
            printf("<<<<<<<<<< ���� ���� ���� >>>>>>>>>>\n");
            MergeSort(arr, 0, n - 1, n);
            printf("\n���� �������� ");
            PrintArray(arr, 0, n - 1, n);
            free(arr);
            break;
        }
        case 2: {
            printf("����� �迭�� ũ�⸦ �Է��ϼ��� : ");
            scanf("%d", &n);
            int* arr = (int*)malloc(sizeof(int) * n);
            for (int i = 0; i < n; i++) {
                arr[i] = rand() % 100 + 1;
            }
            printf("������ ���� >> ");
            for (int i = 0; i < n; i++) {
                printf("%d  ", arr[i]);
            }
            printf("\n");
            printf("<<<<<<<<<< ���� ���� ���� >>>>>>>>>>\n");
            MergeSort1(arr, 0, n - 1, n);

            free(arr);
            break;
        }
        default:
            break;
        }
    }
}