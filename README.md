# CPE2600 Vector Calculator
## Description
Works as a simple version of matlab, allowing users to store vectors and perform operations on them.
## Build Instructions
Using a command line, cd into CPE2600_Vector_Lab and run "make"
## Run Instructions
- Run the command _./vectorCalc_
- To run using valgrind, use _valgrind ./vectorCalc_
## Available Commands
### Base Commands
- help -> Display this guide
- quit/exit -> Close the program
- list -> List all stored vectors (up to 10)
- clear -> Clear all stored vectors
- fill num -> Creates \"num\" new random vectors
- load filename -> loads from a csv file
### Vectors
- entering a vector name alone will print that vector
- perform operations using +, -, *, ., and x. Examples: a . b and c * 3
- assign a vector with "=". Examples: a = 1, 1, 1 and a = b + c
## Dynamic Memory
Whenever a vector is added to the linked list present in vectorData.c, memory is allocated for the new vector. When the user clears or the program ends, the clear function iterates through the linked list clearing each address along the way.