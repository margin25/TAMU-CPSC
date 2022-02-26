#ifndef UNSORTEDMPQ_H
#define UNSORTEDMPQ_H

#include <vector>
#include <stdexcept>
#include "MPQ.h"

/**
 * Minimum Priority Queue based on a vector
 */
template <typename T>
class UnsortedMPQ : MPQ<T>
{
   // Implement the four funtions (insert, is_empty, min, remove_min) from MPQ.h
   // To hold the elements use std::vector
   // For remove_min() and min() just throw exception if the UnsortedMPQ is empty. Mimir already has a try/catch block so don't use try/catch block here.
public:
   void insert(const T &value);
   bool is_empty();
   T min();
   T remove_min();

private:
   std::vector<T> mpq_vector;
};

// is_empty()
template <typename T>
bool UnsortedMPQ<T>::is_empty()
{
   if (mpq_vector.size() != 0)
      return false;
   return true;
}

// Insert
template <typename T>
void UnsortedMPQ<T>::insert(const T &value)
{
   mpq_vector.push_back(value);
}

// min
template <typename T>
T UnsortedMPQ<T>::min()
{
   if (is_empty() == true)
   {
      throw("exception thrown");
   }
   else
   {
      T min = mpq_vector.at(0);
      for (int x = 0; x < mpq_vector.size(); x++)
      {
         if (mpq_vector.at(x) < min)
            min = mpq_vector.at(x);
      }
      return min;
   }
}

// remove_min
template <typename T>
T UnsortedMPQ<T>::remove_min()
{
   int index = 0;
   T min = mpq_vector.at(0);
   if (is_empty() == true)
   {
      throw("exception thrown");
   }
   else
   {
      for (int x = 0; x < mpq_vector.size(); x++)
      {
         if (mpq_vector.at(x) < min)
         {
            index = x;              // acquires index of min
            min = mpq_vector.at(x); // acquires value of min
         }
      }
      mpq_vector.erase(mpq_vector.begin() + index);
      return (min);
   }
}

#endif