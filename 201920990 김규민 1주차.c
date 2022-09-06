#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100

typedef struct TreeNode {
    int num;
    struct TreeNode* left, * right;
}TreeNode;

void remove1(TreeNode* r) {
    if (r != NULL) {
        remove1(r->left);
        remove1(r->right);
        free(r);
    }
}

int find_max(int* arr) {
    int max = 0;
    for (int i = 0; i < 10; i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

int find_min(int* arr) {
    int min = 100;
    for (int i = 0; i < 10; i++) {
        if (arr[i] < min)
            min = arr[i];
    }
    return min;
}

int strlen1(char* str) {
    int cnt = 0;
    while (*str != '\0') {
        str++;
        cnt++;
    }
    return cnt;
}

int strlen2(char* str) {
    if (*str == '\0') return 0;
    else return 1 + strlen2(str + 1);
}

int binary(int a, int b) {
    int arr[MAX_SIZE];
    int cnt = 0;
    while (b <= a) {
        arr[cnt] = a % b;         //2진수로 생각했을때 계속해서 2로 나누어 나머지를 구하고 거꾸로 뽑음.
        a /= b;                   //모든 진법변환의 규칙은 같기 때문에 이런방법 채택
        cnt++;
    }
    arr[cnt] = a;
    for (; cnt >= 0; cnt--) {      //거꾸로 뽑아야 하기 때문에 cnt를 큰수부터 작으수로 내려감.
        if (arr[cnt] < 10)
            printf("%c", arr[cnt] + 48);
        else
            printf("%c", arr[cnt] + 55);                //16진수 처리
    }
    printf("(%d)", b);
}

int get_height(TreeNode* node) {
    int height = 0;

    if (node != NULL)
        height = 1 + max(get_height(node->left), get_height(node->right));

    return height;
}

void inorder(TreeNode* t) { // 중위 순회 출력
    if (t != NULL) {
        inorder(t->left);
        printf("[%d]\n", t->num);
        inorder(t->right);
    }
}

TreeNode* new_node(int item) {
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
    temp->num = item;
    temp->left = temp->right = NULL;
    return temp;
}

TreeNode* insert_node(TreeNode* node, int key) {
    if (node == NULL) return new_node(key);
    if (key < node->num)
        node->left = insert_node(node->left, key);
    else if (key > node->num)
        node->right = insert_node(node->right, key);

    return node;
}



int main(void) {
    int N;
    while (1) {
        printf("\n0. 프로그램 종료\n");
        printf("1. 최대 최소 찾기\n");
        printf("2. 문자열 길이\n");
        printf("3. 진법변환\n");
        printf("4. 트리계산\n");
        printf("사용하실 프로그램을 선택하세요 : ");
        scanf("%d", &N);

        switch (N)
        {
        case 0: {
            printf("프로그램을 종료합니다.");
            return 0;
        }
        case 1: {
            int n;
            int arr[10];
            for (int i = 0; i < 10; i++) {
                arr[i] = rand() % 10 + 1;            //편의를 위해 설정하겠습니다.
                printf("[%d] ", arr[i]);
            }
            printf("\n제일 큰 수 : %d\n", find_max(arr));
            printf("제일 작은 수 : %d\n", find_min(arr));
            break;
        }
        case 2: {
            while (1) {
                int n;
                printf("\n0.종료\n");
                printf("1. 반복문\n");
                printf("2. 순환함수\n");
                scanf("%d", &n);
                if (n == 0) {
                    printf("프로그램을 종료합니다.\n");
                    break;
                }
                else if (n == 1) {
                    char str[MAX_SIZE];
                    printf("문자열을 입력하세요 : ");
                    scanf("%s", str);
                    printf("%d", strlen1(str));
                    break;
                }
                else if (n == 2) {
                    char str[MAX_SIZE];
                    printf("문자열을 입력하세요 : ");
                    scanf("%s", str);
                    printf("%d", strlen2(str));
                    break;
                }

            }
            break;

        }
        case 3: {
            int a, b;
            printf("10진수의 수 a와 변환할 진수 b를 입력하세요(ex 55 16) : ");
            scanf("%d %d", &a, &b);
            printf("%d수 %d진법변환 결과 : ", a, b);
            binary(a, b);
            break;
        }
        case 4: {
            TreeNode* r = NULL;
            int num1;
            for (int i = 0; i < 10; i++) {
                num1 = rand() % 100 + 1;
                printf("[%d] ", num1);
                r = insert_node(r, num1);
            }
            int x = get_height(r);
            printf("\n높이 : %d\n", x);
            inorder(r);
            remove1(r);
            break;
        }
        }
    }
}