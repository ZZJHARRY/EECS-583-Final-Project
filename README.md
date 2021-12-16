# EECS-583-Final-Project

EECS 583 Final Project (Group 20) - Zijian Zhang, Huiruo Zou, Yunhao Wang, Zhaoyuan Zhang

We are implementing the paper [Improved Basic Block Reordering](https://ieeexplore.ieee.org/abstract/document/9050435?casa_token=1hzPWQlIa8sAAAAA:QzBxIIrX6pAR08cerlU4UsZ45zB-0FfXFRp3nSALw76phNCss6gfAVJCR9dngw_-c9qalDU9lS0) as our final project.

Reordering_Algorithm.ipynb - Implementation of the core reordering algorithms

dfs.py - python-implemented script for traversing profiling data output

test.cpp - LLVM IR pass for reordering

Profiling:

Machine Level Script:
1. gcc -g src/toy.c -o toy_exe
2. python objdump_to_cfg.py --func main toy_exe -o toy_profiling.txt

Example toy_profiling.txt:
basic block and instructions

  bb8 [label="1152: cmpl   $0x5f5e0fe,-0x10(%rbp)\l1159: jle    11d1 <main+0xa8>\l"];

basic block orders

  bb0 -> bb36;
  bb36 -> bb8;
  bb36 -> bb38;
  bb8 -> bb33;
  
  
IR Level steps:
 1. make build dir in IR Profiling
 2. run cmake.. and make -j2 in build dir
 3. cd .. and cd Profiling
 4. ./run.sh toy
