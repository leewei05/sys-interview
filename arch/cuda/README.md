### What is CUDA?

CUDA (Compute Unified Device Architecture) is a parallel computing platform and programming model developed by NVIDIA. It allows software developers to use a CUDA-enabled graphics processing unit (GPU) for general purpose processing – an approach known as GPGPU (General-Purpose computing on Graphics Processing Units).

### Streaming Multiprocessors (SMs)

A Streaming Multiprocessor (SM) is the basic processing unit on an NVIDIA GPU. Each SM is designed to execute hundreds of threads concurrently. It contains multiple processing cores (CUDA cores), a shared memory pool, and schedulers to manage and issue instructions to the threads. This architecture allows the GPU to achieve high throughput by parallelizing the execution of a large number of threads.

### Warps

A warp is a group of 32 threads that are executed simultaneously by a Streaming Multiprocessor (SM). All threads in a warp execute the same instruction at the same time. This is the SIMT (Single Instruction, Multiple Threads) execution model. If threads in a warp diverge due to a conditional branch, the warp executes each branch path sequentially, disabling threads that are not on the taken path. This can lead to performance degradation and is known as thread divergence.

### CUDA Memory Model

CUDA provides a hierarchical memory model that allows programmers to control data locality. The different memory spaces are:

- **Registers:** Private to each thread. Fastest memory on the GPU.
- **Shared Memory:** Shared by all threads in a thread block. It is on-chip and provides high-speed access.
- **Global Memory:** The main GPU memory. It is large but has higher latency. All threads can access global memory.
- **Constant Memory:** Read-only memory for all threads. It is cached and provides high-bandwidth access when all threads in a warp access the same location.
- **Texture Memory:** Read-only memory optimized for 2D spatial access patterns.