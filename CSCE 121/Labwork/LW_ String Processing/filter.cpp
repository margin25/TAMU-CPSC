#include <iostream>
#include <string>
using std::cin, std::cout, std::endl, std::string;

int main()
{
    string filter;
    string input;
    cout << "Please enter the sentence: ";
    cin >> input;
    cout << endl;
    cout << "Please enter the filter word: ";
    cin >> filter;
    cout << endl;
    cout << "Filtered sentence: ";
    int location = input.find(filter);
    string hash = "";
    for (int i = 0; i < filter.size(); i++)
        hash += "#";
    input.replace(location, filter.size(), hash);
    cout << input << endl;
    return 0;
}