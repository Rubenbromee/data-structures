#ifndef LIST_UTIL_H
#define LIST_UTIL_H

#include <cstddef>
#include <cmath>

std::size_t next_power_of_two(std::size_t n) {
    // To avoid negative numbers in bitshifting
    if (n == 0) {
        return 1;
    }

    n--; // Decrement incase n is a power of two

    // Different exponent limit depending on size of size_t (system dependent)
    int exponent_limit = sizeof(std::size_t) - 1;

    /* 
        The bits of the current value of n are right shifted 2^i times and that value is temporarily stored in (n >> 2^i).
        A bitwise OR operation is then performed between the current value of n and (n >> 2^i).
        This will continue until all bits right of the highest set bit in the initial value of n are set.
        This will increase n to the next power of two for n, minus 1.
        The function then returns n + 1, producing the next power of two for n.
    */
    /* 
        Example, let's say that, after the above decrement, n is 5:
        n = 5 = 0000 0101

        First loop iteration (2^i = 1):
        0000 0101 >> 1 = 0000 0010
        0000 0101 | 0000 0010 = 0000 0111

        Second loop iteration (2^i = 2):
        0000 0111 >> 2 = 0000 0001
        0000 0111 | 0000 0001 = 0000 0111

        Third loop iteration (2^i = 4):
        0000 0111 >> 4 = 0000 0000
        0000 0111 | 0000 0000 = 0000 0111

        All loop iterations above 4 will have the same result,
        since the bits will be shifted right more and more times
        always creating 0000 0000 after the bitshift

        This will produce 0000 0111 = 7
        
        The function then returns n + 1 so in the case of n being 5 after the decrement, i.e. n = 6 initially,
        the next power of two will be 8.
    */
    int power_of_two = 1;
    for (int i = 0; i < exponent_limit; i++) {
        std::size_t prev_n = n; // Set previous n to be able to do early return
        n = n | (n >> power_of_two); // Perform combined right bit shift and bitwise OR

        // Check if current value is same as previous value, i.e. all bits right of the highest set bit has been set
        // In that case, return early
        if (prev_n == n) {
            return n + 1;
        }

        power_of_two *= 2; // Set next power of two
    }

    return n + 1;
}

#endif