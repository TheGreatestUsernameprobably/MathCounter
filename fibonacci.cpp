#include "fibonacci.hpp"

void Fibonacci::CalculateNumbers(unsigned int amount) {
    if (amount <= Fibonacci::numbers.size()) { return; }
    for (unsigned int i = Fibonacci::numbers.size(); i < amount+1; ++i) {
        mpz_class next_number = numbers[i-1] + numbers[i - 2];
        Fibonacci::numbers.push_back(next_number);
    }
}


void Fibonacci::PrintNumbers() const {
    for (size_t i = 0; i < numbers.size(); ++i) {
        std::cout << i << " : " << numbers[i] << "\n";
    }
}

