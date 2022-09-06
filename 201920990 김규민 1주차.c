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
        arr[cnt] = a % b;         //2������ ���������� ����ؼ� 2�� ������ �������� ���ϰ� �Ųٷ� ����.
        a /= b;                   //��� ������ȯ�� ��Ģ�� ���� ������ �̷���� ä��
        cnt++;
    }
    arr[cnt] = a;
    for (; cnt >= 0; cnt--) {      //�Ųٷ� �̾ƾ� �ϱ� ������ cnt�� ū������ �������� ������.
        if (arr[cnt] < 10)
            printf("%c", arr[cnt] + 48);
        else
            printf("%c", arr[cnt] + 55);                //16���� ó��
    }
    printf("(%d)", b);
}

int get_height(TreeNode* node) {
    int height = 0;

    if (node != NULL)
        height = 1 + max(get_height(node->left), get_height(node->right));

    return height;
}

void inorder(TreeNode* t) { // ���� ��ȸ ���
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
        printf("\n0. ���α׷� ����\n");
        printf("1. �ִ� �ּ� ã��\n");
        printf("2. ���ڿ� ����\n");
        printf("3. ������ȯ\n");
        printf("4. Ʈ�����\n");
        printf("����Ͻ� ���α׷��� �����ϼ��� : ");
        scanf("%d", &N);

        switch (N)
        {
        case 0: {
            printf("���α׷��� �����մϴ�.");
            return 0;
        }
        case 1: {
            int n;
            int arr[10];
            for (int i = 0; i < 10; i++) {
                arr[i] = rand() % 10 + 1;            //���Ǹ� ���� �����ϰڽ��ϴ�.
                printf("[%d] ", arr[i]);
            }
            printf("\n���� ū �� : %d\n", find_max(arr));
            printf("���� ���� �� : %d\n", find_min(arr));
            break;
        }
        case 2: {
            while (1) {
                int n;
                printf("\n0.����\n");
                printf("1. �ݺ���\n");
                printf("2. ��ȯ�Լ�\n");
                scanf("%d", &n);
                if (n == 0) {
                    printf("���α׷��� �����մϴ�.\n");
                    break;
                }
                else if (n == 1) {
                    char str[MAX_SIZE];
                    printf("���ڿ��� �Է��ϼ��� : ");
                    scanf("%s", str);
                    printf("%d", strlen1(str));
                    break;
                }
                else if (n == 2) {
                    char str[MAX_SIZE];
                    printf("���ڿ��� �Է��ϼ��� : ");
                    scanf("%s", str);
                    printf("%d", strlen2(str));
                    break;
                }

            }
            break;

        }
        case 3: {
            int a, b;
            printf("10������ �� a�� ��ȯ�� ���� b�� �Է��ϼ���(ex 55 16) : ");
            scanf("%d %d", &a, &b);
            printf("%d�� %d������ȯ ��� : ", a, b);
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
            printf("\n���� : %d\n", x);
            inorder(r);
            remove1(r);
            break;
        }
        }
    }
}