//
//  MatrixMultiplication.cpp
//  P7
//
//  Name: Mualla Argin
//  UIN: 728003004

#include "MatrixMultiplication.h"
#define MIN(a, b) ((a) < (b) ? (a) : (b))

void matrixMult1(const std::vector<std::vector<int>> &a, const std::vector<std::vector<int>> &b, std::vector<std::vector<int>> &result, const int n)
{
    // row vs col
    int i, j, k;
    for (i = 0; i < n; i++)
    {

        for (j = 0; j < n; j++)
        {

            result[i][j] = 0;

            for (k = 0; k < n; k++)

                result[i][j] += a[i][k] * b[k][j];
        }
    }
}

void matrixMult2(const std::vector<std::vector<int>> &a, const std::vector<std::vector<int>> &b, std::vector<std::vector<int>> &result, const int n)
{
    // ikj
    int i, j, k;
    for (i = 0; i < n; i++)
    {
        for (k = 0; k < n; k++)
        {
            for (j = 0; j < n; j++)
                result[i][j] += a[i][k] * b[k][j];
        }
    }
}

void matrixMult3(const std::vector<std::vector<int>> &a, const std::vector<std::vector<int>> &b, std::vector<std::vector<int>> &result, const int n)
{
    // jik
    int i, j, k;
    for (j = 0; j < n; j++)
    {
        for (i = 0; i < n; i++)
        {

            result[i][j] = 0;

            for (k = 0; k < n; k++)

                result[i][j] += a[i][k] * b[k][j];
        }
    }
}

void blockingMatrixMult(const std::vector<std::vector<int>> &a, const std::vector<std::vector<int>> &b, std::vector<std::vector<int>> &result, const int n, const int block_size)
{
    // 500
    int i, j, k, kk, jj, sum;
    for (kk = 0; kk < n; kk += block_size)
    {
        for (jj = 0; jj < n; jj += block_size)
        {
            for (i = 0; i < n; i++)
            {
                for (j = jj; j < MIN(jj + block_size, n); j++)
                {
                    sum = 0;
                    for (k = kk; k < MIN(kk + block_size, n); k++)
                    {
                        sum += a[i][k] * b[k][j];
                    }
                    result[i][j] += sum;
                }
            }
        }
    }
}
