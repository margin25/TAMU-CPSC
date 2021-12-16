#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <stdexcept>
#include <iostream>
#include <vector>
#include <math.h>

/*
 * Binary Heap class
 */
template <typename T>
class BinaryHeap
{
public:
    //Implement the below 4 methods. Please note these methods are not from MPQ.h
    //BinaryHeap class does not inherit MPQ class
    //Implement BinaryHeap insert operation
    //Also implement upheap and downheap operations (functions provided below) and call them from wherever necessary
    void insert(const T &data);
    // Return true if BinaryHeap is empty otherwise false
    bool is_empty();
    // Return minimum element in the BinaryHeap
    T min();
    // Remove minimum element in the BinaryHeap and return it
    T remove_min();

private:
    //
    std::vector<T> elements;
    int size = 0;
    //Implement down heap operation
    void down_heap(int i);
    //Implement up heap operation
    void up_heap(int i);

    //Pre-implemented helper functions
    //swaps two elements at positions a and b
    void swap(int a, int b)
    {
        T c(elements[a]);
        elements[a] = elements[b];
        elements[b] = c;
    }
    //Binary tree (Complete Binary tree) can be represented in vector form and hence, stored in a vector.
    //Returns the right child index of current index
    int right_child(int i) { return 2 * i + 2; }
    //Returns the left child index of current index
    int left_child(int i) { return 2 * i + 1; }
    //Returns the parent index of current index
    int parent(int i) { return floor((i - 1) / 2); }
    //Checks if current index is an internal node
    bool is_internal(int i) { return left_child(i) < size || right_child(i) < size; }
    //Checks if current index is a leaf
    bool is_leaf(int i) { return left_child(i) >= size && right_child(i) >= size; }
};

/*
 * Restores the binary heap property starting from a node that is smaller than its parent
 */
template <typename T>
void BinaryHeap<T>::up_heap(int i)
{
    int parent_index = parent(i);
    /*
     * Can be computed iteratively or recursively
     */
    while (0 < i && elements[i] < elements[parent(i)])
    {
        swap(i, parent(i));
        // now i is parent
        i = parent(i);
    }
}

/*
 * Restores the binary heap property starting from an node that is larger than its children
 */
template <typename T>
void BinaryHeap<T>::down_heap(int i)
{
    int curr_index = i;
    int right_index = right_child(i);
    int left_index = left_child(i);
    /*
     * Can be computed iteratively or recursively
     */
    // left
    if (elements[left_index] < elements[curr_index] && left_index < size)
    {
        curr_index = left_index;
    }
    // right
    if (elements[right_index] < elements[curr_index] && right_index < size)
    {
        curr_index = right_index;
    }
    //
    if (i != curr_index)
    {
        swap(curr_index, i);
        down_heap(curr_index);
    }
}

// empty
template <typename T>
bool BinaryHeap<T>::is_empty()
{
    if (size != 0)
        return false;
    return true;
}

// min
template <typename T>
T BinaryHeap<T>::min()
{
    if (is_empty() == true)
    {
        throw("Exception thrown");
    }
    else
    {
        T minimum = elements[0];
        return minimum;
    }
}

// remove_min
template <typename T>
T BinaryHeap<T>::remove_min()
{
    if (is_empty() == true)
    {
        throw("Exception thrown");
    }
    else
    {
        T min = elements[0];
        int len = --size;
        elements[0] = elements[len];
        elements.erase(--elements.end());
        down_heap(0);
        return min;
    }
}

// insert
template <typename T>
void BinaryHeap<T>::insert(const T &data)
{
    size++;
    int n_size = size - 1;
    elements.push_back(data);
    up_heap(n_size);
}

#endif