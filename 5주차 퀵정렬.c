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
	int i = left - 1;														//i 더작은값이 나오면 i와 스왑 후 j++
	printf("%d단계>>\n", cnt++);
	printf("[기준값 : %d]\n", x);
	for (int j = left; j < right; j++) {									//j 앞으로가며 하나씩 비교
		if (arr[j] < x) {
			int tmp = arr[++i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}
	}
	int tmp = arr[i + 1];
	arr[i + 1] = arr[right];
	arr[right] = tmp;														//책처럼 2구간 첫번째와 기준값 스왑
	PrintArray(arr, left, right, len);
	return i + 1;															//2구간 첫번째 인덱스가 방금 정렬한 기준값이 됨.
}

int partition2(int* arr, int left, int right, int len) {
	int x = arr[left];
	int i = left;															
	printf("%d단계>>\n", cnt++);
	printf("[기준값 : %d]\n", x);
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
	printf("%d단계>>\n", cnt++);
	printf("[기준값 : %d]\n", x);
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
		printf("0. 프로그램종료\n");
		printf("1. 마지막값을 기준으로 확인하기\n");
		printf("2. 첫번째값을 기준으로 확인하기\n");
		printf("3. 양쪽에서 확인하기\n");
		printf("원하는 프로그램을 선택하세요 : ");
		scanf("%d", &N);
		switch (N)
		{
		case 0: {
			printf("프로그램을 종료합니다.");
			return 0;
		}
		case 1: {
			cnt = 1;
			int n;
			printf("배열의 크기를 입력하세요 : ");
			scanf("%d", &n);
			int* arr = (int*)malloc(sizeof(int) * n);
			printf("정렬전 배열 : ");
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
			printf("배열의 크기를 입력하세요 : ");
			scanf("%d", &n);
			int* arr = (int*)malloc(sizeof(int) * n);
			printf("정렬전 배열 : ");
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
			printf("배열의 크기를 입력하세요 : ");
			scanf("%d", &n);
			int* arr = (int*)malloc(sizeof(int) * n);
			printf("정렬전 배열 : ");
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