#pragma once
#include "..\Counter\counter.hpp"
#include "..\FileManager\file_manager.hpp"
#include <memory>


class CounterSystem {
    std::unique_ptr<Counter> counter;
    std::unique_ptr<FileManager> file_manager;
    virtual void CountLastNumbers(uint32_t amount)= 0;
    virtual void CountLastNumbersToIndex(uint32_t to) = 0;
    virtual void CountNumbers(uint32_t amount)= 0;
    virtual void CountNumbersToIndex(uint32_t to) = 0;
};