#include <iostream>
#include "cstring.h"

unsigned int length(char str[])
{
  int count = 0;
  for (int i = 0; str[i] != '\0'; i++)
  {
    count++;
  }
  // returns the length of the string including zero (0)
  return count;
}

unsigned int find(char str[], char character)
{
  // returns
  //  - the index of the first occurence of character in str
  //  - the size if the character is not found
  int length = 0;

  for (int i = 0; str[i] != '\0'; i++)
  {

    if ((str[i] == character))
    {
      return (length);
    }
    length++;
  }
  return length;
}

bool equalStr(char str1[], char str2[])
{
  int count = 0;
  int length = 0;
  int max_length = 0;
  // returns true if they are equal and false if they are not
  for (int i = 0; str2[i] != '\0'; i++)
  {
    if (str1[i] == str2[i])
    {
      count++;
    }
    length++;
  }
  if (count == length)
    return true;
  return false;
}