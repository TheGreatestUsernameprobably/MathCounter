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