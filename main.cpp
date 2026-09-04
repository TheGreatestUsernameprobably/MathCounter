#include <iostream>
#include <vector>
#include <gmpxx.h>
#include "Fibonacci/fibonacci.hpp"
#include <filesystem>


int main() {
    Fibonacci fib;
    fib.CalculateNumbers(1e5);
    fib.SaveNumbers();

    std::cout << "Done!" << "\n";
    return 0;
}