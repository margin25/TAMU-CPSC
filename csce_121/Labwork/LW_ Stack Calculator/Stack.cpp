#include <cmath>
#include <iostream>
#include <string>
#include "Stack.h"
using std::cout, std::endl, std::string, std::cin, std::ifstream;

// add function definitions

// add element to the top of Stack s
// if Stack s is full, resize the underlying array
void push(Stack &s, double element)
{
    if (s.capacity == s.length) // if Stack is full
    {
        s.capacity = s.capacity * 2;                // resizing the array should double the capacity
        double *new_array = new double[s.capacity]; // dynamically allocate memory of size = capacity
        for (int i = 0; i < s.length; i++)
        {
            new_array[i] = s.A[i]; //copying over values to new array
        }
        delete[] s.A;    // deallocate memory : makes sure memory leak does not occur for 1d array , deletes memory of new_array.
        s.A = new_array; //setting memory address of A equal to memory address of new_array
    }
    s.A[s.length] = element; // adds element to the top of the stack
    s.length++;              // increases length by 1 accordingly
}

// remove and return the element on top of Stack s
// if Stack s is empty, return NAN
double pop(Stack &s)
{
    if (s.length != 0)
    {
        double top_element = s.A[s.length - 1]; // holds value of last index
        s.length--;                             // decreases length accordingly
        return top_element;
    }
    else
    {
        return (NAN); // if Stack s is empty, return NAN
    }
}
