
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h> //printf() comes from here
#include <iostream>
using namespace std;


#define N 100
#define THREADS_PER_BLOCK 10;

__global__ void cuda_hello() { //__global__ declares the function to run on GPU
    printf("Hello, I'm on the gpu");
}

__global__ void vectoradd(float *out, float *a, float *b, int n) {
    for (int i = 0; i < n;i++)
        out[i] = a[i] + b[i];
}

__global__ void parallel_addB(float* out, float* a, float* b) {
    //block parallel function
    out[threadIdx.x] = a[blockIdx.x] + b[blockIdx.x];
}

__global__ void parallel_addT(float* out, float* a, float* b) {
    //thread parallel function
    out[threadIdx.x] = a[threadIdx.x] + b[threadIdx.x];
}

__global__ void parallel_add(float* out, float* a, float* b, int n) {
    int index = threadIdx.x + blockIdx.x * blockDim.x;
    //each block has blockDim threads. 
    //eg. if each block has 5 threads, index 13 is the 4th index of block 3
    out[index] = a[index] + b[index];

}

int main(){
    cuda_hello <<<1, 1 >>>  (); 
    //<<< M , T >>> indicates launching in parallel M blocks each with T threads


    float* a, * b, * out;

    // Allocate memory
    a = (float*)malloc(sizeof(float) * N);
    b = (float*)malloc(sizeof(float) * N);
    out = (float*)malloc(sizeof(float) * N);
    
    //initialize the array
    for (int i = 0;i < N; i++) {
        //recall that array[index]=*(array+index)
        a[i]= 1.0f;
        b[i] = 2.0f;
    }
    cout << a[3] << endl;


    //vectoradd(out, a, b, N)<<<1,1>>>; 
    //does not work; a,b,out are declared on cpu and are in RAM
    //they need to be in GPU memory

    //can use cudaMalloc/cudaFree to allocate on GPU memory
    //can use cudaMemcpy to transfer values from host to device memory
    float *d_a;
    float *d_b;
    float *d_out;

    
    cudaMalloc((void**)&d_a, sizeof(float) * N); //void** is a pointer to a pointer of unspecified type
    cudaMalloc((void**)&d_b, sizeof(float) * N); 
    cudaMalloc((void**)&d_out, sizeof(float) * N);

    cudaMemcpy(d_a, a, sizeof(float) * N, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, sizeof(float) * N, cudaMemcpyHostToDevice);


    vectoradd << <1, 1 >> > (d_out, d_a, d_b,N);
    cudaMemcpy (out, d_out, sizeof(float) * N, cudaMemcpyDeviceToHost);
   
   


    cout <<endl<<out[10]<<endl;

    parallel_addB << <N, 1 >> > (d_out, d_a, d_b);  //run on N blocks in parallel
    cudaMemcpy(out, d_out, sizeof(float) * N, cudaMemcpyDeviceToHost);
    cout << endl << out[10] << endl;


    parallel_addT << <1, N >> > (d_out, d_a, d_b);  //run on N threads in parallel
    cudaMemcpy(out, d_out, sizeof(float) * N, cudaMemcpyDeviceToHost);
    cout << endl << out[10] << endl;


    parallel_add << <10, 10>> > (d_out, d_a, d_b, N);
    cudaMemcpy(out, d_out, sizeof(float) * N, cudaMemcpyDeviceToHost);
    cout << endl << out[10] << endl;






    //remember to unallocate
    cudaFree(d_a);cudaFree(d_b);cudaFree(d_out);
    free(a);free(b);free(out);
    return 0;
    }

