#include <iostream>
#include <vector>
#include <gmpxx.h>
#include "Fibonacci/fibonacci.hpp"
#include <filesystem>


int main() {
    Fibonacci fib("C:/Custom files/Programming/VS Code/Projects/MathCounter/Fibonacci/fibonacci_numbers.txt");
    //fib.CalculateNumberTo(2e7+5e6);
    std::cout << "Done!" << "\n";
    return 0;
}