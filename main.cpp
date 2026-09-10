#include <iostream>
#include <vector>
#include <gmpxx.h>
#include "Fibonacci/fibonacci.hpp"
#include <filesystem>

const std::string TXT_PATH = "C:/Custom files/Programming/VS Code/Projects/MathCounter/Fibonacci/fibonacci_numbers.txt";
const std::string BIN_PATH = "C:/Custom files/Programming/VS Code/Projects/MathCounter/Fibonacci/fibonacci_numbers.bin";



int main() {
    Fibonacci fib(TXT_PATH, BIN_PATH);
    FileUtils::ClearFile(fib.bin_file_path);
    fib.CalculateNumbers(1e2);
    FileUtils::CreateFile("C:/Custom files/Programming/VS Code/Projects/MathCounter/Fibonacci/test.txt");
    std::cout << "Done!" << "\n";
    return 0;
}