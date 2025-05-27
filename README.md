# Cache Lab Implementation - Optimizing Matrix Transpose

## Overview

This repository contains my implementation of the Cache Lab from CMU's Computer Systems: A Programmer's Perspective (CS:APP) course. The lab focuses on understanding cache memory organization and optimizing matrix transpose operations to minimize cache misses.

## Lab Components

The implementation consists of two main parts:

1. **Cache Simulator**: A simulator that models the behavior of a cache memory hierarchy
2. **Matrix Transpose Optimizer**: An optimized matrix transpose function that minimizes cache misses

## Implementation Details

### Cache Simulator

- Models a configurable cache with parameters for size, associativity, and block size
- Implements LRU (Least Recently Used) replacement policy
- Handles both hits and misses (cold, conflict, and capacity)
- Provides detailed statistics about cache performance

### Matrix Transpose Optimizer

The matrix transpose optimization achieves perfect performance (minimum cache misses) by:

1. **Blocking**: Dividing the matrix into smaller blocks that fit in cache
2. **Loop Reordering**: Optimizing memory access patterns
3. **Diagonal Handling**: Special processing for diagonal elements

Optimizations implemented:
- Block sizes carefully chosen based on cache parameters
- Special handling for matrices that aren't perfect multiples of block size
- Minimal evictions by maximizing cache locality


## How to Use

1. Build the simulator:
   ```
   make
   ```

2. Run the cache simulator:
   ```
   ./csim-ref -s <num_sets> -E <associativity> -b <block_size> -t <trace_file>
   ```

3. Test the matrix transpose:
   ```
   ./test-trans -M <rows> -N <cols>
   ```


## References

- Bryant & O'Hallaron, *Computer Systems: A Programmer's Perspective*
- CMU CS:APP course materials
