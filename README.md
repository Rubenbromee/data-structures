# Data structures from scratch

## Introduction

Why reinvent the wheel? To find out how a wheel is made i suppose.

In this repository I try rewriting data structures from scratch to learn how they are structured and used.

The data structures I implement in this repository are:
* List, a dynamic array like Vector in C++ or List in python
* Queue, single ended
* Doubly linked list
* Hash map with linear probing and FNV1-1a hashing function
* Directed graph data structure

## How to run

To build and run the project with CMake, run the following commands from the root of the project:
```
cd build/
cmake ..
make run
```
To clean up the build folder, from the project root, run this command in a unix terminal: 
```
./clean.sh
```

## Discussion

From scratch is a nuanced term, I'm not writing assembly here, although that would be interesting to do as well. The implementations are, as far as I can tell, similar to how they are implemented in the C++ standard library. I haven't implemented all possible functionality for each data structure and there is more to explore but just through implementing these data structures I have learned a lot about their inner workings.

During this project I used templates for most of the data structures to allow them to store a generic type. Using templates in a nice way proved to be difficult. I am not that experienced with all the features of C++ so my solution for the template implementations was to implement all template functions in a header file. From what I understand template functions need to have their implementations present when they are used and therefore I decided that keeping everything in the header files was the best solution.

One interesting bug I came across during development was a recursion bug related to operator overloading. When overloading the copy-assignment constructor for my data structures I thought it would be a good idea to utilize the copy-constructor and do an implementation like this:
```C++
// Copy-assignment operator
graph& operator=(const graph& rhs) {
    // If this and rhs are not the same variable
    if (this != &rhs) {
        this->~graph(); // Clear out the current graph
        *this = graph(rhs); // Copy values from rhs
    }
    return *this;
}
```
The problem with this implementation is the line:
```C++
*this = graph(rhs); // Copy values from rhs
```
This line uses the copy constructor to create a graph and assigns it to a left hand side variable. To an amateur C++ developer such as myself this didn't seem like much of a problem at first glance. But since the equal sign (=) is redefined, this makes the copy-assignment operator call itself, causing infinite recursion which crashed the program.

I also wrote some basic exceptions in C++ in this program, which was useful, since I had not handled it that much previously. Error handling in general is not the easiest to approach and different languages approach it differently, exceptions, try-catch, error objects, pattern matching, are all different approaches to the same problem. One that isn't easy to solve.