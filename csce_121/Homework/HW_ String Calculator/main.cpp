#include <iostream>
#include <string>
#include <limits>
#include "./string_calculator.h"

using std::cout, std::endl, std::cin;
using std::string;

int main()
{

    cout << "String Calculator" << endl;
    /* cout << add("0", "0") << endl;
    cout << add("0", "1") << endl;
    cout << add("0", "2") << endl;
    cout << add("0", "3") << endl;
    cout << add("0", "4") << endl;
    cout << add("0", "5") << endl;
    cout << add("0", "6") << endl;
    cout << add("0", "7") << endl;
    cout << add("0", "8") << endl;
    cout << add("0", "9") << endl;
    cout << add("1", "1") << endl;
    cout << add("1", "2") << endl;
    cout << add("1", "3") << endl;
    cout << add("1", "4") << endl;
    cout << add("1", "5") << endl;
    cout << add("1", "6") << endl;
    cout << add("1", "7") << endl;
    cout << add("1", "8") << endl;
    cout << add("1", "9") << endl;
    cout << add("2", "2") << endl;
    cout << add("2", "3") << endl;
    cout << add("2", "4") << endl;
    cout << add("2", "5") << endl;
    cout << add("2", "6") << endl;
    cout << add("2", "7") << endl;
    cout << add("2", "8") << endl;
    cout << add("2", "9") << endl;
    cout << add("3", "3") << endl;
    cout << add("3", "4") << endl;
    cout << add("3", "5") << endl;
    cout << add("3", "6") << endl;
    cout << add("3", "7") << endl;
    cout << add("3", "8") << endl;
    cout << add("3", "9") << endl;
    cout << add("4", "4") << endl;
    cout << add("4", "5") << endl;
    cout << add("4", "6") << endl;
    cout << add("4", "7") << endl;
    cout << add("4", "8") << endl;
    cout << add("4", "9") << endl;
    cout << add("5", "5") << endl;
    cout << add("5", "6") << endl;
    cout << add("5", "7") << endl;
    cout << add("5", "8") << endl;
    cout << add("5", "9") << endl;
    cout << add("6", "6") << endl;
    cout << add("6", "7") << endl;
    cout << add("6", "8") << endl;
    cout << add("6", "9") << endl;
    cout << add("7", "7") << endl;
    cout << add("7", "8") << endl;
    cout << add("7", "9") << endl;
    cout << add("8", "8") << endl;
    cout << add("8", "9") << endl;
    cout << add("9", "9") << endl;
    cout << add("99", "1") << endl;
    cout << add("1", "999") << endl;
    cout << add("867", "5309") << endl;
    cout << add("123", "456") << endl;
    cout << add("7654", "2346") << endl;
    cout << add("56678", "66778") << endl;
    cout << add("1234567890", "9876543210") << endl;
    cout << add("0", "125416") << endl;
    cout << add("-1", "-1") << endl;
    cout << add("-1", "-2") << endl;
    cout << add("-1", "-3") << endl;
    cout << add("-1", "-4") << endl;
    cout << add("-1", "-5") << endl;
    cout << add("-1", "-6") << endl;
    cout << add("-1", "-7") << endl;
    cout << add("-1", "-8") << endl;
    cout << add("-1", "-9") << endl;
    cout << add("-2", "-2") << endl;
    cout << add("-2", "-3") << endl;
    cout << add("-2", "-4") << endl;
    cout << add("-2", "-5") << endl;
    cout << add("-2", "-6") << endl;
    cout << add("-2", "-7") << endl;
    cout << add("-2", "-8") << endl;
    cout << add("-2", "-9") << endl;
    cout << add("-3", "-3") << endl;
    cout << add("-3", "-4") << endl;
    cout << add("-3", "-5") << endl;
    cout << add("-3", "-6") << endl;
    cout << add("-3", "-7") << endl;
    cout << add("-3", "-8") << endl;
    cout << add("-3", "-9") << endl;
    cout << add("-4", "-4") << endl;
    cout << add("-4", "-5") << endl;
    cout << add("-4", "-6") << endl;
    cout << add("-4", "-7") << endl;
    cout << add("-4", "-8") << endl;
    cout << add("-4", "-9") << endl;
    cout << add("-5", "-5") << endl;
    cout << add("-5", "-6") << endl;
    cout << add("-5", "-7") << endl;
    cout << add("-5", "-8") << endl;
    cout << add("-5", "-9") << endl;
    cout << add("-6", "-6") << endl;
    cout << add("-6", "-7") << endl;
    cout << add("-6", "-8") << endl;
    cout << add("-6", "-9") << endl;
    cout << add("-7", "-7") << endl;
    cout << add("-7", "-8") << endl;
    cout << add("-7", "-9") << endl;
    cout << add("-8", "-8") << endl;
    cout << add("-8", "-9") << endl;
    cout << add("-9", "-9") << endl;
    cout << add("-99", "-1") << endl;
    cout << add("-1", "-999") << endl;
    cout << add("-867", "-5309") << endl;
    cout << add("-123", "-456") << endl;
    cout << add("-7654", "-2346") << endl;
    cout << add("-56678", "-66778") << endl;
    cout << add("-1234567890", "-9876543210") << endl;
    cout << add("7", "-4") << endl; */
    /* cout << subtract("3", "2") << endl;
    cout << subtract("7", "7") << endl;
    cout << subtract("199", "59") << endl;
    cout << subtract("248", "120") << endl;
    cout << subtract("455", "320") << endl;
    cout << subtract("544", "352") << endl;
    cout << subtract("801", "109") << endl;
    cout << subtract("1154", "536") << endl;
    cout << subtract("1394", "455") << endl;
    cout << subtract("1275", "11") << endl;
    cout << subtract("991", "979") << endl; */

    /*
    cout << subtract("37", "39") << endl;
    cout << subtract("146", "149") << endl;
    cout << subtract("388", "575") << endl;
    cout << subtract("172", "563") << endl;
    cout << subtract("338", "429") << endl;
    cout << subtract("800", "1015") << endl; 
    cout << subtract("186", "350") << endl;
    cout << subtract("21", "708") << endl;   
    cout << subtract("491", "1552") << endl; */

    /* cout << subtract("-170", "-294") << endl;
    cout << subtract("-76", "-829") << endl;
    cout << subtract("-342", "-940") << endl;
    cout << subtract("-479", "-729") << endl;
    cout << subtract("-861", "-1208") << endl;
    cout << subtract("-867", "-867") << endl; */

    /* // subtract (small, negatives, nonnegative result)
    cout << subtract("-170", "-294") << endl;
    cout << subtract("-76", "-829") << endl;
    cout << subtract("-342", "-940") << endl;
    cout << subtract("-479", "-729") << endl;
    cout << subtract("-861", "-1208") << endl;
    cout << subtract("-867", "-867") << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl; */

    //subtract (small, opposite signs)
    /* cout << subtract("1", "-1") << endl;
    cout << subtract("1", "-2") << endl;
    cout << subtract("1", "-3") << endl;
    cout << subtract("1", "-4") << endl;
    cout << subtract("1", "-5") << endl;
    cout << subtract("1", "-6") << endl;
    cout << subtract("1", "-7") << endl;
    cout << subtract("1", "-8") << endl;
    cout << subtract("1", "-9") << endl;
    cout << subtract("2", "-2") << endl;
    cout << subtract("2", "-3") << endl;
    cout << subtract("2", "-4") << endl;
    cout << subtract("2", "-5") << endl;
    cout << subtract("2", "-6") << endl;
    cout << subtract("2", "-7") << endl;
    cout << subtract("2", "-8") << endl;
    cout << subtract("2", "-9") << endl;
    cout << subtract("3", "-3") << endl;
    cout << subtract("3", "-4") << endl;
    cout << subtract("3", "-5") << endl;
    cout << subtract("3", "-6") << endl;
    cout << subtract("3", "-7") << endl;
    cout << subtract("3", "-8") << endl;
    cout << subtract("3", "-9") << endl;
    cout << subtract("4", "-4") << endl;
    cout << subtract("4", "-5") << endl;
    cout << subtract("4", "-6") << endl;
    cout << subtract("4", "-7") << endl;
    cout << subtract("4", "-8") << endl;
    cout << subtract("4", "-9") << endl; */
    /*
    cout << subtract("-5", "5") << endl;
    cout << subtract("-5", "6") << endl;
    cout << subtract("-5", "7") << endl;
    cout << subtract("-5", "8") << endl;
    cout << subtract("-5", "9") << endl;
    cout << subtract("-6", "6") << endl;
    cout << subtract("-6", "7") << endl;
    cout << subtract("-6", "8") << endl;
    cout << subtract("-6", "9") << endl;
    cout << subtract("-7", "7") << endl;
    cout << subtract("-7", "8") << endl;
    cout << subtract("-7", "9") << endl;
    cout << subtract("-8", "8") << endl;
    cout << subtract("-8", "9") << endl;
    cout << subtract("-9", "9") << endl;
    cout << subtract("-321", "654") << endl;
    cout << subtract("7", "-9993") << endl; */

    /* cout << add("7", "-4") << endl;
    cout << add("40", "-1") << endl;
    cout << add("375", "-301") << endl;
    cout << add("522", "-126") << endl;
    cout << add("748", "-661") << endl; */
    /*
    cout << add("-2", "2") << endl;
    cout << add("-127", "128") << endl;
    cout << add("-105", "218") << endl;
    cout << add("-199", "397") << endl;
    cout << add("-31", "371") << endl;
    cout << add("-569", "600") << endl;
    cout << add("-276", "643") << endl; 
    */
    /* cout << multiply("4", "2") << endl;
    cout << multiply("6", "7") << endl;
    cout << multiply("18", "51") << endl;
    cout << multiply("2", "73") << endl;
    cout << multiply("15", "29") << endl;
    cout << multiply("138", "3") << endl;
    cout << multiply("133", "193") << endl; */

    // TODO(student): implement the UI
}
