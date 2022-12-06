#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX(a,b,c) (((a) > (b)) ? (((c)>(a))?(c):(a)) : (((c)>(b))?(c):(b)))

int arr[][5] = { {2,5,1,3,6},{3,14,25,11,2},{23,13,24,3,2,},{1,19,7,9,8},{18,21,5,8,2} };
int arr2[][6] = { {0,0,0,0,0,0}, { 0,2,5,1,3,6 },{0,3,14,25,11,2},{0,23,13,24,3,2,},{0,1,19,7,9,8},{0,18,21,5,8,2} };
int c[5][5];
int arr1[][4] = { {6,7,12,5},{5,3,11,18},{7,17,3,3},{8,10,14,9} };
int c1[4][4];

void printMatrix(int i) {
    printf("\n<< �ʱ� ��� >>\n");
    for (int x = 0; x < i; x++) {
        for (int y = 0; y < i; y++) {
            printf("%2d ", arr[x][y]);
        }
        printf("\n");
    }
    printf("\n<< ��� ��� >>\n");
    for (int x = 0; x < i; x++) {
        for (int y = 0; y < i; y++) {
            printf("%2d ", c[x][y]);
        }
        printf("\n");
    }
}

int matrixPath(int n) {

    c[0][0] = arr[0][0];

    for (int i = 1; i < n; i++)
        c[i][0] = arr[i][0] + c[i - 1][0];
    for (int j = 1; j < n; j++)
        c[0][j] = arr[0][j] + c[0][j - 1];
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++)
            c[i][j] = arr[i][j] + max(c[i - 1][j], c[i][j - 1]);
    }
    printMatrix(n);

    return c[n - 1][n - 1];
}

int cnt = 0;
int matrixPath1(int i, int j) {
    cnt++;
    if (i == 0 || j == 0) return 0;
    else {
        return (arr2[i][j] + max(matrixPath1(i - 1, j), matrixPath1(i, j - 1)));
    }
}

int matrixPath2(int n) {

    c1[0][0] = arr1[0][0];

    for (int i = 1; i < n; i++)
        c1[i][0] = arr1[i][0] + c1[i - 1][0];
    for (int j = 1; j < n; j++)
        c1[0][j] = arr1[0][j] + c1[0][j - 1];
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++)
            c1[i][j] = arr1[i][j] + MAX(c1[i - 1][j], c1[i][j - 1], c1[i - 1][j - 1]);
    }
    printf("\n�ʱ� ��� >>\n");
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            printf("%2d ", arr1[x][y]);
        }
        printf("\n");
    }
    printf("\n��� ��� >>\n");
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            printf("%2d ", c1[x][y]);
        }
        printf("\n");
    }
    return c1[n - 1][n - 1];
}

int stone(int n) {
    int** peb;
    int** w;
    peb = (int**)malloc(sizeof(int*) * 4);
    w = (int**)malloc(sizeof(int*) * 3);
    for (int i = 0; i < 4; i++) {
        peb[i] = (int*)malloc(sizeof(int) * n);
    }
    for (int i = 0; i < 3; i++) {
        w[i] = (int*)malloc(sizeof(int) * n);
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n; j++) {
            w[i][j] = rand() % 30;
        }
    }

    peb[0][0] = w[0][0];
    peb[1][0] = w[1][0];
    peb[2][0] = w[2][0];
    peb[3][0] = w[0][0] + w[2][0];
    printf("\nw>>\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d", w[i][j]);
        }
        printf("\n");
    }

    for (int i = 1; i < n; i++) {
        for (int p = 0; p < 4; p++) {
            if (p == 0) {
                peb[p][i] = w[p][i] + max(peb[1][i - 1], peb[2][i - 1]);
            }
            else if (p == 1) {
                peb[p][i] = w[p][i] + MAX(peb[0][i - 1], peb[2][i - 1], peb[3][i - 1]);
            }
            else if (p == 2) {
                peb[p][i] = w[p][i] + max(peb[0][i - 1], peb[1][i - 1]);
            }
            else if (p == 3) {
                peb[p][i] = w[0][i] + w[2][i] + peb[1][i - 1];
            }
        }
    }
    printf("\npeb>>\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d", peb[i][j]);
        }
        printf("\n");
    }
    \
    int max = 0;
    for (int i = 0; i < 4; i++) {
        if (max < peb[i][n-1]) {
            max = peb[i][n-1];
        }
    }
    return max;
}

