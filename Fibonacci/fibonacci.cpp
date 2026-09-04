#include "fibonacci.hpp"

void Fibonacci::CalculateNumbers(unsigned int amount) {
    if (amount <= numbers.size()) { return; }
    numbers.reserve(amount);
    for (unsigned int i = numbers.size(); i < amount; ++i) {
        mpz_class next_number = numbers[i-1] + numbers[i - 2];
        numbers.push_back(next_number);
    }
}


void Fibonacci::PrintNumbers() const {
    for (size_t i = 0; i < numbers.size(); ++i) {
        std::cout << i << " : " << numbers[i] << "\n";
    }
}


void Fibonacci::SaveNumbers() const {
    std::ofstream out("C:/Custom files/Programming/VS Code/Projects/MathCounter/Fibonacci/fibonacci_numbers.txt");
    if (!out) {
        std::cout << "Cant open file!" << "\n";
        return;
    }
    int width = std::to_string(numbers.size() - 1).length();

    std::cout << "File opened!\n";
    for (size_t i = 0; i < numbers.size(); ++i) {
        out << std::right << std::setw(width) << i+1 << " : " << numbers[i] << '\n';
    }
    std::cout << "File closed!\n";
    out.close();
}
