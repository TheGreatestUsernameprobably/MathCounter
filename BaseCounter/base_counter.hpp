#pragma once
#include <gmpxx.h>

class BaseCounter {
    public:
        struct Line {
                unsigned int index;
                mpz_class value;
            };
    
};