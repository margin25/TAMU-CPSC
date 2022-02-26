//
//  main.cpp
//  P7
//
//  Name: Mualla Argin
//  UIN: 728003004

#include "MatrixMultiplication.h"
#include <chrono>
#include <ctime>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, const char *argv[])
{

    // File Read Operation
    ifstream ifs(string(argv[1]), std::ifstream::in);
    int size;
    ifs >> size;
    cout << size << endl;
    vector<vector<int>> a(size, vector<int>(size, 0));
    vector<vector<int>> b(size, vector<int>(size, 0));
    vector<vector<int>> mult(size, vector<int>(size, 0));
    int i, j, k;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            ifs >> a[i][j];
        }
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            ifs >> b[i][j];
        }
    }

    // read test case (using ifstream) into a vector

    // Matrix Mult 1
    long double duration;
    clock_t start = std::clock();
    matrixMult1(a, b, mult, size);
    clock_t end = std::clock();
    duration = (end - start) / (long double)CLOCKS_PER_SEC;
    std::cout << "Matrix Mult 1: " << duration << " seconds.\n";

    // Matrix Mult 2
    start = std::clock();
    matrixMult2(a, b, mult, size);
    end = std::clock();
    duration = (end - start) / (long double)CLOCKS_PER_SEC;
    std::cout << "<Matrix Mult 2: " << duration << " seconds.\n";

    // Matrix Mult 3
    start = std::clock();
    matrixMult3(a, b, mult, size);
    end = std::clock();
    duration = (end - start) / (long double)CLOCKS_PER_SEC;
    std::cout << "Matrix Mult 3: " << duration << " seconds.\n";

    // Matrix Mult Blocking
    start = std::clock();
    blockingMatrixMult(a, b, mult, size, 500);
    end = std::clock();
    long double duration = (end - start) / (long double)CLOCKS_PER_SEC;
    std::cout << "Matrix Multiplication Blocking: " << duration << " seconds.\n";

    return 0;
}
