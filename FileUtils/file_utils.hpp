#pragma once

#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>


namespace FileUtils {
    void CreateFile(const std::string& file_path);
    void ClearFile(const std::string& file_path);
    bool isFileEmpty(const std::string& path);
}