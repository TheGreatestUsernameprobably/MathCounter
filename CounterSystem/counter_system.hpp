#pragma once
#include "..\Counter\counter.hpp"
#include "..\FileManager\file_manager.hpp"
#include <memory>


class CounterSystem {
    std::unique_ptr<Counter> counter;
    std::unique_ptr<FileManager> file_manager;
    virtual void CountNumber(uint32_t amount)= 0;
    virtual void CountNumberTo(uint32_t to) = 0;
    virtual void CountNumbers(uint32_t amount)= 0;
    virtual void CountNumbersTo(uint32_t to) = 0;
};