#ifndef BINARYHEAP_MPQ_H
#define BINARYHEAP_MPQ_H

#include "BinaryHeap.h"
#include <stdexcept>
#include "MPQ.h"

/*
 * Minimum Priority Queue based on a binary heap
 */
template <typename T>
class BinaryHeapMPQ : MPQ<T>
{
   // Implement the four funtions (insert, is_empty, min, remove_min) from MPQ.h
   // It is enough if the 4 methods in  BinaryHeapMPQ calls the corresponding implemented methods in BinaryHeap.h.
   // To hold the elements use BinaryHeap (from BinaryHeap.h)
   // For remove_min() and min() throw exception if the BinaryHeapMPQ is empty. Mimir already has a try/catch block so don't use try/catch block here.
public:
   T min();
   T remove_min();
   void insert(const T &data);
   bool is_empty();

private:
   BinaryHeap<T> final_BinaryHeap;
};

template <typename T>
T BinaryHeapMPQ<T>::min()
{
   return (final_BinaryHeap.min());
}

template <typename T>
T BinaryHeapMPQ<T>::remove_min()
{
   return (final_BinaryHeap.remove_min());
}

template <typename T>
void BinaryHeapMPQ<T>::insert(const T &data)
{
   final_BinaryHeap.insert(data);
}

template <typename T>
bool BinaryHeapMPQ<T>::is_empty()
{
   return (final_BinaryHeap.is_empty());
}

#endif