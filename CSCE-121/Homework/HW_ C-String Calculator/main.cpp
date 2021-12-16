// main.cpp
#include <iostream>
#include <limits>
#include "my_string.h"
#include "my_sstream.h"
#include "./string_calculator.h"

using std::cout, std::endl, std::cin;

int main()
{
    my_string test = "moo";
    my_string test_2 = test;
    my_string test_3 = 'c' + test;
    //char greeting[2] = {'m', '\0'};
    /* cout << "String Calculator" << endl;
    cout << test.at(0) << endl;
    cout << test[0] << endl; */
    //cout << test + greeting << endl;
    cout << "moo moo : " << test + test_2 << endl;
    my_string something_else = "hellohello";
    //cin >> something_else;
    cout << test.substr(1) << endl;
    cout << something_else << endl;
    //cout << test.substr(1) << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;

    // TODO(student): put your existing implementation of main here
}
