#include <iostream>
#include <string>
using std::cin, std::cout, std::endl, std::string;

int main() {
    string user_input; 
    string length; 
    unsigned var;
    int og = 0; 
    int notog = 0;
    cout << "Please enter obfuscated sentence: ";
    cin >> user_input;
    cout << "Please enter deobfuscation details: ";
    cin >> length;
    cout << "Deobfuscated sentence: ";
    //convert deobfuscation chars to int
    if(length.size() >1){
        for(int i = 0;i<length.size();i++){
        var = length.at(i) - '0';
        og+=var;
        user_input.insert(og," ");
        og++;
        }
    cout << user_input << " ";
    }
    else{
        for(int i = 0;i<length.size();i++){
        var = length.at(i) - '0';
        og+=var;
        cout << user_input.substr(0,var) << " ";
    }
    
    }
    cout << endl;
    return (0);
}

