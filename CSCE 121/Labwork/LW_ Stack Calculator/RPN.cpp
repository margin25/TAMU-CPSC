#include <cmath>
#include <iostream>
#include <string>
#include "Stack.h"

// add function definitions
using std::cout, std::endl, std::string, std::cin, std::ifstream, std::stod;
//  The RPN algorithm is simple and uses a stack to store intermediate values of the computation:
string string_values;
int int_values;
// STEP 1: Read numbers and push onto the stack until you read an operator (one of +, -, *, /) or =
// Hint: read a string (e.g. std::string or char[]), then check if the first character is a digit
// or ‘.’ (dot). If so, then the string is an operand (convert to double with stod(std::string) or atof(char[])),
// otherwise the string is an operator (use switch to handle the different cases).
// syntax you'd like to have:
Stack new_stack;
double double_val;
double right;
double left;
double result;
int main()
{
    //cout << "Enter values: ";
    while (cin >> string_values)
    {
        //cout << string_values << endl;
        if (string_values.at(0) == '.')
        {
            //cout << "in if statement" << endl;
            double_val = stod(string_values);
            push(new_stack, double_val);
        }
        else if (isdigit(string_values[0]))
        {
            //cout << "in else if statement" << endl;
            double_val = stod(string_values);
            push(new_stack, double_val);
        }
        else if (string_values[0] == '=')
        {
            result = pop(new_stack);
            cout << result << endl;
        }
        else
        {
            //cout << "in else statement" << endl;
            right = pop(new_stack);
            left = pop(new_stack);
            if (string_values[0] == '+')
            {
                //cout << "in + statement" << endl;
                result = (right + left);
                //cout << result << endl;
                push(new_stack, result);
            }
            else if (string_values[0] == '-')
            {
                //cout << "in + statement" << endl;
                result = (left - right);
                //cout << result << endl;
                push(new_stack, result);
            }
            else if (string_values[0] == '*')
            {
                //cout << "in + statement" << endl;
                result = (right * left);
                //cout << result << endl;
                push(new_stack, result);
            }
            else if (string_values[0] == '/')
            {
                //cout << "in + statement" << endl;
                result = (left / right);
                //cout << result << endl;
                push(new_stack, result);
            }
            else
            {
                cout << "[ERROR] invalid operator: " << string_values << endl;
                break;
            }
        }
    }
    return (0);
}

// STEP 2: If an operator (+, -, *, or /) is read,
// pop the top two elements of the stack into variables for right and left operands
// First pop goes into right
// Second pop goes into left
// Do the operation and push the result onto the stack

// STEP 3: Repeat steps 1,2 until ‘=’ is read

//STEP 4: Pop the result from the stack
