# Heap priority queue
Implementation of priority queue using binary heap data structure.

This code was compiled on Windows 10 using Visual Studio 2022.
In order to test the basic capabilites of the implementation, main.cpp was provided which tests the basic functionality.

# Available features
Available actions for the heap are:
1) New heap of order m
2) Add new element
3) Get min element
4) Delete min element
5) Change heap order
6) Add one heap to another heap
7) Print heap
8) Delete heap
9) Delete arbitrary key

Available actions for the priority queue are:
1) New empty queue
2) Test if queue is empty
3) Get first element
4) Delete first element
5) Add new element
6) Load from file
7) Load using random numbers
8) Benchmark

# Performance
The following is a performance benchmark of the given implementation. It was tested using the Benchmark.cpp class.
Time is represented in miliseconds.

```
Item count  M  Ins. time   Ins. steps   Del. time   Del. steps
---------    -  ---------   ----------   ---------   ----------
100          2  6.45        272          0.02        945
100          4  0.02        238          0.02        1068
100          8  0.02        176          0.02        1434
1000         2  0.16        3528         0.34        15809
1000         4  0.13        2008         0.24        17277
1000         8  0.12        1596         0.22        23828
10000        2  1.57        35574        4.79        225179
10000        4  1.35        20988        3.17        238602
10000        8  1.10        16048        2.43        328321
100000       2  12.94       355696       51.83       2916799
100000       4  11.13       209920       37.09       3036420
100000       8  10.26       159894       30.79       4179673
```

