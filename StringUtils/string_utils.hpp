#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <array>
#include <gmpxx.h>
#include "../BaseCounter/base_counter.hpp"

class StringUtils {
    public:
        static const std::string spaces;
        static std::string TrimSpaces(const std::string& value);
        static std::vector<std::string> ReadLastLines(const unsigned int& number_of_lines, const std::string& filename);
        static BaseCounter::Line ParseToLine(const std::string& line);
};