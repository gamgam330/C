#include <stdio.h>
#include <stdlib.h>
#define MAX(a, b) (((a)>(b))?(a):(b))

typedef struct treeNode {
    int data;
    struct treeNode* left;
    struct treeNode* right;
} treeNode;

treeNode n8 = { 42, NULL, NULL };
treeNode n7 = { 30, NULL, NULL };
treeNode n6 = { 55, &n8, NULL };
treeNode n5 = { 15, &n7, NULL };
treeNode n4 = { 2, NULL, NULL };
treeNode n3 = { 10, NULL, &n6 };
treeNode n2 = { 16, &n4, &n5 };
treeNode n1 = { 22, &n2, &n3 };
treeNode* T2 = &n1;

int count(treeNode* node) {
    int count1 = 0;
    if (node != NULL)
        count1 = 1 + count(node->left) + count(node->right);
    return count1;
}

void preorder(treeNode* root) {
    if (root != NULL) {
        printf("[%d]", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(treeNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("[%d]", root->data);
        inorder(root->right);
    }
}

int len = 0;
treeNode* search_node(treeNode* node, int data) {
    len++;
    if (node == NULL)
        return NULL;

    if (data == node->data)
        return node;
    else if (data < node->data)
        return search_node(node->left, data);
    else
        return search_node(node->right, data);
}

treeNode* create_node(int data) {
    treeNode* node = (treeNode*)malloc(sizeof(treeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

treeNode* insert(treeNode* node, int data) {
    if (node == NULL) {
        return create_node(data);
    }
    if (data < node->data) node->left = insert(node->left, data);
    else if (data > node->data) node->right = insert(node->right, data);
    else return node;

    return node;
}

treeNode* min_value_node(treeNode* node) {
    treeNode* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

treeNode* delete_node(treeNode* root, int data) {
    if (root == NULL)return root;

    if (data < root->data)
        root->left = delete_node(root->left, data);

    else if (data > root->data)
        root->right = delete_node(root->right, data);

    else {
        if (root->left == NULL) {
            treeNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            treeNode* temp = root->left;
            free(root);
            return temp;
        }
        treeNode* temp = min_value_node(root->right);                        //������ �ϰ� ����� ��� �����Ǵ±���
        root->data = temp->data;
        root->right = delete_node(root->right, temp->data);
    }
    return root;
}

int sum = 0, count1 = 1;
int ipl(treeNode* node, int count) {
    if (node != NULL) {
        sum += count;
        printf("sum: %2d  count: %2d\n", sum, count);
        ipl(node->left, count + 1);
        ipl(node->right, count + 1);
    }
    return sum;
}

int i = 0;
int check(treeNode* node, int* temp) {
    if (node != NULL) {
        if (!check(node->left, temp))
            return 0;
        if (i == 0)
            temp[i++] = node->data;
        else if (temp[i - 1] < node->data)
            temp[i++] = node->data;
        else
            return 0;
        if (!check(node->right, temp))
            return 0;
    }
    return 1;
}

int hasPathSum(treeNode* root, int sum) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) {
        return sum - root->data == 0;
    }
    return (hasPathSum(root->left, sum - root->data)) || (hasPathSum(root->right, sum - root->data));
}
int main(void) {
    int N;
    treeNode* root = NULL, * root1;
    while (1) {
        printf("\n0. ���α׷� ����\n");
        printf("1. �˻�\n");
        printf("2. ����\n");
        printf("3. ����\n");
        printf("4. IPL(���ΰ�α���)\n");
        printf("5. ��� �˻� ����\n");
        printf("6. �����˻�Ʈ������ �Ǻ�\n");
        printf("7. haspathsum\n");
        printf("���ϴ� ���α׷��� �Է��ϼ��� :");
        scanf("%d", &N);
        switch (N) {
        case 0: {
            printf("���α׷��� �����մϴ�\n");
            return 0;
        }
        case 1: {
            int n;
            printf("\n-------------------------------------------\n");
            printf("�˻��� ���� �Է� : ");
            scanf("%d", &n);
            len = 0;
            if (search_node(root, n) != NULL)
                printf("%d�� �����մϴ�. / [%d]�� ��.\n", n, len);
            else
                printf("%d�� �����ϴ�. / [%d]�� ��\n", n, len);
            printf("-------------------------------------------\n");
            break;
        }
        case 2: {
            int n;
            printf("\n���� ���� \n");
            n = rand() % 99 + 1;
            root = insert(root, n);
            printf("-------------------------------------------\n");
            printf("���� ��ȸ ���>> \n");
            inorder(root);
            printf("\n-------------------------------------------\n");
            printf("\n");
            break;
        }
        case 3: {
            int n;
            printf("\n-------------------------------------------\n");
            printf("������ ���� �Է� : ");
            scanf("%d", &n);
            root = delete_node(root, n);
            printf("���� ��ȸ ��� \n");
            inorder(root);
            printf("\n-------------------------------------------\n");
            break;
        }
        case 4: {
            sum = 0, count1 = 1;
            printf("\n-------------------------------------------\n");
            printf("IPL : %d\n", ipl(root, count1));
            printf("-------------------------------------------\n");
            break;

        }
        case 5: {
            sum = 0, count1 = 1;
            printf("\n-------------------------------------------\n");
            printf("����Ʈ���� ��� ���� : %d\n", count(root));
            printf("��� �˻� ���� : %.2f\n", (double)ipl(root, count1) / count(root));
            printf("-------------------------------------------\n");
            break;
        }
        case 6: {
            i = 0;
            int n;
            printf("\n����� Ʈ���� �Է��ϼ���(1/2) : ");
            scanf("%d", &n);
            if (n == 1) {
                root1 = root;
            }
            else if (n == 2) {
                root1 = T2;
            }
            int* temp = malloc(sizeof(int) * count(root1));
            printf("-------------------------------------------\n");
            if (check(root1, temp) == 1) {
                printf("\n�����˻�Ʈ���Դϴ�.\n");
                printf("-------------------------------------------\n\n");
            }
            else {
                printf("\n�����˻�Ʈ���� �ƴմϴ�.\n");
                printf("-------------------------------------------\n\n");
            }
            break;
        }
        case 7: {
            int n1;
            printf("\n����� Ʈ���� �Է��ϼ���(1/2) : ");
            scanf("%d", &n1);
            if (n1 == 1) {
                root1 = root;
            }
            else if (n1 == 2) {
                root1 = T2;
            }
            int n;
            printf("-------------------------------------------\n");
            printf("ã�����ϴ� ����� ���� �Է��ϼ��� : ");
            scanf("%d", &n);
            int boolean = hasPathSum(root1, n);
            if (boolean == 1) {
                printf("[%d]�� ���� ���� ��ο� �����մϴ�.\n", n);
            }
            else {
                printf("[%d]�� ���� ���� ��ο� �������� �ʽ��ϴ�.\n", n);
            }
            printf("-------------------------------------------\n");
            break;
        }
        }
    }
}