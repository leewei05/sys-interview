### getelementptr

`getelementptr` returns the address of a member of an aggregated data structure, such as a struct in C.
This instruction is similar with x86's lea(load effective address) instruction.

```asm
lea eax, [ebx + ecx + 12345]
```

`eax` register has the memory address of the sum of `ebx + ecx + 12345`.

This is an [example](https://llvm.godbolt.org/z/EqWjG8bKf) from the LLVM reference.

```c
// source
struct RT {
  char a;
  int b[10][20];
  char c;
};

struct ST {
  int e;
  double d;
  struct RT f;
};

int *foo(struct ST *s) {
    return &(s[1].f.b[5][13]);
}
```

```
%struct.ST = type { i32, double, %struct.RT }
%struct.RT = type { i8, [10 x [20 x i32]], i8 }

define dso_local ptr @foo(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  store ptr %0, ptr %2, align 8
  %3 = load ptr, ptr %2, align 8
  %4 = getelementptr inbounds %struct.ST, ptr %3, i64 1
  %5 = getelementptr inbounds %struct.ST, ptr %4, i32 0, i32 2
  %6 = getelementptr inbounds %struct.RT, ptr %5, i32 0, i32 1
  %7 = getelementptr inbounds [10 x [20 x i32]], ptr %6, i64 0, i64 5
  %8 = getelementptr inbounds [20 x i32], ptr %7, i64 0, i64 13
  ret ptr %8
}
```

Above LLVM IR is also equivalent to

```
%struct.RT = type { i8, [10 x [20 x i32]], i8 }
%struct.ST = type { i32, double, %struct.RT }

define ptr @foo(ptr %s) {
entry:
  %arrayidx = getelementptr inbounds %struct.ST, ptr %s, i64 1, i32 2, i32 1, i64 5, i64 13
  ret ptr %arrayidx
}
```

`getelementptr` also has a vector version, where one or more of its argument is a vector.

### GlobalIsel

GlobalISel is a framework that translates LLVM IR to Machine IR (MIR). Global means the entire function, instead of a single basic block. ISel is a short term for instruction selection.

What does it do?
- IR Translation
- Legalization: replace unsupported instructions to supported ones.
- Register bank selector
- Instruction selection: selects targeted ISA instructions from gMIR.

### SelectionDAG
