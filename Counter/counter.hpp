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
        std::vector<Line> base_value = {Line{0, 0}};
        std::vector<Line> cache = base_value;

        virtual void CountLastNumbers(uint32_t amount)= 0;
        virtual void CountLastNumbersToIndex(uint32_t to) = 0;
        virtual void CountNumbers(uint32_t amount)= 0;
        virtual void CountNumbersToIndex(uint32_t to) = 0;
        virtual void CalculateNumber() = 0;
};