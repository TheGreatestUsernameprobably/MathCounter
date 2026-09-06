#include "fibonacci.hpp"

void Fibonacci::CalculateNumbers(const unsigned int& amount) {
    if (amount <= last_lines.last_line.index) { return; }
    std::cout << "Calculating...\n";
    for (unsigned int i = last_lines.last_line.index+1; i < amount+1; ++i) {
        mpz_class next_number = last_lines.previous_line.value + last_lines.last_line.value;
        last_lines.previous_line.value = last_lines.last_line.value;
        last_lines.previous_line.index += 1;
        last_lines.last_line.value = next_number;
        last_lines.last_line.index += 1;
    }
    std::cout << "Finished calculating!\n";
    SaveNumbers();
}

void Fibonacci::CalculateNumbersTo(const unsigned int& to_number) {
    if (to_number <= last_lines.last_line.index) { return; }
    numbers.reserve(to_number+1);
    std::cout << "Calculating...\n";
    for (unsigned int i = numbers.size(); i < to_number+1; ++i) {
        mpz_class next_number = numbers[i-1] + numbers[i-2];
        numbers.push_back(next_number);
    }
    std::cout << "Finished calculating!\n";
    SaveNumbers();
}


void Fibonacci::SaveNumbers() const {
    std::ofstream file(txt_file_path);
    if (!file) {
        throw std::runtime_error("Cant open file!");
    }
     std::cout << "Saving...\n";
    int width = std::to_string(numbers.size() - 1).length();
    for (size_t i = 0; i < numbers.size(); ++i) {
        file << std::right << std::setw(width) << i << " : " << numbers[i] << '\n';
    }
    std::cout << "Saved!\n";
    file.close();
}


void Fibonacci::ReadNumbers() {
    std::ifstream file(txt_file_path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cant open file!");
    }
    file.seekg(0, std::ios::end);
    std::streampos size = file.tellg();
    if (size == 0) {
        throw std::runtime_error("File is empty!");
    }
    std::vector<std::string> string_lines = StringUtils::ReadLastLines(2, txt_file_path);
    last_lines.previous_line = StringUtils::ParseToLine(string_lines[0]);
    last_lines.previous_line = StringUtils::ParseToLine(string_lines[1]);
}
