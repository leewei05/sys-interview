#include <cuda_runtime.h>

__global__ void matrix_multiplication_kernel(const float* A, const float* B, float* C, int M, int N, int K) {
    int col = blockIdx.x * blockDim.x + threadIdx.x; // col
    int row = blockIdx.y * blockDim.y + threadIdx.y; // row

    // Boundary check because the grid was sized using ceiling division
    // A = M * N
    // B = N * K
    // Think of the final matrix M by K, which means there are M rows and K columns
    if (col < K && row < M) {
        float tmp = 0;
        // Each term in the final matrix is calculated N times
        for(int i =0; i< N; i++) {
            // A: iterate row
            // B: iterate col
            tmp += A[row * N + i] * B[i * K + col];
        }
        // C = M * K
        C[row * K + col] = tmp;
    }
}

// A, B, C are device pointers (i.e. pointers to memory on the GPU)
extern "C" void solve(const float* A, const float* B, float* C, int M, int N, int K) {
    dim3 threadsPerBlock(16, 16);
    dim3 blocksPerGrid((K + threadsPerBlock.x - 1) / threadsPerBlock.x,
                       (M + threadsPerBlock.y - 1) / threadsPerBlock.y);
    
    matrix_multiplication_kernel<<<blocksPerGrid, threadsPerBlock>>>(A, B, C, M, N, K);
    cudaDeviceSynchronize();
}
