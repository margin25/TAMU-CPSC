// string_calculator.cpp
#include <iostream>
#include "my_string.h"
#include "./string_calculator.h"

using std::cout, std::endl;

unsigned int digit_to_decimal(char digit)
{
    // TODO(student): put your existing implementation here
    /*
    convert a character digit to an integer value
    input: digit - a character representing a digit, e.g. '7'
    output: the corresponding integer value of the digit, e.g. 7
    throws: std::invalid_argument if the input is not a valid digit, e.g. '0' -- '9'
    */
    // TODO(student): implement
    int var;
    var = digit - '0';
    if ((digit == '/') || (digit == '(') || (digit == '[') || (digit == '`') || (digit == '{') || (digit == '+') || (digit == '-') || (digit == '*') || (digit == '^') || (digit == ')') || (digit == '}') || (digit == ']'))
    {
        throw std::invalid_argument("invalid argument hehe");
    }

    if (!(var > 0 || var <= 9))
    {
        throw std::invalid_argument("invalid argument wow");
    }
    return var;
}

char decimal_to_digit(unsigned int decimal)
{
    // TODO(student): put your existing implementation here
    if (decimal >= 10)
    {
        throw std::invalid_argument("invalid argument umm");
    }
    unsigned var;
    if (decimal == 0)
        var = '0';
    if (decimal == 1)
        var = '1';
    if (decimal == 2)
        var = '2';
    if (decimal == 3)
        var = '3';
    if (decimal == 4)
        var = '4';
    if (decimal == 5)
        var = '5';
    if (decimal == 6)
        var = '6';
    if (decimal == 7)
        var = '7';
    if (decimal == 8)
        var = '8';
    if (decimal == 9)
        var = '9';
    return var;
}

/* my_string trim_leading_zeros(const my_string& num) {
    // TODO(student): put your existing implementation here
    return "";
    
}

my_string add(const my_string& lhs, const my_string& rhs) {
    // TODO(student): put your existing implementation here
    return "";
}

my_string subtract(const my_string& lhs, const my_string& rhs) {
    // TODO(student): put your existing implementation here
    return "";
}

my_string multiply(const my_string& lhs, const my_string& rhs) {
    // TODO(student): put your existing implementation here
    return "";
}
 */