/*  QUESTION
Numeric Sequence Analysis
Write a complete C++ program. Read from standard input (std::cin) a sequence of integers
that is terminated by the integer zero (0). Print the minimum, maximum, and average of the
positive even values in the sequence (not counting the terminating zero).
Examples
1. Input: -8 6 -7 5 -3 1 2 -4 0
Output: min 2 max 6 average 4
2. Input: 1 -2 3 -4 5 0
Output: no values
*/
#include <iostream>

using std::cin, std::cout, std::endl;

int main()

{
    //convert string to int

    // ask user for input
    //cout << "enter values:" << endl;
    //cin >> ;

    //traverse (loop through string until we reach 0) and find even integers , (initialize array )put even integers in array
    //stop traversing when we hit "/n"

    //DEFINE FUNCTION COMPUTE MIN: int find_min(int arr[])
    //compute min
    /* double min = values[0];
  for (unsigned int i = 0; i < size; i++)
  {
    if (arr[i] < min) //if current number @ index is smaller  than the original min then assign value at index to min
      min = arr[i];
  }
  return min;
}*/
    //DEFINE FUNCTION COMPUTE MAX: int find_max(int arr[])
    //compute max
    /* double max = values[0]; //initalize to first number in the array bc we are gonna compare it with other indices later
  for (unsigned int i = 0; i < size; i++)
  {
    if (arr[i] > max) //if current number @ index is bigger than the original max then assign value at index to max
      max = arr[i];
  }
  return max;*/

    // compute avg
    //DEFINE FUNCTION COMPUTE MAX: int find_avg(int arr[])
    /*
     double sum = 0; // initalize variable that holds sum
  if (size == 0)  //dumb
  {
    throw std::invalid_argument("invalid argument");
  }
  for (unsigned int i = 0; i < size; i++)
  {
    sum += (arr[i]); //sum up all the values in the indices
  }
  return (sum / size); // avg = sum/size so logic
}
    */
    //terminate when 0
    return (0);

    //have another function that prints all these values
}
