#include <iostream>
#include <string>
#include "./string_calculator.h"
using std::cout, std::endl;
using std::string;

unsigned int digit_to_decimal(char digit)
{
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
    /*
    convert an integer value to a character digit
    input: decimal - an integer value of a digit, e.g. 7
    output: the corresponding character of the digit, e.g. '7'
    throws: std::invalid_argument if the input is not a valid digit, e.g. 0 -- 9
    */
    // TODO(student): implement
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

string trim_leading_zeros(string num)
{
    /*
    remove the leading zeros from a number
    input: num - a string representing a number with zero or more leading 0s
    output: a copy of the input with all leading 0s removed
    throws: none 
    */
    // TODO(student): implement
    long unsigned int j = 0;
    while (num.at(j) == '0')
    {
        j++;
        if (j == num.size())
            break;
    }
    //case where they are all 0 (positive numbers)
    if (num.size() == j)
        return ("0");
    //case where they are NOT all 0 (positive numbers)
    else
    {
        num.erase(0, j);
    }
    //negative numbers
    if (num.at(0) == '-')
    {
        string wo_neg = trim_leading_zeros(num.substr(1));
        //case where they are  all 0 (negative numbers)
        if (wo_neg == "0")
            return ("0");
        //case where they are NOT all 0 (negative numbers)
        else
            return ('-' + wo_neg);
    }
    return num;
}

string add(string lhs, string rhs)
{
    /*
    add two numbers 
    input: lhs,rhs - strings representing numbers, e.g. "1", "2"
    output: the result of adding rhs to lhs: lhs + rhs e.g. "3"
    throws: none.
    */
    // TODO(student): implement
    //small,positive
    int lhs_int = digit_to_decimal(lhs.at(lhs.size() - 1)); //initializes rightmost digit of LHS as int
    int rhs_int = digit_to_decimal(rhs.at(rhs.size() - 1)); //initializes rightmost digit of RHS as int
    int sum_int = 0;                                        // initializes sum of current column
    int carry = 0;                                          // initalizes carry value
    int range = 0;                                          // initalizes value that will tell us how many times for loop is going to loop
    int column_sum = 0;                                     //initializes calculations for ones place
    string Answer = "";                                     // initalizes value that will hold the Answer as a string
    if ((lhs.at(0) == '-') && (rhs.at(0) == '-'))           // do when both lhs and rhs are negatives
    {
        lhs = lhs.substr(1);
        rhs = rhs.substr(1);
        Answer = "-" + add(lhs, rhs);
        return Answer;
    }
    else if ((rhs.at(0) == '0') && (lhs.at(0) == '-'))
    {
        lhs = lhs.substr(1);
        Answer = "-" + add(lhs, rhs);
        return Answer;
    }
    else if ((lhs.at(0) == '0') && (rhs.at(0) == '-'))
    {
        rhs = rhs.substr(1);
        Answer = "-" + add(lhs, rhs);
        return Answer;
    }
    else if ((lhs.at(0) != '0') && (rhs.at(0) == '-'))
    {
        rhs = rhs.substr(1);
        return (subtract(lhs, rhs));
    }
    else if (((lhs.at(0) == '-') && (rhs.at(0) != '0')))
    {
        lhs = lhs.substr(1);
        return (subtract(rhs, lhs));
    }

    // small,opposite signs, negative results
    if (rhs.size() == lhs.size()) // if str length of rhs = lhs , set range to lhs.size()
    {
        range = lhs.size();
    }
    while (lhs.size() < rhs.size()) // if lhs < rhs add zeros to lhs for padding to simplify addition process
    {
        lhs.insert(0, "0");
        range = rhs.size();
    }
    while (rhs.size() < lhs.size()) // if rhs < lhs add zeros to rhs for padding to simplify addition process
    {
        rhs.insert(0, "0");
        range = lhs.size();
    }
    for (int i = 0; i < range; i++) //elementary addition calculations
    {
        lhs_int = digit_to_decimal(lhs.at(lhs.size() - i - 1)); //stores rightmost digit of LHS as int
        rhs_int = digit_to_decimal(rhs.at(rhs.size() - i - 1)); //stores rightmost digit of RHS as int
        sum_int = lhs_int + rhs_int + carry;
        column_sum = (sum_int % 10); //ones place
        Answer = decimal_to_digit(column_sum) + Answer;
        if (sum_int > 9)
            carry = sum_int / 10; //tens place
        else
            carry = 0;
    }
    if (carry == 1)
    {
        Answer = '1' + Answer;
    }

    return Answer;
}

string subtract(string lhs, string rhs)
{

    int borrow = 0;         // initalizes borrow value
    int range = 0;          // initalizes value that will tell us how many times for loop is going to loop
    string Answer = "";     // initalizes value that will hold the Answer as a string
    string lhs_no_neg = ""; // initalizes string for negative lhs with removed negative counterpart
    string rhs_no_neg = ""; // initalizes string for negative rhs with removed negative counterpart
    bool isNegative = false;
    if ((lhs.at(0) == '-') && (rhs.at(0) == '-')) // do when both lhs and rhs are negatives
    {
        rhs_no_neg = rhs.substr(1);
        lhs_no_neg = lhs.substr(1);
        Answer = subtract(rhs_no_neg, lhs_no_neg);
        return Answer;
    }
    else if ((lhs.at(0) == '-') && (digit_to_decimal(rhs.at(0)) != 0)) //when lhs - and rhs +
    {
        lhs_no_neg = lhs.substr(1);
        Answer = add(lhs_no_neg, rhs);
        return ('-' + Answer);
    }
    else if ((digit_to_decimal(lhs.at(0)) != 0) && (rhs.at(0) == '-')) // when lhs + and rhs -
    {
        rhs_no_neg = rhs.substr(1);
        Answer = add(lhs, rhs_no_neg);
        return Answer;
    }
    // swapping  lhs and rhs : if lhs is originally smaller than rhs.
    if (rhs.size() > lhs.size())
    {
        string temp = rhs;
        rhs = lhs;
        lhs = temp;
        isNegative = true;
    }
    else if (rhs.size() == lhs.size())
    {
        bool larger_rhs = false;
        for (long unsigned int i = 0; i < rhs.size(); i++)
        {
            if (digit_to_decimal(rhs.at(i)) > digit_to_decimal(lhs.at(i)))
            {
                larger_rhs = true;
                isNegative = true;
                break;
            }

            else if (digit_to_decimal(rhs.at(i)) < digit_to_decimal(lhs.at(i)))
            {
                larger_rhs = false;
                break;
            }
        }

        if (larger_rhs)
        {

            isNegative = true;
            string temp = rhs;
            rhs = lhs;
            lhs = temp;
        }
    }
    if (rhs.size() == lhs.size()) // if str length of rhs = lhs , set range to lhs.size()
    {
        range = lhs.size();
    }
    while (lhs.size() < rhs.size()) // if lhs < rhs add zeros to lhs for padding to simplify addition process
    {
        lhs.insert(0, "0");
        range = rhs.size();
    }
    while (rhs.size() < lhs.size()) // if rhs < lhs add zeros to rhs for padding to simplify subtraction process
    {
        rhs.insert(0, "0");
        range = lhs.size();
    }
    // doing the subtraction :
    int diff = 0;
    for (int i = range - 1; i >= 0; i--)
    {
        diff = digit_to_decimal(lhs.at(i)) - digit_to_decimal(rhs.at(i)) - borrow;
        if (diff < 0)
        {
            diff += 10;
            Answer = decimal_to_digit(diff) + Answer;
            borrow = 1;
        }
        else
        {
            borrow = 0;
            Answer = decimal_to_digit(diff) + Answer;
        }
    }
    if (isNegative == true)
    {
        return ('-' + trim_leading_zeros(Answer));
    }
    return (trim_leading_zeros(Answer));
}

string multiply(string lhs, string rhs)
{
    // TODO(student): implement
    int isNegative = false;
    // || ACCOUNTING FOR SIGNS ||
    if (rhs.at(0) == '-' && lhs.at(0) != '-')
    {
        isNegative = true;
        rhs = rhs.substr(1);
    }

    if (rhs.at(0) != '-' && lhs.at(0) == '-')
    {
        isNegative = true;
        lhs = lhs.substr(1);
    }

    if (rhs.at(0) == '-' && lhs.at(0) == '-')
    {
        rhs = rhs.substr(1);
        lhs = lhs.substr(1);
    }

    // || SWAPPING LHS AND RHS IF LHS IS ORIGINALLY SMALLER THAN RHS. ||
    // Why? (In case future me forgets) : bc its hella lengthy and difficult if i dont swap in the beginning.
    // Trynna simplify the process for you by swapping ahead of time ok boo :*
    if (rhs.size() > lhs.size())
    {
        string temp = rhs;
        rhs = lhs;
        lhs = temp;
    }

    int carry = 0;
    int mult = 0;
    string intermediate = "";
    string total = "0";
    int count = 0;
    for (int i = rhs.size() - 1; i >= 0; i--) //outer for loop : controls RHS
    {
        for (int j = lhs.size() - 1; j >= 0; j--) //inner for loop : controls LHS
        {

            mult = digit_to_decimal(lhs.at(j)) * digit_to_decimal(rhs.at(i)) + carry;

            // || TELLS US MULTIPLICATION RESULTS IN A CARRY ||
            if (mult > 9)
                carry = mult / 10;
            else
                carry = 0;

            // || LEFTMOST MULTIPLICATION CASE ||
            if (j == 0) // makes sure we account for carry of left most numbers of LHS * RHS multiplication
            {
                if (carry > 0) //if carry  > 0 then the left most numbers multiplication results in a carry
                {

                    intermediate = decimal_to_digit(mult % 10) + intermediate;
                    mult = mult / 10;
                    intermediate = decimal_to_digit(mult % 10) + intermediate; //accounts for carry
                }
                else // //if carry  = 0 then the left most numbers multiplication results in a carry
                {
                    intermediate = decimal_to_digit(mult % 10) + intermediate;
                }
            }
            else
                intermediate = decimal_to_digit(mult % 10) + intermediate;
        }
        // || used to account for placeholder 0s in long multiplication ||
        for (int x = 0; x < count; x++)
        {
            intermediate = intermediate + "0";
        }
        //increment counter : count
        count++;
        //carry needs to be reset every time we switch to a diff number on rhs.
        carry = 0;
        // || ADDING CURRENT INTERMEDIATE VALUE TO TOTAL||
        total = add(total, intermediate);
        // || REMOVING ALL VALUES IN INTERMEDIATE TO PREP FOR NEXT ITERATION ||
        intermediate = "";
    }

    if (carry == 1)
    {
        total = '1' + total;
    }

    if (isNegative == true)
    {
        return ("-" + trim_leading_zeros(total));
    }
    else
    {
        return trim_leading_zeros(total);
    }
}
