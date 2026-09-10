#pragma once
#include <iostream>
#include <gmpxx.h>
#include <vector>
#include <fstream>
#include <iomanip>
#include "../StringUtils/string_utils.hpp"
#include "../BaseCounter/base_counter.hpp"
#include "../FileUtils/file_utils.hpp"
#include <filesystem>
#include <cstdint>


class Fibonacci : public Counter{
    private: 
        const uint8_t STRING_WIDTH = 10;
        const uint16_t CACHE_WIDTH = 1000;
        struct LastLines {
            Line previous_line;
            Line last_line;
        };
        LastLines last_lines = {
            Line{0, 0},
            Line{1, 1}
        };
        std::vector<Line> cache;
        void UpdateFileHeader(std::fstream& file, uint64_t& last_numer_bytes_offset, uint64_t& previous_numer_bytes_offset, uint64_t& count);
        void ReadOneLine(std::ifstream& file, uint64_t offset, Line& line);
        void SaveBinary();
        void SaveCacheBinary(std::fstream& file);
        void ReadBinary();
        //void ReadNumbers();
        void WriteFileHeader(std::fstream& file);
        void WriteFileNumbers(std::fstream& file, uint64_t& last_numer_bytes_offset, uint64_t& previous_numer_bytes_offset) const;
        std::vector<unsigned char> SerializeMPZ(const mpz_class& num) const;
        mpz_class DeserializeMPZ(const std::vector<unsigned char>& bytes);
    public:
        Fibonacci(
            const std::string& txt_file_name,
            const std::string& bin_file_name) {
            txt_file_path = txt_file_name;
            bin_file_path = bin_file_name;
            if (!FileUtils::isFileEmpty(bin_file_path)) {
                ReadBinary();
            }
            cache = {last_lines.previous_line, last_lines.last_line};
        }
        std::string txt_file_path;
        std::string bin_file_path;
        void CalculateNumbers(const unsigned int& amount);
        void CalculateNumbersTo(const unsigned int& to_number);
        void CalculateNumberTo(const unsigned int& to_number);
        void Save() const;
};