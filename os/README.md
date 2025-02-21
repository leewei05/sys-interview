### What is a process?

By definition, a process is a running program. Here's a process struct if we want to implement process in an OS.

```
struct proc {
    int pid;                 // process id
    enum state {             // process state
        RUNNING,
        WAITING,
        ZOMBIE,
        COMPLETE,
    };
    ptd_t *pgdir;            // page table directory
    struct context *context; // process' registers' values
    struct file *ofile[...]; // open files
};
```
