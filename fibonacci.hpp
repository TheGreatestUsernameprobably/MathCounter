#pragma once
#include <iostream>
#include <gmpxx.h>
#include <vector>

class Fibonacci {
    private: 
        std::vector<mpz_class> numbers = {0, 1};
    public:
        void CalculateNumbers(unsigned int amount);
        void PrintNumbers() const;
};