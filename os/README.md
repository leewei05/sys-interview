### OS Interface

One OS design is to separate user program and kernel program. Kernel is a special program that provides services for users to run programs. User program invokes `system call` to run certain privilege instructions. One a system call is invoked, the hardware raises privilege level and executes predefined function.

How to separate user space and kernel space?

The kernel uses the CPU's hardware protection mechanisms to ensure that each process in user space can only access its own memory space.

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

### What is a file descriptor?

A file descriptor is an integer that represents an I/O object that we can read from or write to. There are 3 built-in file descriptors in Unix: stdin 0, stdout 1, stderr 2.

I/O redirection can be implemented by playing with file descriptors.

```c
char *argv[2];
argv[0] = "cat";
argv[1] = 0;

if(fork() == 0) {
    close(0);
    open("input.txt", O_RDONLY);
    exec("cat", argv);
}
```

The code above is the implementation of `cat < input.txt`. Newly created file descriptor starts from the lowest available integer in the system. If we close(0) first, then open() a file. open() will return 0 as its new file descriptor.

### What is a pipe?

A pipe is a kernel buffer that bridges two processes.

```c
int p[2];
char *argv[2];
argv[0] = "wc";
argv[1] = 0;

pipe(p);
if(fork() == 0) { // child
    close(0);
    dup(p[0]);    // child stdin reads from pipe
    close(p[0]);  // close both read, write from pipe
    close(p[1]);  // or else both ends won't receive EOF
    exec("/bin/wc", argv);
} else { // parent
    close(p[0]);  // parent closes read pipe
    write(p[1], "hello world\n", 12);
    close(p[1]);
}
```

Pipeline can be implemented without pipe. `cat input.txt | wc` is the same as `cat input.txt > /tmp/t; wc < /tmp/t`. However, having pipe can have multiple advantages.

1. Pipe cleans up themselves. With the second approach, we have to remove the temporary file ourselves.
1. Pipe can pass arbitrary data, while file direction needs enough space on disk.
1. Pipe allows parallel execution, while the second approach needs to execute in sequence.
1. Pipe's blocking read write is more efficient than non-blocking files for inter-process communication.

// TODO: pipe blocking

### How to boot an OS?

The following is specific for booting xv6 on i386.

- Power on
- Execute BIOS(ROM)
- BIOS loads the bootloader(512 bytes) at 0x7c00 to 0x7e00 and jumps to that address
- Processor starts off in real mode(16 bits)
    - disable processor interrupts
    - zero segment registers
- Switch to protected mode(32 bits)
    - setup segment descriptor table `gdt`
    - enables protected mode
- Set up stack at 0x7c00($start) as top of the stack, grows down to 0x0000
- Call into C bootmain
    - load the first 4096 bytes of the kernel at 0x10000
    - check if this is valid ELF
    - Load xv6 kernel from disk to memory, zero the remainder segment
        - kernel address is linked at 0x80100000(virtual)
        - kernel physical address starts at 0x100000
- Jump kernel entry
- Set up page directory and enable paging
- Set up stack pointer esp
- Jump to main()

### What is paging?

Paging is a technique that OS uses to enforce isolation between processes.

CR3 register in x86 is the page directory base register. The value is updated by the OS whenever a process is scheduled to run.

The paging hardware uses the upper 20 bits to locate the entry in the page table.
