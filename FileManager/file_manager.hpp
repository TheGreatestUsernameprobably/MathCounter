#pragma once
#include <cstdint>
#include <gmpxx.h>
#include <vector>
#include <filesystem>
#include <fstream>
#include <string>
#include "../FileUtils/file_utils.hpp"
#include "../Counter/counter.hpp"

class FileManager {
    protected:
        struct Header {
            uint64_t reading_offset = 0;
            uint64_t last_number_offset = 0;
            uint32_t count = 0;
        };
        struct LineStructure {
            uint64_t previous_number_offset = 0;
            uint32_t index = 0;
            uint64_t bytes_size = 0;
            mpz_class value = 0;
        };
        Header header;

        void SetupFile(const std::string& file_path);
        virtual void SetupHeader(std::fstream& file);
        virtual void WriteEmptyHeader(std::fstream& file);
        virtual void WriteNumbers(const std::vector<mpz_class>& numbers) = 0;
        virtual void WriteHeader(std::fstream& file);
    public:
        std::string system_name;
        std::string text_file_path;
        std::string bin_file_path;
        FileManager(const std::string& txt_path, const std::string& bin_path) : text_file_path(txt_path), bin_file_path(bin_path) {
            SetupFile(bin_file_path);
            SetupFile(text_file_path);
            std::fstream file(bin_file_path, std::ios::binary | std::ios_base::in | std::ios_base::out);
            SetupHeader(file);
            file.close();
        }
        virtual ~FileManager() = default;



};