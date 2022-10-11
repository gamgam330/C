#include<stdio.h>
#include<stdlib.h>

void PrintArray(int* arr, int left, int right, int len) {
	for (int i = 0; i < len; i++) {
		if (i == left)
			printf("[ %d ", arr[i]);
		else if (i == right)
			printf(" %d ] ", arr[i]);
		else
			printf("%d ", arr[i]);
	}
	printf("\n\n");
}

void swap(int *arr, int a, int b) {
	int tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}

int cnt = 1;
int partition1(int* arr, int left, int right, int len) {
	int x = arr[right];
	int i = left - 1;														//i ���������� ������ i�� ���� �� j++
	printf("%d�ܰ�>>\n", cnt++);
	printf("[���ذ� : %d]\n", x);
	for (int j = left; j < right; j++) {									//j �����ΰ��� �ϳ��� ��
		if (arr[j] < x) {
			int tmp = arr[++i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}
	}
	int tmp = arr[i + 1];
	arr[i + 1] = arr[right];
	arr[right] = tmp;														//åó�� 2���� ù��°�� ���ذ� ����
	PrintArray(arr, left, right, len);
	return i + 1;															//2���� ù��° �ε����� ��� ������ ���ذ��� ��.
}

int partition2(int* arr, int left, int right, int len) {
	int x = arr[left];
	int i = left;															
	printf("%d�ܰ�>>\n", cnt++);
	printf("[���ذ� : %d]\n", x);
	for (int j = left+1; j <= right; j++) {									
		if (arr[j] < x) {
			int tmp = arr[++i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}
	}
	int tmp = arr[i];
	arr[i] = arr[left];
	arr[left] = tmp;														
	PrintArray(arr, left, right, len);
	return i;
}

int partition3(int* arr, int left, int right, int len) {
	int x = arr[left];
	int left_mark = left + 1, right_mark = right;
	printf("%d�ܰ�>>\n", cnt++);
	printf("[���ذ� : %d]\n", x);
	while (left_mark <= right_mark) {
		while (arr[left_mark] <= x) {
			left_mark++;
		}
		while (arr[right_mark] > x) {
			right_mark--;
		}
		if (left_mark < right_mark) {
			swap(arr, left_mark, right_mark);
		}
	}
	swap(arr, left, right_mark);
	PrintArray(arr, left, right, len);
	return right_mark;
}

void qickSort1(int* arr, int left, int right, int len) {
	if (left < right) {
		int mid = partition1(arr, left, right, len);
		qickSort1(arr, left, mid - 1, len);
		qickSort1(arr, mid + 1, right, len);
	}
}

void qickSort2(int* arr, int left, int right, int len) {
	if (left < right) {
		int mid = partition2(arr, left, right, len);
		qickSort2(arr, left, mid - 1, len);
		qickSort2(arr, mid + 1, right, len);
	}
}

void qickSort3(int* arr, int left, int right, int len) {
	if (left < right) {
		int mid = partition3(arr, left, right, len);
		qickSort3(arr, left, mid - 1, len);
		qickSort3(arr, mid + 1, right, len);
	}
}

int main(void) {
	while (1) {
		int N;
		printf("0. ���α׷�����\n");
		printf("1. ���������� �������� Ȯ���ϱ�\n");
		printf("2. ù��°���� �������� Ȯ���ϱ�\n");
		printf("3. ���ʿ��� Ȯ���ϱ�\n");
		printf("���ϴ� ���α׷��� �����ϼ��� : ");
		scanf("%d", &N);
		switch (N)
		{
		case 0: {
			printf("���α׷��� �����մϴ�.");
			return 0;
		}
		case 1: {
			cnt = 1;
			int n;
			printf("�迭�� ũ�⸦ �Է��ϼ��� : ");
			scanf("%d", &n);
			int* arr = (int*)malloc(sizeof(int) * n);
			printf("������ �迭 : ");
			for (int i = 0; i < n; i++) {
				arr[i] = rand() % 100 + 1;
				printf("%d  ", arr[i]);
			}
			printf("\n");
			qickSort1(arr, 0, n - 1, n);
			break;
		}
		case 2: {
			cnt = 1;
			int n;
			printf("�迭�� ũ�⸦ �Է��ϼ��� : ");
			scanf("%d", &n);
			int* arr = (int*)malloc(sizeof(int) * n);
			printf("������ �迭 : ");
			for (int i = 0; i < n; i++) {
				arr[i] = rand() % 100 + 1;
				printf("%d  ", arr[i]);
			}
			printf("\n");
			qickSort2(arr, 0, n - 1, n);
			break;
		}
		case 3: {
			cnt = 1;
			int n;
			printf("�迭�� ũ�⸦ �Է��ϼ��� : ");
			scanf("%d", &n);
			int* arr = (int*)malloc(sizeof(int) * n);
			printf("������ �迭 : ");
			for (int i = 0; i < n; i++) {
				arr[i] = rand() % 100 + 1;
				printf("%d  ", arr[i]);
			}
			printf("\n");
			qickSort3(arr, 0, n - 1, n);
			break;
		}
		default:
			break;
		}
	}
}