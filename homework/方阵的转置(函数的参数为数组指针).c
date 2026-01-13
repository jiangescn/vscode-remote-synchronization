#include <stdio.h>

#define N 3 // 矩阵维度

// 声明使用数组指针（指向一维数组的指针）实现转置
void transMatrix(int (*matrix)[N]);
int main()
{
    int A[N][N];
    int i, j;

    // 输入矩阵

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            scanf("%d", &A[i][j]);
        }
    }
    
    transMatrix(A);

    // 使用元素指针转置
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
    

    return 0;
}

void transMatrix(int (*matrix)[N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }
}
