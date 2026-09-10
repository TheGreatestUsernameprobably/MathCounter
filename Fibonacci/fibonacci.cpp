#include "fibonacci.hpp"

void Fibonacci::CalculateNumbers(const unsigned int& amount) {
    std::fstream file(bin_file_path, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
    if (FileUtils::isFileEmpty(bin_file_path))  WriteFileHeader(file);
    
    file.seekp(0, std::ios_base::end);
    unsigned int starting_point = last_lines.last_line.index+1;
    uint64_t prev_offset = 0, last_offset = 0, count = starting_point+amount;

    std::cout << "Calculating " << amount << " numbers...\n";
    for (unsigned int i = starting_point; i < amount; ++i) {
        mpz_class next_number = last_lines.previous_line.value + last_lines.last_line.value;
        last_lines.previous_line.value = last_lines.last_line.value;
        last_lines.previous_line.index += 1;
        last_lines.last_line.value = next_number;
        last_lines.last_line.index += 1;
        std::cout << last_lines.last_line.value << "\n";

        cache.push_back(last_lines.last_line);

        if (((i+1) % CACHE_WIDTH) == 0) {
            WriteFileNumbers(file, prev_offset, last_offset);
            cache.clear();
        }
    }
    if (cache.size() > 1) {
        WriteFileNumbers(file, prev_offset, last_offset);
        cache.clear();
    }

    UpdateFileHeader(file, prev_offset, last_offset, count);
    cache.clear();
    file.close();
    std::cout << "Remaining cache size: " << cache.size() << std::endl;
    std::cout << "last_offset = " << last_offset << ", prev_offset = " << prev_offset << std::endl;
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
    SaveBinary();
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
    SaveBinary();
}


void Fibonacci::ReadBinary() {
    std::ifstream file(bin_file_path, std::ios::binary);
    if (!file) {
        last_lines = { Line{0, 0}, Line{1, 1} };
        cache = {last_lines.previous_line, last_lines.last_line};
        return;
    }
    uint64_t prev_offset, last_offset, count;
    file.read(reinterpret_cast<char*>(&prev_offset), sizeof(prev_offset));
    file.read(reinterpret_cast<char*>(&last_offset), sizeof(last_offset));
    file.read(reinterpret_cast<char*>(&count), sizeof(count));
    ReadOneLine(file, prev_offset, last_lines.previous_line);
    ReadOneLine(file, last_offset, last_lines.last_line);
    std::cout << last_lines.last_line.value << "\n";
    std::cout << last_lines.previous_line.value << "\n";
    cache = {last_lines.previous_line, last_lines.last_line};
}


void Fibonacci::ReadOneLine(std::ifstream& file, uint64_t offset, Line& line) {
    file.seekg(offset);

    uint64_t index;
    file.read(reinterpret_cast<char*>(&index), sizeof(index));

    uint64_t len;
    file.read(reinterpret_cast<char*>(&len), sizeof(len));

    std::vector<unsigned char> bytes(len);
    if (len > 0) file.read(reinterpret_cast<char*>(bytes.data()), len);

    line.index = index;
    line.value = DeserializeMPZ(bytes);
}


void Fibonacci::SaveBinary() {
    std::fstream file(bin_file_path, std::ios::binary);
    if (!file) throw std::runtime_error("Cant open file!");

    std::cout << "Saving...\n";
    uint64_t last_numer_bytes_offset = 0, previous_numer_bytes_offset = 0, count = cache.size();
    WriteFileHeader(file);
    WriteFileNumbers(file, previous_numer_bytes_offset, last_numer_bytes_offset);
    UpdateFileHeader(file, previous_numer_bytes_offset, last_numer_bytes_offset, count);
    std::cout << "Saved!\n";
    file.close();
    cache.clear();
}


void Fibonacci::WriteFileHeader(std::fstream& file) {
    // Saving first 2 bytes offsets
    uint64_t zero = 0;
    file.seekp(0);
    file.write(reinterpret_cast<const char*>(&zero), sizeof(zero));
    file.write(reinterpret_cast<const char*>(&zero), sizeof(zero));
    file.write(reinterpret_cast<const char*>(&zero), sizeof(zero));
}


void Fibonacci::WriteFileNumbers(std::fstream& file, uint64_t& previous_numer_bytes_offset, uint64_t& last_numer_bytes_offset) const {
    //std::cout << "WriteFileNumbers called, cache size = " << cache.size() << std::endl;
    for (size_t i = 0; i < cache.size(); ++i) {
        const auto& line = cache[i];
        // Saving fibonacci number index, byte length of number and it`s value
        uint64_t index = line.index;
        auto bytes = SerializeMPZ(line.value);
        uint64_t bytes_length = static_cast<uint32_t>(bytes.size());
        //std::cout << line.value << "\n";
        file.write(reinterpret_cast<const char*>(&index), sizeof(index));
        file.write(reinterpret_cast<const char*>(&bytes_length), sizeof(bytes_length));
        file.write(reinterpret_cast<const char*>(bytes.data()), bytes_length);

        uint64_t current_offset = file.tellp();
        if (i == cache.size()-1) {
            last_numer_bytes_offset = current_offset;
        }
        else if (i == cache.size()-2) {
            previous_numer_bytes_offset = current_offset;

        }
    }
}


void Fibonacci::UpdateFileHeader(
    std::fstream& file, uint64_t& previous_numer_bytes_offset, uint64_t& last_numer_bytes_offset,
    uint64_t& count) {
    file.seekp(0);
    file.write(reinterpret_cast<const char*>(&previous_numer_bytes_offset), sizeof(previous_numer_bytes_offset));
    file.write(reinterpret_cast<const char*>(&last_numer_bytes_offset), sizeof(last_numer_bytes_offset));
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));
}


void Fibonacci::Save() const {
    std::ofstream file(txt_file_path);
    if (!file) {
        throw std::runtime_error("Cant open file!");
    }
    std::cout << "Saving text...\n";
    for (Line line : cache) {
        file << std::right << std::setw(STRING_WIDTH) << line.index << " : " << line.value << '\n';
    }
    std::cout << "Saving text...\n";
    file.close();
}


std::vector<unsigned char> Fibonacci::SerializeMPZ(const mpz_class& num) const {
    size_t count = 0;
    void* data = mpz_export(nullptr, &count, 1, 1, 0, 0, num.get_mpz_t());
    std::vector<unsigned char> bytes;
    if (count > 0) {
        bytes.assign(
                    static_cast<unsigned char*>(data),
                    static_cast<unsigned char*>(data) + count);
        free(data);
    }
    return bytes;
}


mpz_class Fibonacci::DeserializeMPZ(const std::vector<unsigned char>& bytes) {
    mpz_class result;
    if (bytes.empty()) {
        result = 0;
    } else {
        mpz_import(result.get_mpz_t(), bytes.size(), 1, 1, 0, 0, bytes.data());
    }
    return result;
}