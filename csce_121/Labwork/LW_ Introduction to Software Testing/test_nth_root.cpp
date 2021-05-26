#include <iostream>
#include <cmath>
#include "./nth_root.h"

int main()
{
    { // MINIMUM REQUIREMENT (for this lab)
        // just call the function with various values of n and x
        //nth_root(2, 1);
        try
        {
            nth_root(0, 1); //n=0
            throw std::domain_error("Domain Error");
        }
        catch (std::domain_error &excpt)
        {
            std::cout << excpt.what() << std::endl;
            std::cout << "Domain Error" << std::endl;
        }
        try
        {
            nth_root(6, -15); //n is even and x is negative
            throw std::domain_error("Domain Error");
        }
        catch (std::domain_error &excpt)
        {
            std::cout << excpt.what() << std::endl;
            std::cout << "Domain Error" << std::endl;
        }
        try
        {
            nth_root(2, 0);
            throw std::domain_error("Domain Error");
        }
        catch (std::domain_error &excpt)
        {
            std::cout << excpt.what() << std::endl;
            std::cout << "Domain Error" << std::endl;
        }
        try
        {
            nth_root(-1, 0); ///n is negative and x = 0
            throw std::domain_error("Domain Error");
        }
        catch (std::domain_error &excpt)
        {
            std::cout << excpt.what() << std::endl;
            std::cout << "Domain Error" << std::endl;
        }
        //nth_root(0, 3);    // A
        //nth_root(6, -15);   // B
        //nth_root(2, 0);   // C
        nth_root(1, 5);   // D
        nth_root(-1, 4);  // E
        nth_root(-2, 3);  //F
        nth_root(-6, 20); //G
        nth_root(6, 20);  //H
        nth_root(6, 1);   //I
        nth_root(2, 2);   //J
        nth_root(3, 0);   //K
        nth_root(4, 1);   //L
        nth_root(3, -2);  //M
        nth_root(5, 3);   //N
        nth_root(2, 0.5); //O
        nth_root(2, 4);   //P
    }

    { // TRY HARD
        // report the value : nth_root(2, 1)
        //double actual = nth_root(2, 0);
        //std::cout << "nth_root(2, 0) = " << actual << std::endl;
    }

    /*     { // TRY HARDER
        //compare the actual value to the expected value
        double actual = nth_root(2, 1);
        double expected = 1;
        if (std::fabs(actual - expected) > 0.00005)
        {
            std::cout << "[FAIL] (n=2, x=1)" << std::endl;
            std::cout << "  expected nth_root(2, 1) to be " << expected << std::endl;
            std::cout << "  got " << actual << std::endl;
        }
        else
        {
            std::cout << "[PASS] (n=2, x=1)" << std::endl;
        }
    } */
}
