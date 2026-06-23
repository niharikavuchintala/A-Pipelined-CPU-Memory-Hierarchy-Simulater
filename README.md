# A-Pipelined-CPU-Memory-Hierarchy-Simulater
# CPU & Memory Simulator

This repository contains a C++ simulator that models CPU task scheduling and cache memory management. It simulates how programs fight for CPU time and how memory moves through different cache levels. 

## What it does
* **Scheduler:** I used a Round Robin algorithm with a time quantum of 3 to give tasks their turns on the CPU.
* **Cache System:** It simulates L1 (32 slots), L2 (128 slots), L3 (512 slots), and RAM.
* **Eviction (FIFO):** When a cache level gets full, it simply kicks out the oldest memory block (FIFO) to make room for the new one.
* **Tracking:** It prints out exactly what is happening at every cycle so you can watch the cache hits and misses happen in real-time.

## How to run it
You just need standard C++ to run this. No extra libraries are required. 

1. Make sure `code.cpp` and `input.txt` are saved in the exact same folder.
2. Open your terminal in that folder and compile the code:
   g++ code.cpp -o code.exe
3. Run the program:
   .\code.exe
