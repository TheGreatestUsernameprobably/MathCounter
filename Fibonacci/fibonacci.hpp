#pragma once
#include <iostream>
#include <gmpxx.h>
#include <vector>
#include <fstream>
#include <iomanip>
#include "../StringUtils/string_utils.hpp"
#include "../BaseCounter/base_counter.hpp"
#include <filesystem>

class Fibonacci : public BaseCounter{
    private: 
        const unsigned int STRING_WIDTH = 10;
        const unsigned int CACHE_WIDTH = 1000;
        struct LastLines {
            Line previous_line;
            Line last_line;
        };
        LastLines last_lines = {
            Line{0, 0},
            Line{1, 1}
        };
        std::vector<Line> cache;
        void Save() const;
        void SaveCache(std::ofstream& file);
        void ReadNumbers();
        bool IsFileEmpty() const;
    public:
        void ClearFile() const;
        Fibonacci(const std::string& file_name) {
            txt_file_path = file_name;
            if (!IsFileEmpty()) {
                ReadNumbers();
            }
            cache = {last_lines.previous_line, last_lines.last_line};
        }
        std::string txt_file_path;
        void CalculateNumbers(const unsigned int& amount);
        void CalculateNumbersTo(const unsigned int& to_number);
        void CalculateNumberTo(const unsigned int& to_number);
};