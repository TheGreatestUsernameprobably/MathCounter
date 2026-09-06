#pragma once
#include <iostream>
#include <gmpxx.h>
#include <vector>
#include <fstream>
#include <iomanip>
#include "../StringUtils/string_utils.hpp"
#include "../BaseCounter/base_counter.hpp"

class Fibonacci : public BaseCounter{
    private: 
        //std::vector<mpz_class> numbers = {0, 1};
        struct LastLines {
            Line previous_line;
            Line last_line;
        };
        LastLines last_lines = {
            Line{0, 1},
            Line{1, 1}
        };
        void SaveNumbers() const;
        void ReadNumbers();
    public:
        std::string txt_file_path = "C:/Custom files/Programming/VS Code/Projects/MathCounter/Fibonacci/fibonacci_numbers.txt";
        void CalculateNumbers(const unsigned int& amount);
        void CalculateNumbersTo(const unsigned int& to_number);
};