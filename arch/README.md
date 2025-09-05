### Memory Ordering

**Memory ordering** refers to the rules when a processor's reads and writes to memory become visible to other processors.

- **Sequential Consistency** guarantees the result of every memory operations from all threads are in a single, global, sequential order. It's easier for the programmer to program but it's hard for hardware and compilers to performa optimizations by reordering memory operations.
- **Total Store Ordering** is a weaker memory model. It allows processors to have write buffers. Whenever there's a memory write, this operation goes to the write buffer. Other processors will only see this operation when it is flushed from the buffer to the shared cache. This model requires programmer to use explicit synchronization operations (mutex, atomic).

### SIMD

**Single Instruction, Multiple Data** is a hardware-level parallelism model where a single instruction operates on multiple data elements.

- Vertical operations apply the same instructions to a vector of data. `[A, B, C, D] * 2 -> [A*2, B*2, C*2, D*2]`
- Horizontal operations combine elements within a single vector. `[A, B, C, D] -> A + B + C + D`

### SIMT

**Single Instruction, Multiple Threads** is a software-level abstraction of SIMD, most famously used by NVIDIA GPUs. It presents a programming model where multiple independent threads execute the same program concurrently. The GPU hardware then groups these threads into "warps" and schedules them for execution on SIMD units.