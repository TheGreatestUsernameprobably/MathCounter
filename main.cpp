#include <iostream>
#include <vector>
#include <gmpxx.h>
#include "Fibonacci/fibonacci.hpp"
#include <filesystem>


int main() {
    Fibonacci fib;
    fib.CalculateNumbers(1e3);
    std::cout << "Done!" << "\n";
    return 0;
}