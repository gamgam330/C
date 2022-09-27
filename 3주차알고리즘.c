#include <stdio.h>
#include <stdlib.h>

void SelectionSort(int* arr, int len) {                        //���������� �Ǿտ� ����ֱ�
    int cnt = 0, result = 0, k;
    for (int i = 0; i < len - 1; i++) {
        printf("%d�ܰ� : ", i + 1);
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
        printf("   /   [%d]�� ���߽��ϴ�.\n", cnt);
    }
    printf("���ĵ� �迭 : ");
    for (int i = 0; i < len; i++) {
        printf("%d  ", arr[i]);
    }
    printf("\n\n");
    printf("�� ���� Ƚ�� : %d\n\n", result);
}

void InsertionSort(int* arr, int len) {                        //����ؼ� �ѱ� �о�� �ڱ��ڸ� ã���� ����
    int cnt = 0, result = 0, front, j, k;
    for (int i = 1; i < len; i++) {
        front = arr[i];
        printf("%d�ܰ� : ", i);
        cnt = 0;
        for (j = i - 1; j >= 0 && arr[j] > front; j--) {            //������ ���ų�(�ε���0) �տ������� ���簪�� ũ�ٸ� ����
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
        printf("   /   [%d]�� ���߽��ϴ�.\n", cnt);
        result += cnt;
    }
    printf("���ĵ� �迭 : ");
    for (int i = 0; i < len; i++) {
        printf("%3d", arr[i]);
    }
    printf("\n\n");
    printf("�� ���� Ƚ�� : %d\n\n", result);
}

void BubbleSort(int* arr, int len) {                        //�տ������� �ΰ��� �� �� ����
    int cnt = 0, result = 0, tip = 0, N;
    printf("1. ��ȯ�� �Ͼ�� �ʴ´ٸ� ����\n");
    printf("2. ���� ���X\n");
    printf("���� �ɼ��� �������ּ��� : ");
    scanf("%d", &N);
    for (int i = 0; i < len - 1; i++) {
        printf("\n%d�ܰ�>>>\n", i + 1);
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
                printf("           [%d]�� ���߽��ϴ�.\n", cnt);
                printf("������ �������ϴ�. \n");
                break;
            }
            result += cnt;
            printf("           [%d]�� ���߽��ϴ�.\n", cnt);
        }
        else if (N == 2) {
            result += cnt;
            printf("           [%d]�� ���߽��ϴ�.\n", cnt);
        }
    }
    printf("���ĵ� �迭 : ");
    for (int i = 0; i < len; i++) {
        printf("%d  ", arr[i]);
    }
    printf("\n\n");
    printf("�� ���� Ƚ�� : %d\n\n", result);
}

int main(void) {
    int N, n;
    while (1) {
        printf("0. ���α׷�����\n");
        printf("1. ��������\n");
        printf("2. ��������\n");
        printf("3. ��������\n");
        printf("���ϴ� ���α׷��� �Է��ϼ��� : ");
        scanf("%d", &N);
        //int arr[10] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
        switch (N)
        {
        case 0: {
            printf("���α׷��� �����մϴ�.");
            return 0;
        }
        case 1: {
            printf("����� �迭�� ũ�⸦ �Է��ϼ��� : ");
            scanf("%d", &n);
            int* arr = (int*)malloc(sizeof(int) * n);
            for (int i = 0; i < n; i++) {
                arr[i] = rand() % 100 + 1;
            }
            printf("������ �迭 : ");
            for (int i = 0; i < n; i++) {
                printf("%d  ", arr[i]);
            }
            printf("\n");
            printf("        <<<<<<<<<<���� ���� ����>>>>>>>>>>\n");
            SelectionSort(arr, n);
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
            printf("������ �迭 : ");
            for (int i = 0; i < n; i++) {
                printf("%d  ", arr[i]);
            }
            printf("\n");
            printf("        <<<<<<<<<<���� ���� ����>>>>>>>>>>\n");
            InsertionSort(arr, n);
            free(arr);
            break;
        }
        case 3: {
            printf("����� �迭�� ũ�⸦ �Է��ϼ��� : ");
            scanf("%d", &n);
            int* arr = (int*)malloc(sizeof(int) * n);
            for (int i = 0; i < n; i++) {
                arr[i] = rand() % 100 + 1;
            }
            printf("������ �迭 : ");
            for (int i = 0; i < n; i++) {
                printf("%d  ", arr[i]);
            }
            printf("\n");
            printf("    <<<<<<<<<<���� ���� ����>>>>>>>>>>\n");
            BubbleSort(arr, n);
            free(arr);
            break;
        }
        default:
            break;
        }
    }
}