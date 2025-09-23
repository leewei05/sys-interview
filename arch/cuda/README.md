### What is CUDA?

CUDA (Compute Unified Device Architecture) is a parallel computing platform and programming model developed by NVIDIA. It allows software developers to use a CUDA-enabled graphics processing unit (GPU) for general purpose processing – an approach known as GPGPU (General-Purpose computing on Graphics Processing Units).

### Streaming Multiprocessors (SMs)

A Streaming Multiprocessor (SM) is the basic processing unit on an NVIDIA GPU. Each SM is designed to execute hundreds of threads concurrently. It contains multiple processing cores (CUDA cores), a shared memory pool, and schedulers to manage and issue instructions to the threads. This architecture allows the GPU to achieve high throughput by parallelizing the execution of a large number of threads.

### Warps

A warp is a group of 32 threads that are executed simultaneously by a Streaming Multiprocessor (SM). All threads in a warp execute the same instruction at the same time. This is the SIMT (Single Instruction, Multiple Threads) execution model. If threads in a warp diverge due to a conditional branch, the warp executes each branch path sequentially, disabling threads that are not on the taken path. This can lead to performance degradation and is known as thread divergence.

### CUDA Memory Model

CUDA provides a hierarchical memory model that allows programmers to control data locality. The different memory spaces are:

- **Registers:** Private to each thread. Fastest memory on the GPU.
- **Shared Memory:** Shared by all threads in a thread block. It is on-chip and provides high-speed access. Shared memory is allocated using the `__shared__` memory space specifier. 
- **Global Memory:** The main GPU memory. It is large but has higher latency. All threads can access global memory.
- **Constant Memory:** Read-only memory for all threads. It is cached and provides high-bandwidth access when all threads in a warp access the same location.
- **Texture Memory:** Read-only memory optimized for 2D spatial access patterns.
- **Distributed Shared Memory:** Shared memory of all thread blocks in a cluster.
- **Unified Memory:** A single unified memory pool that is a single pointer value enables across host and device.

One thing to remember is that CUDA programming model assumes a system composed of a host and a device, each with their **separate memory**. Kernels operate out of device memory, so the CUDA runtime provides functions to allocate, deallocate, and transfer memory between host and device.

#### L2 Cache Management

- **Persisting**: when a kernel access a data region in the global memory repeatedly. This data region in the L2 cache will be called L2 Cache set-aside.
- **Streaming**: when a kernel access a data region once.

### Thread Hierarchy

CUDA organizes threads into a three-level hierarchy:

1.  **Threads:** The most basic unit of execution. Each thread executes an instance of the kernel function. Threads are identified by their `threadIdx`, which can be a 1D, 2D, or 3D index within a thread block.

2.  **Thread Blocks:** A group of threads that execute together on the same Streaming Multiprocessor (SM). Threads within a block can cooperate by sharing data through a high-speed shared memory and can synchronize their execution. Thread blocks are identified by their `blockIdx` within a grid.

3.  **Grid:** A collection of thread blocks that execute the same kernel. The grid is the highest level of the hierarchy. The dimensions of the grid are specified by `gridDim`.

This hierarchical organization allows for scalable parallelism. The number of threads per block and the number of blocks per grid can be adjusted to fit the specific GPU architecture and the problem being solved. All threads in a grid execute the same kernel code.

### SIMT

**Single Instruction, Multiple Threads** is a software-level abstraction of SIMD, most famously used by NVIDIA GPUs. It presents a programming model where multiple independent threads execute the same program concurrently. The GPU hardware then groups these threads into "warps" and schedules them for execution on SIMD units.

### Compilation Workflow

`nvcc` a closed-source compiler that compiles `PTX` to binary (cubin object).

- offline compilation: compiles source code into a mix of host code and device code.
- Just-in-Time compilation: device driver compiles `PTX` code at runtime to binary. It is more cache friendly, since the device driver will cache a copy. 
