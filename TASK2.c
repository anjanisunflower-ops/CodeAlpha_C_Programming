// Medium – Matrix Operations//
#include <stdio.h>

#define MAX 10

void readMatrix(int m[MAX][MAX], int r, int c, char name) {
    int i, j;
    printf("Enter elements of matrix %c (%dx%d):\n", name, r, c);
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            scanf("%d", &m[i][j]);
}

void printMatrix(int m[MAX][MAX], int r, int c) {
    int i, j;
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++)
            printf("%6d", m[i][j]);
        printf("\n");
    }
}

int getSize(int *r, int *c) {
    printf("Enter rows and columns (max %d): ", MAX);
    if (scanf("%d %d", r, c) != 2 || *r < 1 || *c < 1 || *r > MAX || *c > MAX) {
        printf("Invalid size.\n");
        return 0;
    }
    return 1;
}

void addSub(int sign) {
    int a[MAX][MAX], b[MAX][MAX], res[MAX][MAX], r, c, i, j;
    if (!getSize(&r, &c)) return;
    readMatrix(a, r, c, 'A');
    readMatrix(b, r, c, 'B');
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            res[i][j] = a[i][j] + sign * b[i][j];
    printf("Result:\n");
    printMatrix(res, r, c);
}

void multiply(void) {
    int a[MAX][MAX], b[MAX][MAX], res[MAX][MAX] = {{0}};
    int r1, c1, r2, c2, i, j, k;
    printf("Matrix A - ");
    if (!getSize(&r1, &c1)) return;
    printf("Matrix B - ");
    if (!getSize(&r2, &c2)) return;
    if (c1 != r2) {
        printf("Multiplication not possible: columns of A must equal rows of B.\n");
        return;
    }
    readMatrix(a, r1, c1, 'A');
    readMatrix(b, r2, c2, 'B');
    for (i = 0; i < r1; i++)
        for (j = 0; j < c2; j++)
            for (k = 0; k < c1; k++)
                res[i][j] += a[i][k] * b[k][j];
    printf("Result (A x B):\n");
    printMatrix(res, r1, c2);
}

void transpose(void) {
    int a[MAX][MAX], t[MAX][MAX], r, c, i, j;
    if (!getSize(&r, &c)) return;
    readMatrix(a, r, c, 'A');
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            t[j][i] = a[i][j];
    printf("Transpose:\n");
    printMatrix(t, c, r);
}

int main(void) {
    int ch;
    do {
        printf("\n===== MATRIX OPERATIONS =====\n");
        printf("1. Addition\n2. Subtraction\n3. Multiplication\n4. Transpose\n5. Exit\nEnter choice: ");
        if (scanf("%d", &ch) != 1) { printf("Invalid input.\n"); return 1; }
        switch (ch) {
            case 1: addSub(1); break;
            case 2: addSub(-1); break;
            case 3: multiply(); break;
            case 4: transpose(); break;
            case 5: printf("Goodbye!\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (ch != 5);
    return 0;
}
