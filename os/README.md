### OS Interface

One OS design is to separate user program and kernel program. Kernel is a special program that provides services for users to run programs. User program invokes `system call` to run certain privilege instructions. One a system call is invoked, the hardware raises privilege level and executes predefined function.

How to separate user space and kernel space?

The kernel uses the CPU's hardware protection mechanisms to ensure that each process in user space can only access its own memory space.

// TODO
This protection mechanism uses cr3 register in x86.

### What is a process?

By definition, a process is a running program. Here's a process struct if we want to implement process in an OS. Whenever the kernel switches an available CPU to a waiting process, the current running process' context is saved, and the waiting process' context is restored to run.

```c
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
### How to create a child process?

First, fork() system call creates an identical child process. Child process returns 0 after a fork() call, and parent process returns its pid. Initially, child process has the same memory content as the parent process. Even though the memory content is the same initially, they are executing different memory space and different registers.

```c
int pid = fork();
if(pid > 0) { // parent
    printf("parent: child=%d\n", pid);
    pid = wait();
    printf("child %d is done\n", pid);
} else if(pid == 0) { // child
    printf("child: exiting\n");
    exit();
} else {
    printf("fork error\n");
}
```

Then, we call exec() that takes two arguments, a path to an executable and an array of string arguments. exec() replaces the calling process' memory with new memory content from the executable.

```c
// argv[0] is usually ignored because it is conventionally the name of the program
argv[1] = "hello";
argv[2] = 0;
exec("/bin/echo", argv);
printf("exec error\n"); // This line will not execute if exec succeeds.
```

This is basically how a shell is implemented.


