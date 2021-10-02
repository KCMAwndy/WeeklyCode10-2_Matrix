#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define N 3

void findCofactor(double mat[N][N], double temp[N][N], int p, int q, int n) {
    int i = 0, j = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (row != p && col != q) {
                temp[i][j++] = mat[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

double findDet(double mat[N][N], int n) {
    int det = 0;
    if (n == 1) {
        return mat[0][0];
    }
    double temp[N][N]; 
    int sign = 1;  
    for (int f = 0; f < n; f++) {
        findCofactor(mat, temp, 0, f, n);
        det += sign * mat[0][f] * findDet(temp, n - 1);
        sign = -sign;
    }
    return det;
}

void findAdj(double mat[N][N], double adj[N][N]) {
    if (N == 1) {
        adj[0][0] = 1;
        return;
    }
    int sign = 1;
    double temp[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            findCofactor(mat, temp, i, j, N);
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            if (findDet(temp, N - 1) != (double)0) {
                adj[j][i] = (sign) * (findDet(temp, N - 1));
            }
            else {
                adj[j][i] = 0 * (findDet(temp, N - 1));
            }
        }
    }
}


bool findInverse(double mat[N][N], double inverse[N][N]) {
    int det = findDet(mat, N);
    if (det == 0) {
        printf("It's singular matrix.\n\n");
        return false;
    }
    double adj[N][N];
    findAdj(mat, adj);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            inverse[i][j] = adj[i][j] / double(det);
        }
    }
    return true;
}

void findAplusB(double matA[N][N], double matB[N][N], double rslt[N][N]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            rslt[i][j] = matA[i][j] + matB[i][j];
        }
    }
}

void findAminusB(double matA[N][N], double matB[N][N], double rslt[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            rslt[i][j] = matA[i][j] - matB[i][j];
        }
    }
}

void findAmultiplyB(double matA[N][N], double matB[N][N], double rslt[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            rslt[i][j] = 0;
            for (int k = 0; k < N; k++) {
                rslt[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }
}

void printMat(double mat[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%.3lf\t", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    double adj[N][N],inv[N][N],AplusB[N][N],AminusB[N][N],AmulB[N][N];
    int i = 0, j = 0, k = 0, l = 0;
    int m = 0, n = 0, detA = 0, detB = 0;
    double matA[N][N], matB[N][N];
    for (i = 0; i < 2; i++) {
        if (i == 0) printf("Matrix A :\n");
        else if (i == 1) printf("Matrix B :\n");
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                if (i == 0) scanf("%lf", &matA[j][k]);
                else if (i == 1) scanf("%lf", &matB[j][k]);
            }
        }
    }
    printf("\nDet A : %.3lf", findDet(matA, N));
    printf("\nDet B : %.3lf\n", findDet(matB, N));
    printf("\nAdjoint A : \n");
    findAdj(matA, adj);
    printMat(adj);
    printf("Adjoint B : \n");
    findAdj(matB, adj);
    printMat(adj);
    printf("Inverse A : \n");
    if (findInverse(matA, inv))	printMat(inv);
    printf("Inverse B : \n");
    if (findInverse(matB, inv))	printMat(inv);
    printf("\nA + B : \n");
    findAplusB(matA, matB, AplusB);
    printMat(AplusB);
    printf("A - B : \n");
    findAminusB(matA, matB, AminusB);
    printMat(AminusB);
    printf("A * B : \n");
    findAmultiplyB(matA, matB, AmulB);
    printMat(AmulB);
    return 0;
}