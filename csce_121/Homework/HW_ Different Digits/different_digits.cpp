#include <iostream>
#include <limits>
#include "functions.h"

using std::cout, std::cin, std::endl;

int main()
{
    // TODO(student): print prompt for input
    cout << "Enter numbers 0 < a <= b <= 10000:";
    // TODO(student): read the numbers from standard input
    int num_1;
    int num_2;
    cout << " ";
    cin >> num_1;
    cout << " ";
    cin >> num_2;

    // TODO(student): validate input (and reprompt on invalid input)
    while (is_valid_range(num_1, num_2) != true)
    {
        cout << "Invalid input" << endl;
        cout << "Enter numbers 0 < a <= b <= 10000:";
        cin >> num_1;
        cout << " ";
        cin >> num_2;
    }

    // TODO(student): compute and display solution
    cout << "There are " << count_valid_numbers(num_1, num_2) << " valid numbers between " << num_1 << " and " << num_2 << endl;
    return 0;
}
