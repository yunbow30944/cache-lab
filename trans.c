/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N]) {
    int i, j, k,tmp0, tmp1, tmp2, tmp3, tmp4, tmp5,tmp6,tmp7;
    if(M==32&&N==32){
        for(int i=0;i<32;i+=8){
            for(int j=0;j<32;j+=8){
                for(int k=i;k<i+8;k++){
                    int temp;//对角线值
                    for(int l=j;l<j+8;l++){
                        if(k==l){
                            temp = A[k][l];
                        }
                        else{
                            B[l][k]=A[k][l];
                        }
                    }
                    if(i==j){
                        B[k][k] = temp;
                    }
                }
            }
        }
    }
    else if(M==64&&N==64)
    {
        for(i = 0; i < M/8; i++)
        {
            for(j = 0; j < N/8; j++)
            {
                for(k = 0; k < 4; k++)
                {//A11->B11
                    tmp0 = A[j*8+k][i*8+0];
                    tmp1 = A[j*8+k][i*8+1];
                    tmp2 = A[j*8+k][i*8+2];
                    tmp3 = A[j*8+k][i*8+3];
                    B[i*8+0][j*8+k] = tmp0;
                    B[i*8+1][j*8+k] = tmp1;
                    B[i*8+2][j*8+k] = tmp2;
                    B[i*8+3][j*8+k] = tmp3;
                }
                for(k = 0; k < 4; k++)
                {//A12->B12
                    tmp0 = A[j*8+k][i*8+4+0];
                    tmp1 = A[j*8+k][i*8+4+1];
                    tmp2 = A[j*8+k][i*8+4+2];
                    tmp3 = A[j*8+k][i*8+4+3];
                    B[i*8+0][j*8+4+k] = tmp0;
                    B[i*8+1][j*8+4+k] = tmp1;
                    B[i*8+2][j*8+4+k] = tmp2;
                    B[i*8+3][j*8+4+k] = tmp3;
                }
                for(k = 0; k < 4; k++)
                {//A21&B12->B21
                    tmp0 = B[i*8+k][j*8+4+0];
                    tmp1 = B[i*8+k][j*8+4+1];
                    tmp2 = B[i*8+k][j*8+4+2];
                    tmp3 = B[i*8+k][j*8+4+3];
                    tmp4 = A[j*8+4+0][i*8+k];
                    tmp5 = A[j*8+4+1][i*8+k];
                    tmp6 = A[j*8+4+2][i*8+k];
                    tmp7 = A[j*8+4+3][i*8+k];
                    B[i*8+k][j*8+4+0] = tmp4;
                    B[i*8+k][j*8+4+1] = tmp5;
                    B[i*8+k][j*8+4+2] = tmp6;
                    B[i*8+k][j*8+4+3] = tmp7;
                    B[i*8+4+k][j*8+0] = tmp0;
                    B[i*8+4+k][j*8+1] = tmp1;
                    B[i*8+4+k][j*8+2] = tmp2;
                    B[i*8+4+k][j*8+3] = tmp3;
                }
                for(k = 0; k < 4; k++)
                {//A22->B22
                    tmp0 = A[j*8+4+k][i*8+4+0];
                    tmp1 = A[j*8+4+k][i*8+4+1];
                    tmp2 = A[j*8+4+k][i*8+4+2];
                    tmp3 = A[j*8+4+k][i*8+4+3];
                    B[i*8+4+0][j*8+4+k] = tmp0;
                    B[i*8+4+1][j*8+4+k] = tmp1;
                    B[i*8+4+2][j*8+4+k] = tmp2;
                    B[i*8+4+3][j*8+4+k] = tmp3;
                }
            }
        }
    }
    else if(M==61&&N==67)
    {
       for(i = 0; i < M/8; i++)
        {
            for(j = 0; j < N/8; j++)
            {
                for(k = 0; k < 8; k++)
                {
                    tmp0 = A[j*8+k][i*8+0];
                    tmp1 = A[j*8+k][i*8+1];
                    tmp2 = A[j*8+k][i*8+2];
                    tmp3 = A[j*8+k][i*8+3];
                    tmp4 = A[j*8+k][i*8+4];
                    tmp5 = A[j*8+k][i*8+5];
                    tmp6 = A[j*8+k][i*8+6];
                    tmp7 = A[j*8+k][i*8+7];
                    B[i*8+0][j*8+k] = tmp0;
                    B[i*8+1][j*8+k] = tmp1;
                    B[i*8+2][j*8+k] = tmp2;
                    B[i*8+3][j*8+k] = tmp3;
                    B[i*8+4][j*8+k] = tmp4;
                    B[i*8+5][j*8+k] = tmp5;
                    B[i*8+6][j*8+k] = tmp6;
                    B[i*8+7][j*8+k] = tmp7;
                }
            }
        }
        for(i = 0; i < N ; i++)
        {
            for(j = 8*(M/8); j < M; j++)
            {
                tmp0 = A[i][j];
                B[j][i]=tmp0;
            }
        }
        for(i = 8*(N/8); i < N; i++)
        {
            for(j = 0; j < 8*(M/8); j++)
            {
                tmp0 = A[i][j];
                B[j][i]=tmp0;
            }
        }
    }
}



/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

