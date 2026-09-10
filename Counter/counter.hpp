#pragma once
#include <gmpxx.h>
#include <cstdint>
#include <vector>
#include <iostream>

class Counter {
    protected:
        std::vector<mpz_class> base_value = {0};
        std::vector<mpz_class> cache = base_value;

        struct Line {
                uint32_t index;
                mpz_class value;
            };
        
        virtual void CountNumber(uint32_t amount)= 0;
        virtual void CountNumberTo(uint32_t to) = 0;
        virtual void CountNumbers(uint32_t amount)= 0;
        virtual void CountNumbersTo(uint32_t to) = 0;
        virtual void CalculateNumber() = 0;
};