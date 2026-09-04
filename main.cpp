#include <iostream>
#include <vector>
#include <gmpxx.h>
#include "fibonacci.hpp"


int main() {
    Fibonacci fib;
    fib.CalculateNumbers(100);
    fib.PrintNumbers();

    return 0;
}