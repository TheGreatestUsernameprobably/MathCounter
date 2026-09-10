#include "file_utils.hpp"

namespace FileUtils {
    void CreateFile(const std::string& file_path) {
    if (!std::filesystem::exists(file_path)) {
        std::ofstream create(file_path);
        create.close();
    }
    }


    void ClearFile(const std::string& file_path) {
        std::ofstream file(file_path, std::ios::trunc);
        file.close();
    }
}