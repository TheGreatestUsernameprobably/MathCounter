#include "file_manager.hpp"


void FileManager::SetupFile(const std::string& file_path) {
    FileUtils::CreateFile(file_path);
}


void FileManager::SetupHeader(std::fstream& file) {
    if (!std::filesystem::exists(bin_file_path)) {
        FileUtils::CreateFile(bin_file_path);
    }
    if (std::filesystem::file_size(bin_file_path) == 0) {
        WriteEmptyHeader(file);
        return;
    }

    file.read(reinterpret_cast<char*>(&header.reading_offset), sizeof(header.reading_offset));
    file.read(reinterpret_cast<char*>(&header.last_number_offset), sizeof(header.last_number_offset));
    file.read(reinterpret_cast<char*>(&header.count), sizeof(header.count));
}


void FileManager::WriteEmptyHeader(std::fstream& file) {
    uint64_t zero_64 = 0;
    uint32_t zero_32 = 0;
    file.seekp(0);
    file.write(reinterpret_cast<const char*>(&zero_64), sizeof(zero_64));
    file.write(reinterpret_cast<const char*>(&zero_64), sizeof(zero_64));
    file.write(reinterpret_cast<const char*>(&zero_32), sizeof(zero_32));
}


void FileManager::WriteHeader(std::fstream& file) {
    file.seekp(0);
    file.write(reinterpret_cast<const char*>(&header.reading_offset), sizeof(header.reading_offset));
    file.write(reinterpret_cast<const char*>(&header.last_number_offset), sizeof(header.last_number_offset));
    file.write(reinterpret_cast<const char*>(&header.count), sizeof(header.count));
}


// void FileManager::WriteNumbers(const std::vector<mpz_class>& numbers) {
//     for (size_t i = 0; i < numbers.size(); ++i) {
//         const auto& line = numbers[i];
//         // Saving fibonacci number index, byte length of number and it`s value
//         uint32_t index = line.index;
//         auto bytes = SerializeMPZ(line.value);
//         uint64_t bytes_length = static_cast<uint32_t>(bytes.size());
//         //std::cout << line.value << "\n";
//         file.write(reinterpret_cast<const char*>(&index), sizeof(index));
//         file.write(reinterpret_cast<const char*>(&bytes_length), sizeof(bytes_length));
//         file.write(reinterpret_cast<const char*>(bytes.data()), bytes_length);

//         uint64_t current_offset = file.tellp();
//         if (i == cache.size()-1) {
//             last_numer_bytes_offset = current_offset;
//         }
//         else if (i == cache.size()-2) {
//             previous_numer_bytes_offset = current_offset;

//         }
//     }
// }