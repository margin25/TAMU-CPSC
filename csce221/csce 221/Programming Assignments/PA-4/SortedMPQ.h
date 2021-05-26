#ifndef SORTEDMPQ_H
#define SORTEDMPQ_H

#include <stdexcept>
#include <list>
#include "MPQ.h"
#include <vector>
#include <iostream>

/*
 * Minimum Priority Queue based on a linked list
 */
template <typename T>
class SortedMPQ : MPQ<T>
{
   // Implement the four funtions (insert, is_empty, min, remove_min) from MPQ.h
   // To hold the elements use std::list
   // For remove_min() and min() throw exception if the SortedMPQ is empty. Mimir already has a try/catch block so don't use try/catch block here.
public:
   bool is_empty();
   void insert(const T &value);
   T min();
   T remove_min();

private:
   std::list<T> mpq_vector;
};

// is_empty()
template <typename T>
bool SortedMPQ<T>::is_empty()
{
   if (mpq_vector.size() != 0)
      return false;
   return true;
}

// insert()
template <typename T>
void SortedMPQ<T>::insert(const T &value)
{
   typename std::list<T>::iterator x;
   if (mpq_vector.size() == 0)
   {
      mpq_vector.push_front(value);
      return;
   }
   else
   {

      for (x = mpq_vector.begin(); x != mpq_vector.end(); x++)
      {
         if (value < *x)
         {
            mpq_vector.insert(x, value);
            return;
         }
      }

      mpq_vector.push_back(value);
      return;
   }
}
// min()
template <typename T>
T SortedMPQ<T>::min()
{
   if (is_empty() == true)
   {
      throw("Exception Thrown");
   }
   return mpq_vector.front();
}

// remove_min()
template <typename T>
T SortedMPQ<T>::remove_min()
{
   if (is_empty() == true)
   {
      throw("Exception Thrown");
   }
   T minimum = min();
   mpq_vector.pop_front();
   return (minimum);
}

#endif