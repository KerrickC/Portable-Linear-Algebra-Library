# Portable Linear Algebra Library

A linear algebra library that includes multiplication and tranposition functions.

## Description

This linear algebra library can be ran from the command line (see Executing Progam section below). This project also includes a testing suite build with Catch2 that includes verified solutions to matrix multiplication and transpositions. A Makefile is also included for easy compilation.

## Implementation Details

The user is inituall prompted to select an operation in CLI. Then, the user can create a matrix or matricies (depending on the operation) and the solution to the specified operation (multiplication or transposition) are then displayed to the user. This project is implementing using only STL data structures. A 2-D array is used to represent the matricies. Transposition is done by swapping indexes with another matrix with flipped dimensions O(n^2). Matrix multiplication is done by iteration and is O(n^2) on average. A transposision of one of the arrays is done preliminarily to avoid substantial cache misses, as the program can access the array elements in a linear fashion, hopefully increase cache hit rate. 

### Dependencies

- gcc compiler (runs on c++11)

### Executing program

Running this program can be done manually or with the provided Makefile in Cavanaugh-Kerrick/build. 

- Manually:
```
cd Cavanaugh-Kerrick/src
g++ Cavanaugh-Kerrick.cpp -o a.out -std=c++11
```

- Makefile (recommended)
main program:
```
cd Cavanaugh-Kerrick/build
make
```
tesing suite:
```
cd Cavanaugh-Kerrick/build
make testing
```

## Possible Areas of Improvement

If I had more time to work on the project, I would allow users to import csv files with matricies to allow to faster results. Although my solution is working, there are most likely many areas of improvemnet when it comes to speed. While I am only aware of the current implementation method of matrix multiplication, this is not to say that a much faster way exists.

# PS

I hope you enjoy my solution and I hope to hear from you soon. Thank you for your consideration! If you have any questions about me or my "linear algebra library", please do not hesitate to contact me at kerrickcavanaugh@gmail.com