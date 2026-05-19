# Thread Weak-Memory Test

This project is a small multithreaded experiment that explores **weak memory behavior**.

## What this program does

The program runs a classic two-thread litmus test with four global variables:

- `x` and `y`: shared variables written by different threads
- `a` and `b`: values read back by those threads

Each iteration does the following:

- Thread 1:
  1. writes `x = 1`
  2. reads `y` into `a`
- Thread 2:
  1. writes `y = 1`
  2. reads `x` into `b`

In `main`, every iteration resets `x` and `y` to `0`, starts both threads, and waits for them with `pthread_join`.

The loop continues until this condition is observed:

- `a == 0 && b == 0`

In other words, both threads read `0` in the same iteration.

## Why this is interesting

At first glance, you might expect at least one thread to observe the other thread’s write.  
However, the `a == 0 && b == 0` result can still appear in practice due to:

- hardware and compiler reordering
- store buffering and delayed visibility across cores
- missing synchronization primitives (for example, atomics or fences)

This demonstrates that without explicit synchronization, cross-thread memory visibility and ordering are not reliable.

## Memory-model context

### Sequential consistency

Under **sequential consistency**, all operations appear in one global order that preserves each thread’s program order.  
In that model, both threads reading `0` is not expected.

### Weak memory behavior

Real systems are often not sequentially consistent by default.  
CPUs and memory subsystems may expose loads/stores in different orders across threads, enabling surprising outcomes.

### Compiler effects

Compilers may also reorder or optimize memory operations unless synchronization is used.  
So this experiment can reflect both hardware-level and compiler-level effects.

### Architecture dependence

How often weak-memory outcomes appear depends on platform details, including:

- CPU architecture (for example, x86 vs ARM)
- microarchitecture
- optimizer settings
- OS scheduling behavior

## Important caveat

In standard C, this code uses plain shared variables with unsynchronized concurrent access, which is a **data race** and therefore **undefined behavior**.

So while this is useful as an educational experiment, it is not a formally correct memory-model benchmark in portable C.

## Takeaway

This test is a compact teaching example for:

- why multithreaded behavior can be surprising
- why atomics, memory ordering, and synchronization matter
- why results may differ across compilers and CPU architectures
