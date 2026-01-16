#include <stdio.h>

#define N 3 // 矩阵维度

// 声明使用元素指针（指向单个元素的指针）实现转置
void transMatrix(int *matrix);
int main()
{
    int A[N][N];

    // 输入矩阵
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            scanf("%d", &A[i][j]);
        }
    }

    // 使用元素指针转置
    transMatrix(&A[0][0]);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if(j != 0)
            {
                printf(" ");
            }
            printf("%d", A[i][j]);
        }
        printf("\n");
    }

    return 0;
}

void transMatrix(int *matrix)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            int temp = *(matrix + i * N + j);
            *(matrix + i * N + j) = *(matrix + i + j * N);
            *(matrix + i + j * N) = temp;
        }
    }
}
