#ifndef VALIDATION_H
#define VALIDATION_H
#include <iostream>
#include <string>

using namespace std;

class Validation
{
    public:
        bool is_string(string );
        bool is_integer(string );
        bool is_double(string );
        bool is_formula(string );
};

#endif // VALIDATION_H
