
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <iostream>
using namespace std;

#define N 8


void cpuMatMul(float A[N][N], float B[N][N], float out[N][N]);

__global__ void gpuMatMul(float *A, float *B, float *out, int W);

int main(){


    float A[N][N];
    float B[N][N];
    float C[N][N];
    
    float* pA;
    float* pB;
    float* pC;

    pA = (float*)malloc(sizeof(float) *N* N);
    pB = (float*)malloc(sizeof(float) *N* N);
    pC = (float*)malloc(sizeof(float) *N* N);


    float *dA, *dB, *dC;


    // Allocate memory
    //a = (float*)malloc(sizeof(float) * N);
    //b = (float*)malloc(sizeof(float) * N);
    //out = (float*)malloc(sizeof(float) * N);
    
    //initialize the arrays
    for (int k = 0;k < N; k++) {
        for (int m = 0; m < N;m++) {
            A[m][k] = 2*(float)m + 3*(float)k;
            pA[m*N + k] = A[m][k];
            B[m][k] = 3*(float)m + 4*(float)k;
            pB[m*N + k] = B[m][k];
        }
    }

    cpuMatMul(A, B, C);





    cudaMalloc((void**)&dA, sizeof(float) * N * N); //void** is a pointer to a pointer of unspecified type
    cudaMalloc((void**)&dB, sizeof(float) * N * N);
    cudaMalloc((void**)&dC, sizeof(float) * N * N);


    cudaMemcpy(dA, pA, sizeof(float) * N * N, cudaMemcpyHostToDevice);
    cudaMemcpy(dB, pB, sizeof(float) * N * N, cudaMemcpyHostToDevice);


    //using 2d indexing of threads and blocks
    dim3 threads(4, 4);
    dim3 blocks(2, 2);

    //We must have threads * blocks = (N,N)
    gpuMatMul <<<blocks, threads >>>(dA, dB, dC, N);
    cudaMemcpy(pC, dC, sizeof(float) * N * N, cudaMemcpyDeviceToHost);


    cout << endl;
    for (int m = 0; m < N;m++) {
        for (int n = 0; n < N;n++) {
            cout << C[m][n] << " ";
        }
        cout << endl;
    }
    cout << endl;

    for (int m = 0; m < N;m++) {
        for (int n = 0; n < N;n++) {
            cout << pC[m*N+n] << " ";
        }
        cout << endl;
    }
    cout << endl;

    //free memory
    cudaFree(dA);cudaFree(dB);cudaFree(dC);
    free(pA);free(pB);free(pC);
    return 0;
    }

void cpuMatMul(float A[N][N], float B[N][N], float out[N][N]) {
    float sum = 0.0;
    for (int i = 0; i < N; i++) {
        for (int j = 0;j < N; j++) {
            sum = 0.0;
            for (int k = 0; k < N;k++) {
                sum = sum + A[i][k] * B[k][j];
            }
            out[i][j] = sum;
        }
    }
}

__global__ void gpuMatMul(float *A, float *B, float *out, int W) {
    //element(x, y) can be addressed as : x * width + y
    //eg for a 4x4 matrix, m(1,1) = 5 = 1*4+1

    int col = blockIdx.y * blockDim.y + threadIdx.y;
    int row = blockIdx.x * blockDim.x + threadIdx.x;
    float sum = 0.0;
    if (row < W && col < W) {
        //prevents us from going out of bound in case we launch more threads/blocks
        //than necessary
        for (int k = 0;k < W;k++) {
            //sum = sum + A[row][k] + B[k][col]
            sum += A[row * W + k] * B[k * W + col];
        }
        out[row*W+col] = sum;
    }
}