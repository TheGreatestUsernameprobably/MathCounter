#pragma once
#include "..\..\Counter\counter.hpp"

class FibonacciCounter : public Counter {
    private:
        uint32_t current_index = 0;
        Counter::Line last_line{1, 0};
        Counter::Line previous_line{0, 0};
        bool CheckIndex(const uint32_t to) const;
    public:
        void CountLastNumbers(const uint32_t amount) override;
        void CountLastNumbersToIndex(const uint32_t to) override;
        void CountNumbers(const uint32_t amount) override;
        void CountNumbersToIndex(const uint32_t to) override;
        void CalculateNumber() override;
};