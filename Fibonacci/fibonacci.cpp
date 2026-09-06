#include "fibonacci.hpp"

void Fibonacci::CalculateNumbers(const unsigned int& amount) {
    std::ofstream file(txt_file_path, std::ios_base::app);
    if (!file) {
        throw std::runtime_error("Cant open file!");
    }

    std::cout << "Calculating " << amount << " numbers...\n";
    unsigned int starting_point = last_lines.last_line.index+1;
    for (unsigned int i = starting_point; i < starting_point+amount; ++i) {
        mpz_class next_number = last_lines.previous_line.value + last_lines.last_line.value;

        last_lines.previous_line.value = last_lines.last_line.value;
        last_lines.previous_line.index += 1;
        last_lines.last_line.value = next_number;
        last_lines.last_line.index += 1;
        cache.push_back(last_lines.last_line);
        if (((i+1) % CACHE_WIDTH) == 0) {
            SaveCache(file);
        }
    }

    if (cache.size() != 0) {
        SaveCache(file);
    }
    file.close();

    std::cout << "Finished calculating!\n";
}

void Fibonacci::CalculateNumbersTo(const unsigned int& to_number) {
    std::cout << "Calculating numbers to" << to_number << "...\n";
    cache.reserve(to_number+1);
    for (unsigned int i = last_lines.last_line.index+1; i < to_number+1; ++i) {
        mpz_class next_number = last_lines.previous_line.value + last_lines.last_line.value;

        last_lines.previous_line.value = last_lines.last_line.value;
        last_lines.previous_line.index += 1;
        last_lines.last_line.value = next_number;
        last_lines.last_line.index += 1;
        cache.push_back(last_lines.last_line);
    }
    std::cout << "Finished calculating!\n";
    Save();
}


void Fibonacci::CalculateNumberTo(const unsigned int& to_number) {
    std::cout << "Calculating number to " << to_number << "...\n";
    cache.reserve(to_number+1);
    for (unsigned int i = last_lines.last_line.index+1; i < to_number+1; ++i) {
        mpz_class next_number = last_lines.previous_line.value + last_lines.last_line.value;

        last_lines.previous_line.value = last_lines.last_line.value;
        last_lines.previous_line.index += 1;
        last_lines.last_line.value = next_number;
        last_lines.last_line.index += 1;
    }
    cache = {last_lines.previous_line, last_lines.last_line};
    std::cout << "Finished calculating!\n";
    Save();
}


void Fibonacci::ClearFile() const {
    std::ofstream file(txt_file_path, std::ios::trunc);
    file.close();
}


void Fibonacci::Save() const {
    std::ofstream file(txt_file_path);
    if (!file) {
        throw std::runtime_error("Cant open file!");
    }
    std::cout << "Saving...\n";
    for (Line line : cache) {
        file << std::right << std::setw(STRING_WIDTH) << line.index << " : " << line.value << '\n';
    }
    std::cout << "Saved!\n";
    file.close();
}


void Fibonacci::SaveCache(std::ofstream& file) {
    std::cout << "Saving cache...\n";
    for (Line line : cache) {
        file << std::right << std::setw(STRING_WIDTH) << line.index << " : " << line.value << '\n';
    }
    cache.clear();
    file.flush();
    std::cout << "Saved cache!\n";
}


void Fibonacci::ReadNumbers() {
    std::ifstream file(txt_file_path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cant open file!");
    }
    file.seekg(0, std::ios::end);
    std::streampos size = file.tellg();
    if (size == 0) {
        std::cout << "File is empty!\n";
        return;
    }
    std::vector<std::string> string_lines = StringUtils::ReadLastLines(2, txt_file_path);
    last_lines.previous_line = StringUtils::ParseToLine(string_lines[0]);
    last_lines.last_line = StringUtils::ParseToLine(string_lines[1]);
    cache = {last_lines.previous_line, last_lines.last_line};
}


bool Fibonacci::IsFileEmpty() const {
    std::ofstream file(txt_file_path, std::ios_base::app);
    if (!file) {
        throw std::runtime_error("Cant open file!");
    }
    return std::filesystem::file_size(txt_file_path) == 0;
}