int domino(int n) {
    int* domino = (int*)malloc(sizeof(int) * n);
    domino[0] = 1, domino[1] = 1;

    for (int i = 2; i <= n; i++) {
        domino[i] = domino[i - 1] + domino[i - 2];
    }
    return domino[n];
}

int Stair(int n) {
    int* stair = (int*)malloc(sizeof(int) * n);
    stair[0] = 1, stair[1] = 1, stair[2] = 2;

    for (int i = 3; i <= n; i++) {
        stair[i] = stair[i - 1] + stair[i - 3];
    }
    return stair[n];
}

int Post(int n) {
    int d[3] = { 10, 50, 80 };
    int* dp = malloc(sizeof(int) * n + 1);
    for (int i = 1; i <= n; i++) dp[i] = INT_MAX;
    dp[0] = 0;

    for (int i = 0; i < 3; i++) {
        int coin = d[i];
        for (int j = coin; j <= n; j++) {
            dp[j] = min(dp[j], dp[j - coin] + 1);
        }
    }
    return dp[n];
}

int Post_Greedy(int n) {
    int d[3] = { 80, 50, 10 };
    int count = 0;
    int c[3] = { 0,0,0 };
    for (int i = 0; i < 3; i++) {
        while (n >= d[i]) {
            n -= d[i];
            c[i]++;
            count++;
        }
    }
    printf("80��: [%d��] | 50��: [%d��] | 10��: [%d��]\n", c[0], c[1], c[2]);
    return count;
}


int main() {
    int num;
    while (1) {
        printf("0. ���α׷� ����\n");
        printf("1. ��� ��� ����(DP)\n");
        printf("2. ��� ��� ����(���ȣ��)\n");
        printf("3. ��� ��� ����(��������)\n");
        printf("4. �� ���� ���� ���� ���α׷���\n");
        printf("5. ���̳�(��������)\n");
        printf("6. ���\n");
        printf("7. ��ǥ\n");
        printf("���α׷��� �����ϼ��� : ");
        scanf("%d", &num);

        switch (num) {
        case 0: {
            printf("���α׷��� �����մϴ�\n");
            return 0;
        }
        case 1: {
            cnt = 0;
            printf("\n=====================================\n");
            printf("\n���� ����ġ�� ū ����� ���� : %d\n", matrixPath(5));
            printf("\n=====================================\n");
            break;
        }
        case 2: {
            printf("\n=====================================\n");
            printf("\n���� ����ġ�� ū ����� ���� : %d\n", matrixPath1(5, 5));
            printf("���ȣ�� Ƚ�� : %d��\n", cnt);
            printf("\n=====================================\n");
            break;
        }
        case 3: {
            printf("\n=====================================\n");
            printf("\n���� ����ġ�� ū ����� ���� : %d\n", matrixPath2(4));
            printf("\n=====================================\n");
            break;
        }
        case 4: {
            int n;
            printf("\n=====================================\n");
            printf("���̺��� ũ�⸦ �Է��ϼ��� : ");
            scanf("%d", &n);
            printf("\n���� ����ġ�� ū ����� ���� : %d\n", stone(n));
            printf("\n=====================================\n");
            break;
        }
        case 5: {
            int n;
            printf("\n=====================================\n");
            printf("�簢���� ũ�⸦ �Է��ϼ��� : ");
            scanf("%d", &n);
            printf("���̳븦 ä�� �� �ִ� ����� ���� : %d\n", domino(n));
            printf("\n=====================================\n");
            break;
        }
        case 6: {
            int n;
            printf("\n=====================================\n");
            printf("\n����� ������ �Է��ϼ��� : ");
            scanf("%d", &n);
            printf("����� ������ ����� �� : %d\n", Stair(n));
            printf("\n=====================================\n");
            break;
        }
        case 7: {
            int n;
            printf("\n=====================================\n");
            printf("\n�ݾ��� �Է��ϼ��� : ");
            scanf("%d", &n);
            printf("\n(���� ���α׷���)\n");
            printf("�ּ� ��ǥ ����: %d��\n", Post(n));
            printf("\n(�׸���)\n");
            printf("�ּ� ��ǥ ����: %d��\n", Post_Greedy(n));
            printf("\n=====================================\n");
            break;
        }
        }
        printf("\n");
    }
}