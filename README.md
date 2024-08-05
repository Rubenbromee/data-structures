# Data structures from scratch

In this repository I try rewriting data structures from scratch to learn how they are structured and used.

The data structures I implement in this repository are:
* List, a dynamic array like Vector in C++ or List in python
* Queue, single ended
* Doubly linked list
* Hash map with linear probing and FNV1-1a hashing function
* Directed graph data structure

TODO: cmake instructions

From scratch is a nuanced term, I'm not writing assembly here, although that would be an interesting project as well. The implementations are, as far as I can tell, similar to how they are implemented in the C++ standard library. I haven't implemented all possible functionality for each data structure and there is more to explore but just through implementing these data structures I have learned a lot about how their inner workings.

Discuss copy-assignment recursion bug when using:
struct_a a = struct_a(b);