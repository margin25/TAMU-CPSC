/**
 * There is no Collection.cpp for this assignment.
 * Move all the functions from Collection.cpp to this file except Operator>> 
 * Covert the Collection class to a templated form. (Obj should be replaced with typename "Obj".
 *   Stress_ball_colors and Stress_ball_sizes should be replaced with typename "F2").
 * This file has to be uploaded to mimir.
 */

#ifndef Collection_H
#define Collection_H
#include <string>
#include <iostream>
using namespace std;

enum class Sort_choice
{
    bubble_sort,
    insertion_sort,
    selection_sort
};

template <typename Obj, typename F1, typename F2>
class Collection
{
    Obj *array;
    int size;
    int capacity;
    void resize()
    {
        if (capacity == 0)
        {
            array = new Obj();
            size = 0;
            capacity = 1;
        }
        capacity = 2 * capacity;
        Obj *temporary = new Obj[capacity];
        for (int x = 0; x < size; x++)
        {
            temporary[x] = array[x]; //copy over values in array
        }
        delete[] array; // deallocate memory
        array = temporary;
        temporary = nullptr;
    }

public:
    // constructor with no arguments
    // size and capacity are 0, and array is nullptr
    Collection()
    {
        capacity = 0;
        size = 0;
        array = nullptr;
    }
    // constructor with one argument which is the required capacity of the collection.
    // The array should also be allocated memory equal to the capacity if this constructor is used.
    Collection(int cap)
    {

        capacity = cap;
        size = 0;
        array = new Obj[capacity];
    }
    // copy constructor – makes a copy of a collection.
    Collection(const Collection &c)
    {
        capacity = c.capacity;
        size = c.size;
        array = new Obj[capacity];
        for (int x = 0; x < size; x++)
        {
            array[x] = c.array[x];
        }
    }

    // move constructor – efficiently creates a new collection from an existing one
    Collection(Collection &&c)
    {
        size = c.size;
        capacity = c.capacity;
        array = c.array;
        c.size = 0;
        c.capacity = 0;
        c.array = nullptr;
    }

    // copy assignment – overwrites an exiting collection by another collection
    Collection &operator=(const Collection &c)
    {
        if (this != &c)
        {
            if (array != nullptr)
                delete[] array; // deallocate memory
            capacity = c.capacity;
            size = c.size;
            array = new Obj[capacity]; // allocate memory to array
            for (int x = 0; x < size; x++)
            {
                array[x] = c.array[x];
            }
        }
        return *this;
    }

    // move assignment – efficiently copies a collection during an assignment
    Collection &operator=(Collection &&c)
    {
        capacity = c.capacity;
        array = c.array;
        size = c.size;
        c.capacity = 0;
        c.array = nullptr;
        c.size = 0;
        return *this;
    }

    //destructor – destroys a collection (deallocates allocated memory, set to zero size and capacity)
    ~Collection()
    {
        make_empty();
    }

    //  check if the collection is empty; return true if it is empty and false otherwise:
    void make_empty()
    {
        if (array != nullptr)
        {
            capacity = 0;
            size = 0;
            delete[] array; // deallocate array
            array = nullptr;
        }
    }

    //  make the collection empty (deallocate allocated memory, set to zero size and capacity)
    bool is_empty() const
    {
        return size == 0;
    }

    // insert a stress ball to the collection:
    // If the collection is full, increase the array by doubling its capacity. Use the private helper
    // function resize() to complete this task. The function resize() should double the capacity
    // of the array and correctly copy elements from the old array to a new array.
    void insert_item(const Obj &sb)
    {
        if (size >= capacity)
            resize();
        array[size++] = sb; // inserting item
                            // incrementing size to compensate for the insertions
    }

    // total_items() : return the total number of stress balls in the collection : int total_items() const;
    int total_items() const
    {
        return size;
    }

    int total_items(F2 s) const
    {
        int counter = 0;
        for (int x = 0; x < size; x++)
        {
            if (array[x].get_size() == s)
            {
                counter++;
            }
        }
        return counter;
    }
    int total_items(F1 c) const
    {
        int counter = 0;
        for (int x = 0; x < size; x++)
        {
            if (array[x].get_color() == c)
            {
                counter++;
            }
        }
        return counter;
    }

