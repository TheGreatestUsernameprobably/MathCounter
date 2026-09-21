#pragma once
#include <gmpxx.h>
#include <cstdint>
#include <vector>
#include <iostream>

class Counter {
    public:
        virtual ~Counter() = default;
    protected:
        struct Line {
                    uint32_t index;
                    mpz_class value;
                };
        std::vector<Line> cache = {};
        uint32_t cache_size = 1e3;
        virtual void CountLastNumbers(const uint32_t amount)= 0;
        virtual void CountLastNumbersToIndex(const uint32_t to) = 0;
        virtual void CountNumbers(const uint32_t amount)= 0;
        virtual void CountNumbersToIndex(const uint32_t to) = 0;
        virtual void CalculateNumber() = 0;
};