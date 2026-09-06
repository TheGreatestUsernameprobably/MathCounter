#include "string_utils.hpp"

const std::string StringUtils::spaces = " \t\n\r\f\v";

std::string StringUtils::TrimSpaces(const std::string& value) {
    size_t start = value.find_first_not_of(StringUtils::spaces);
    if (start == std::string::npos) return "";
    size_t end = value.find_last_not_of(StringUtils::spaces);
    return value.substr(start, end - start + 1);
}


std::vector<std::string> StringUtils::ReadLastLines(const unsigned int& number_of_lines, const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cant open file!");
    }
    file.seekg(0, std::ios::end);
    std::streampos size = file.tellg();
    if (size == 0) {
        throw std::runtime_error("File is empty!");
    }
    long long pos = size;
    int lines_found = 0;
    char ch;

    while (pos > 0 && lines_found <= number_of_lines) {
        pos--;
        file.seekg(pos, std::ios::beg);
        file.get(ch);

        if (ch == '\n') {
            lines_found++;
        }
    }

    if (pos == 0) {
        file.seekg(0, std::ios::beg);
    } else {
        file.seekg(pos + 1, std::ios::beg);
    }

    std::vector<std::string> last_lines;
    std::string line;
    while (std::getline(file, line)) {
        last_lines.push_back(line);
    }

    return last_lines;
}


BaseCounter::Line StringUtils::ParseToLine(const std::string& line) {
    size_t colon = line.find(':');
    if (colon == std::string::npos) {
        throw std::runtime_error("Invalid format: missing ':'");
    }
    std::string index_str = TrimSpaces(line.substr(0, colon));
    std::string value_str = TrimSpaces(line.substr(colon + 1));

    unsigned int index = std::stoi(index_str);
    mpz_class value(value_str);

    return BaseCounter::Line{index, value};
}