    void print_items() const
    {
        cout << *this; //
    }

    // To directly access a stress ball in a collection, overload operator[]. It will access a stress ball in
    // array at position i where i starts from 0 through size-1:
    Obj &operator[](int i)
    {
        return array[i];
    }

    const Obj &operator[](int i) const
    {
        return array[i];
    }

    // check if a stress ball of a given color and size is in the collection; return true if it is there and
    // false otherwise.
    bool contains(const Obj &sb) const
    {
        for (int x = 0; x < size; x++)
        {
            if (array[x] == sb)
                return true;
        }
        return false;
    }

    // remove and return a random stress ball (you have no control which stress ball is selected):
    Obj remove_any_item()
    {
        if (size == 0)
        {
            throw("error");
        }
        int random_index = std::rand() % size;
        Obj random_ball = array[random_index];
        Obj *array2 = new Obj[capacity];
        int y = 0;
        for (int x = 0; x < size; x++)
        {
            if (x != random_index)
            {
                array2[y] = array[x];
                y++;
            }
        }
        size = size - 1;
        delete[] array;
        array = array2;
        array2 = nullptr;
        return random_ball;
    }

    // remove a stress ball with a specific color and size from the collection
    void remove_this_item(const Obj &sb)
    {
        if (size == 0)
        {
            throw("error");
        }
        for (int index = 0; index < size; index++)
        {
            if (array[index] == sb)
            {
                Obj *stress = new Obj[capacity];
                int j = 0;
                for (int i = 0; i < size; i++)
                {
                    if (i != index)
                    {
                        stress[j] = array[i];
                        j++;
                    }
                }
                size = size - 1;
                delete[] array;
                array = stress;
                stress = nullptr;
            }
        }
    }

    // istream& operator>‌>(istream& is, Collection& c);
    // reads from the istream is pairs in this format: color size (no parentheses or colons, use space
    // to separate them). As colors use strings (you can use STL class string here): red, blue, yellow,
    // green, and as sizes use strings: small, medium, large. Data is read from an input file in main.cpp
    // and it is passed to istream is
};

template <typename Obj, typename F1, typename F2>
ostream &operator<<(ostream &os, const Collection<Obj, F1, F2> &c)
{
    for (int i = 0; i < c.total_items(); i++)
    {
        os << c[i] << endl;
    }
    return os;
}

// a union operation that combines the contents of two collections into a third collection
// (the contents of c1 and c2 are not changed):
template <typename Obj, typename F1, typename F2>
Collection<Obj, F1, F2> make_union(const Collection<Obj, F1, F2> &c1, const Collection<Obj, F1, F2> &c2)
{
    Collection<Obj, F1, F2> newCollection(c1.total_items() + c2.total_items());
    for (int x = 0; x < c1.total_items(); x++)
    {
        newCollection.insert_item(c1[x]);
    }
    for (int x = 0; x < c2.total_items(); x++)
    {
        newCollection.insert_item(c2[x]);
    }
    return newCollection;
}

template <typename Obj, typename F1, typename F2>
void swap(Collection<Obj, F1, F2> &c1, Collection<Obj, F1, F2> &c2)
{
    Collection<Obj, F1, F2> temp = move(c1);
    c1 = move(c2);
    c2 = move(temp);
}
template <typename Obj, typename F1, typename F2>
void sort_by_size(Collection<Obj, F1, F2> &c, Sort_choice sort)
{
    bool swap = true;
    if (true)
    {
        while (swap)
        {
            swap = false;
            for (int x = 0; x < c.total_items() - 1; x++)
            {
                if (c[x + 1].get_size() < c[x].get_size())
                {
                    Obj temp = c[x];
                    c[x] = c[x + 1]; //swapping
                    c[x + 1] = temp;
                    swap = true;
                }
            }
        }
    }
}
//your code...
//Templated class collection
//Methods from Collection.cpp
#endif