### Memory Ordering

**Memory ordering** refers to the rules when a processor's reads and writes to memory become visible to other processors.

- **Sequential Consistency** guarantees the result of every memory operations from all threads are in a single, global, sequential order. It's easier for the programmer to program but it's hard for hardware and compilers to performa optimizations by reordering memory operations.
- **Total Store Ordering** is a weaker memory model. It allows processors to have write buffers. Whenever there's a memory write, this operation goes to the write buffer. Other processors will only see this operation when it is flushed from the buffer to the shared cache. This model requires programmer to use explicit synchronization operations (mutex, atomic).

### SIMD

**Single Instruction, Multiple Data** is a hardware-level parallelism model where a single instruction operates on multiple data elements.

- Vertical operations apply the same instructions to a vector of data. `[A, B, C, D] * 2 -> [A*2, B*2, C*2, D*2]`
- Horizontal operations combine elements within a single vector. `[A, B, C, D] -> A + B + C + D`

### CPU vs GPU

| Feature | CPU (Central Processing Unit) | GPU (Graphics Processing Unit) |
| :--- | :--- | :--- |
| **Core Design** | A small number of powerful, general-purpose cores designed for low-latency execution of sequential tasks. | A large number of smaller, specialized cores designed for high-throughput parallel processing. |
| **Architecture** | Optimized for **latency**. Each core can execute a different instruction on different data (MIMD - Multiple Instruction, Multiple Data). | Optimized for **throughput**. All cores in a streaming multiprocessor (SM) execute the same instruction on different data (SIMD - Single Instruction, Multiple Data). |
| **Parallelism** | Best suited for **task parallelism**, where different threads perform different tasks. | Excels at **data parallelism**, where the same task is performed on a massive amount of data. |
| **Memory Model** | Large caches to reduce latency for individual core access. | Smaller caches, but with very high-bandwidth memory to feed the large number of cores in parallel. |
| **Use Cases** | General-purpose computing, operating systems, databases, applications requiring complex logic and fast single-thread performance. | Graphics rendering, scientific computing, machine learning, cryptocurrency mining, and other massively parallel computations. |