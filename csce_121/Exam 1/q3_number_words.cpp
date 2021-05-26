/* 
QUESTION 3
Number Words
Write a function that takes as input a non-negative integer in the range 0 to 99 and returns the
English word(s) for the number as a string. Multiple words should be separated by a dash. If
the input exceeds 99, the function should throw an invalid_argument exception.
The function declaration is:
string number_words(unsigned int n);
Examples
1. 0 → “zero”
2. 13 → “thirteen”
3. 42 → “forty-two”
4. 70 → “seventy”
5. 121 → std::invalid_argument
*/
#include <string>

using std::string;

string number_words(unsigned int n)
{
    // TODO(student): write your answer (i.e. comments, code) here
    // first check invalid argument
    //case 1 : <20
    //case 2 : 20-30 (inclusive)
    //case 3 : 30-40 (inclusive)
    //case 3 : 40-50 (inclusive)
    //case 4 : 50-60 (inclusive)
    //case 5 : 60-70 (inclusive)
    //case 6 : 80-90 (inclusive)
    //case 7 : 90-99 (inclusive)
    /* string string_version_of_int;
    if (n > 99) // throws invalid argument exception if input > 99
    {
        throw std::invalid_argument("invalid argument");
    }
    if (n == 0)
    {
        string_version_of_int = "zero";
    }
    else if (n == 1)
    {
        string_version_of_int = "one";
    }
    else if (n == 2)
    {
        string_version_of_int = "two";
    }
    else if (n == 3)
    {
        string_version_of_int = "three";
    }
    else if (n == 4)
    {
        string_version_of_int = "four";
    }
    else if (n == 5)
    {
        string_version_of_int = "five";
    }
    else if (n == 6)
    {
        string_version_of_int = "six";
    }
    else if (n == 7)
    {
        string_version_of_int = "seven";
    }
    else if (n == 8)
    {
        string_version_of_int = "eight";
    }
    else if (n == 9)
    {
        string_version_of_int = "nine";
    }
    else if (n == 10)
    {
        string_version_of_int = "ten";
    }
    else if (n == 11)
    {
        string_version_of_int = "eleven";
    }
    else if (n == 12)
    {
        string_version_of_int = "twelve";
    }
    else if (n == 13)
    {
        string_version_of_int = "thirteen";
    }
    else if (n == 14)
    {
        string_version_of_int = "fourteen";
    }
    else if (n == 15)
    {
        string_version_of_int = "fifteen";
    }
    else if (n == 16)
    {
        string_version_of_int = "sixteen";
    }
    else if (n == 17)
    {
        string_version_of_int = "seventeen";
    }
    else if (n == 18)
    {
        string_version_of_int = "eighteen";
    }
    else if (n == 19)
    {
        string_version_of_int = "nineteen";
    }
    else if (n == 20)
    {
        string_version_of_int = "twenty";
    }
    else if (n == 21)
    {
        string_version_of_int = "twenty-one";
    }
    else if (n == 22)
    {
        string_version_of_int = "twenty-two";
    }
    else if (n == 23)
    {
        string_version_of_int = "twenty-three";
    }
    else if (n == 24)
    {
        string_version_of_int = "twenty-four";
    }
    else if (n == 25)
    {
        string_version_of_int = "twenty-five";
    }
    else if (n == 26)
    {
        string_version_of_int = "twenty-six";
    }
    else if (n == 27)
    {
        string_version_of_int = "twenty-seven";
    }
    else if (n == 28)
    {
        string_version_of_int = "twenty-eight";
    }
    else if (n == 29)
    {
        string_version_of_int = "twenty-nine";
    }
    else if (n == 30)
    {
        string_version_of_int = "thirty";
    }
    else if (n == 31)
    {
        string_version_of_int = "thirty-one";
    }
    else if (n == 32)
    {
        string_version_of_int = "thirty-two";
    }
    else if (n == 33)
    {
        string_version_of_int = "thirty-three";
    }
    else if (n == 34)
    {
        string_version_of_int = "thirty-four";
    }
    else if (n == 35)
    {
        string_version_of_int = "thirty-five";
    }

    else if (n == 36)
    {
        string_version_of_int = "thirty-six";
    }
    else if (n == 37)
    {
        string_version_of_int = "thirty-seven";
    }
    else if (n == 38)
    {
        string_version_of_int = "thirty-eight";
    }
    else if (n == 39)
    {
        string_version_of_int = "thirty-nine";
    }
    else if (n == 40)
    {
        string_version_of_int = "fourty";
    }
    else if (n == 41)
    {
        string_version_of_int = "fourty-one";
    }
    else if (n == 42)
    {
        string_version_of_int = "fourty-two";
    }
    else if (n == 43)
    {
        string_version_of_int = "fourty-three";
    }
    else if (n == 44)
    {
        string_version_of_int = "fourty-four";
    }
    else if (n == 45)
    {
        string_version_of_int = "fourty-five";
    }
    else if (n == 46)
    {
        string_version_of_int = "fourty-six";
    }
    else if (n == 47)
    {
        string_version_of_int = "fourty-seven";
    }
    else if (n == 48)
    {
        string_version_of_int = "fourty-eight";
    }
    else if (n == 49)
    {
        string_version_of_int = "fourty-nine";
    }
    else if (n == 50)
    {
        string_version_of_int = "fifty";
    }
    else if (n == 51)
    {
        string_version_of_int = "fifty-one";
    }
    else if (n == 52)
    {
        string_version_of_int = "fifty-two";
    }
    else if (n == 53)
    {
        string_version_of_int = "fifty-three";
    }
    else if (n == 54)
    {
        string_version_of_int = "fifty-four";
    }
    else if (n == 55)
    {
        string_version_of_int = "fifty-five";
    }
    else if (n == 56)
    {
        string_version_of_int = "fifty-six";
    }
    else if (n == 57)
    {
        string_version_of_int = "fifty-seven";
    }
    else if (n == 58)
    {
        string_version_of_int = "fifty-eight";
    }
    else if (n == 59)
    {
        string_version_of_int = "fifty-nine";
    }
    else if (n == 60)
    {
        string_version_of_int = "sixty";
    }
    else if (n == 61)
    {
        string_version_of_int = "sixty-one";
    }
    else if (n == 62)
    {
        string_version_of_int = "sixty-two";
    }
    else if (n == 63)
    {
        string_version_of_int = "sixty-three";
    }
    else if (n == 64)
    {
        string_version_of_int = "sixty-four";
    }
    else if (n == 65)
    {
        string_version_of_int = "sixty-five";
    }
    else if (n == 66)
    {
        string_version_of_int = "sixty-six";
    }
    else if (n == 67)
    {
        string_version_of_int = "sixty-seven";
    }
    else if (n == 68)
    {
        string_version_of_int = "sixty-eight";
    }
    else if (n == 69)
    {
        string_version_of_int = "sixty-nine";
    }
    else if (n == 70)
    {
        string_version_of_int = "seventy";
    }
    else if (n == 71)
    {
        string_version_of_int = "seventy-one";
    }
    else if (n == 72)
    {
        string_version_of_int = "seventy-two";
    }
    else if (n == 73)
    {
        string_version_of_int = "seventy-three";
    }
    else if (n == 74)
    {
        string_version_of_int = "seventy-four";
    }
    else if (n == 75)
    {
        string_version_of_int = "seventy-five";
    }
    else if (n == 76)
    {
        string_version_of_int = "seventy-six";
    }
    else if (n == 77)
    {
        string_version_of_int = "seventy-seven";
    }
    else if (n == 78)
    {
        string_version_of_int = "seventy-eight";
    }
    else if (n == 79)
    {
        string_version_of_int = "seventy-nine";
    }
    else if (n == 80)
    {
        string_version_of_int = "eighty";
    }
    //80
    else if (n == 80)
    {
        string_version_of_int = "eighty";
    }
    else if (n == 81)
    {
        string_version_of_int = "eighty-one";
    }
    else if (n == 82)
    {
        string_version_of_int = "eighty-two";
    }
    else if (n == 83)
    {
        string_version_of_int = "eighty-three";
    }
    else if (n == 84)
    {
        string_version_of_int = "eighty-four";
    }
    else if (n == 85)
    {
        string_version_of_int = "eighty-five";
    }
    else if (n == 86)
    {
        string_version_of_int = "eighty-six";
    }
    else if (n == 87)
    {
        string_version_of_int = "eighty-seven";
    }
    else if (n == 88)
    {
        string_version_of_int = "eighty-eight";
    }
    else if (n == 89)
    {
        string_version_of_int = "eighty-nine";
    }
    //ninety
    else if (n == 90)
    {
        string_version_of_int = "ninety";
    }
    else if (n == 91)
    {
        string_version_of_int = "ninety-one";
    }
    else if (n == 92)
    {
        string_version_of_int = "ninety-two";
    }
    else if (n == 93)
    {
        string_version_of_int = "ninety-three";
    }
    else if (n == 94)
    {
        string_version_of_int = "ninety-four";
    }
    else if (n == 95)
    {
        string_version_of_int = "ninety-five";
    }
    else if (n == 96)
    {
        string_version_of_int = "ninety-six";
    }
    else if (n == 97)
    {
        string_version_of_int = "ninety-seven";
    }
    else if (n == 98)
    {
        string_version_of_int = "ninety-eight";
    }
    else if (n == 99)
    {
        string_version_of_int = "ninety-nine";
    }
    else
    {
        string_version_of_int = "";
    }

    return string_version_of_int; */
    return (""); //only put this so this compiles when i submit it
}
