#include "fibonacci_counter.hpp"

bool FibonacciCounter::CheckIndex(const uint32_t to) const
{
    if (current_index <= to) {
        std::cout << "Already calculated that number" << "\n";
        return true;
    }
    return false;
}

void FibonacciCounter::CountLastNumbers(const uint32_t amount)
{

}

void FibonacciCounter::CountLastNumbersToIndex(const uint32_t to)
{
    if (CheckIndex(to)) return;
    cache.reserve(to+1);
    for (size_t i = current_index; i < to+1; ++i) {
        CalculateNumber();
        if (((i+1) % cache_size) == 0) {
            //here, how do i call a function from different file, from for example CounterSystem that has FileSystem that has Save() method?
        }
    }
}

void FibonacciCounter::CountNumbers(const uint32_t amount)
{
}

void FibonacciCounter::CountNumbersToIndex(const uint32_t to)
{
    if (CheckIndex(to)) return;
}

void FibonacciCounter::CalculateNumber()
{
    mpz_class next_number = last_line.value + previous_line.value;
    previous_line.value = last_line.value;
    previous_line.index += 1;
    last_line.value = next_number;
    last_line.index += 1;
    cache.push_back(last_line);
}
