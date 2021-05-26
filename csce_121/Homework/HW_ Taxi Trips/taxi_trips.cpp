#include <stdexcept>
#include <string>
using std::string;
#include "taxi_trips.h"

bool is_payment_valid(string type, string valid_types[], unsigned int size)
{
  /*
  returns true if type is one of the type values in array valid_types
  input:  type - string with payment type that we are checking for validity
          valid_types - array of strings listing the valid types
          size - the number of elements in array valid_types
  output: returns true if string type appears in array valid_types and
          false otherwise
          if size is zero, it throws std::invalid_argument
  */
  // TODO(student): implement
  if (size == 0) // if theres nothing to evaluate this whole process is invalid so throw error
  {
    throw std::invalid_argument("invalid argument");
  }
  bool value = false; // initializing to false bc the if statement in the for loop is checking to see if its true
  for (unsigned int i = 0; i < size; i++)
  {
    if (valid_types[i] == type) //true if index type is one of the type values in array valid_types
      value = true;
  }
  return value; //returns boolean value that tells us if payment is valid or not
}

double max(double values[], unsigned int size) //
{
  /*
  returns the max number in an array
  input: values  - an array of double non-negative numbers
        size - the number of elements in the array
  output: the largest number that appears in the array.
          if size is zero, it throws std::invalid_argument
  */
  // TODO(student): implement
  if (size == 0) //stupid person would only try this
  {
    throw std::invalid_argument("invalid argument");
  }
  double max = values[0]; //initalize to first number in the array bc we are gonna compare it with other indices later
  for (unsigned int i = 0; i < size; i++)
  {
    if (values[i] > max) //if current number @ index is bigger than the original max then assign value at index to max
      max = values[i];
  }

  return max; //duhhhh
}

double min(double values[], unsigned int size) //similar logic to max
{
  /*
  returns the min number in an array
  input: values  - an array of double non-negative numbers
        size - the number of elements in the array
  output: the smallest number that appears in the array.
          if size is zero, it throws std::invalid_argument
  */
  // TODO(student): implement
  if (size == 0)
  {
    throw std::invalid_argument("invalid argument");
  }
  double min = values[0];
  for (unsigned int i = 0; i < size; i++)
  {
    if (values[i] < min) //if current number @ index is smaller  than the original min then assign value at index to min
      min = values[i];
  }

  return min;
}

double average(double values[], unsigned int size)
{
  /*
  returns the average of the numbers in an array
  input: values  - an array of double non-negative numbers
        size - the number of elements in the array
  output: the average of the numbers in the array.
          if size is zero, it throws std::invalid_argument 
  */
  // TODO(student): implement
  double sum = 0; // initalize variable that holds sum
  if (size == 0)  //dumb
  {
    throw std::invalid_argument("invalid argument");
  }
  for (unsigned int i = 0; i < size; i++)
  {
    sum += (values[i]); //sum up all the values in the indices
  }
  return (sum / size); // avg = sum/size so logic
}

double mode(double values[], unsigned int size)
{
  /*
  returns the mode of the numbers in the array. If there are
  multiple values for mode (i.e., multiple occur most frequently),
  the function returns the first of them.

  input: values  - an array of double non-negative numbers
        size - the number of elements in the array
  output: the mode of the numbers in the array
          if size is zero, it throws std::invalid_argument 
  */
  // TODO(student): implement
  double highest_freq = 0.0;
  double current_index_occurences = 0.0; //
  if (size == 0)                         //same
  {
    throw std::invalid_argument("invalid argument");
  }
  for (unsigned int index = 0; index < size; index++) //two for loops are needed bc the outer loop stays constant while we cycle through the different indices in the inner loop
  //this allows us to check all values of the array and in turn find the mode
  {
    double count = 0; // counts how many times that number appears in the array
    for (unsigned int i = 0; i < size; i++)
    {
      if (values[index] == values[i]) //outer loop value(current index being checked) = inner loop value
      {
        count++; //increment count
      }
      if (current_index_occurences < count)
      {
        current_index_occurences = count; //basically if current number occurs less then count then set current_index_occurences to count so that u can compare to the biggest occurences next.
        highest_freq = values[i];         // basically holds the value of the number with the highest frequency
      }
    }
  }
  return highest_freq;
}

unsigned int length_longest_seq_zeros(double values[], unsigned int size)
{
  /*
  returns the length of the longest sequence of zeroes in the array
  input: values  - an array of double non-negative numbers
        size - the number of elements in the array
  output: the length of the longest zero sequence in the array
          if size is zero, it throws std::invalid_argument 
  */
  // TODO(student): implement
  int longest_zero = 0;
  int current_zero = 0;
  if (size == 0)
  {
    throw std::invalid_argument("Invalid Argument");
  }
  for (unsigned int i = 0; i < size; i++)
  {
    if (values[i] == 0) // if value at index  is 0
    {
      current_zero += 1; //then increment current zero
    }
    else //if not
    {
      current_zero = 0; //set current zero to 0 bc there is no longer a sequence of zeroes
    }
    if (current_zero > longest_zero) // if current_zero is greater than longest zero
    {
      longest_zero = current_zero; // then set them equal bc current_zero should now be the longest
    }
  }
  return (longest_zero); // return lonngest sequence of zeroes tadaaah!
}