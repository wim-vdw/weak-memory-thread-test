# Thread Weak-Memory Test

This project contains a very small multithreaded test case that explores **weak memory behavior**.

## Idea

Two threads run in parallel:

- Thread 1 writes `x = 1`, then reads `y`
- Thread 2 writes `y = 1`, then reads `x`

The interesting result is when both threads read `0`.

## Concepts

### Sequential consistency
Under **sequential consistency**, all operations appear to happen in one global order that is consistent with the program order of each thread. In that model, the result where both threads read `0` is not expected.

### Weak memory
Real systems are often **not sequentially consistent** by default. CPUs and memory subsystems may allow loads and stores to become visible in different orders, which can make surprising results possible.

### Compiler effects
Compilers may also reorder or optimize memory operations unless synchronization primitives or atomics are used. This means a test like this can be affected by both **hardware memory behavior** and **compiler optimization**.

### CPU architecture
The probability of observing weak-memory effects depends on the CPU architecture:

- **x86** is relatively strong
- **ARM** is generally weaker
- behavior can also vary by microarchitecture, OS scheduler, and optimization level

## This program as a test case

`main.c` implements a classic two-thread litmus test. It is useful as a simple experiment, but without atomic operations it is not a fully reliable memory-model test in standard C, because unsynchronized concurrent accesses can cause undefined behavior.

## Takeaway

This program is a small educational example that helps illustrate:

- why multithreaded code can behave unexpectedly
- why **atomics**, **memory ordering**, and **synchronization** matter
- why results may differ across compilers and CPU architectures
