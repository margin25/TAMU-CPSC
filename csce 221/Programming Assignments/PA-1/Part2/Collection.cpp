#include "Collection.h"
#include "Stress_ball.h"
#include <exception>
#include <cstdlib>
using namespace std;

// Use the private helper function resize() to complete this task.
// TODO : The function resize() should double the capacity of the array and correctly copy elements from the old array to a new array.
void Collection::resize()
{
    if (capacity == 0)
    {
        array = new Stress_ball();
        size = 0;
        capacity = 1;
    }
    capacity = 2 * capacity;
    Stress_ball *temporary = new Stress_ball[capacity];
    for (int x = 0; x < size; x++)
    {
        temporary[x] = array[x]; //copy over values in array
    }
    delete[] array; // deallocate memory
    array = temporary;
    temporary = nullptr;
}

// constructor with no arguments
// size and capacity are 0, and array is nullptr
Collection::Collection()
{
    capacity = 0;
    size = 0;
    array = nullptr;
}
// constructor with one argument which is the required capacity of the collection.
// The array should also be allocated memory equal to the capacity if this constructor is used.
Collection::Collection(int cap)
{

    capacity = cap;
    size = 0;
    array = new Stress_ball[capacity];
}
// copy constructor – makes a copy of a collection.
Collection::Collection(const Collection &c)
{
    capacity = c.capacity;
    size = c.size;
    array = new Stress_ball[capacity];
    for (int x = 0; x < size; x++)
    {
        array[x] = c.array[x];
    }
}

// move constructor – efficiently creates a new collection from an existing one
Collection::Collection(Collection &&c)
{
    size = c.size;
    capacity = c.capacity;
    array = c.array;
    c.size = 0;
    c.capacity = 0;
    c.array = nullptr;
}

// copy assignment – overwrites an exiting collection by another collection
Collection &Collection::operator=(const Collection &c)
{
    if (this != &c)
    {
        if (array != nullptr)
            delete[] array; // deallocate memory
        capacity = c.capacity;
        size = c.size;
        array = new Stress_ball[capacity]; // allocate memory to array
        for (int x = 0; x < size; x++)
        {
            array[x] = c.array[x];
        }
    }
    return *this;
}

// move assignment – efficiently copies a collection during an assignment
Collection &Collection::operator=(Collection &&c)
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
Collection::~Collection()
{
    make_empty();
}

//  check if the collection is empty; return true if it is empty and false otherwise:
void Collection::make_empty()
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
bool Collection::is_empty() const
{
    return size == 0;
}

// insert a stress ball to the collection:
// If the collection is full, increase the array by doubling its capacity. Use the private helper
// function resize() to complete this task. The function resize() should double the capacity
// of the array and correctly copy elements from the old array to a new array.
void Collection::insert_item(const Stress_ball &sb)
{
    if (size >= capacity)
        resize();
    array[size++] = sb; // inserting item
                        // incrementing size to compensate for the insertions
}

// total_items() : return the total number of stress balls in the collection : int total_items() const;
int Collection::total_items() const
{
    return size;
}

int Collection::total_items(Stress_ball_sizes s) const
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
int Collection::total_items(Stress_ball_colors c) const
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

void Collection::print_items() const
{
    string string_color = "";
    string string_size = "";
    for (int x = 0; x < size; x++)
    {

        switch (array[x].get_size())
        {
        case Stress_ball_sizes::small:
            string_size = "small";
            break;
        case Stress_ball_sizes::medium:
            string_size = "medium";
            break;
        case Stress_ball_sizes::large:
            string_size = "large";
            break;
        }

        switch (array[x].get_color())
        {
        case Stress_ball_colors::red:
            string_color = "red";
            break;
        case Stress_ball_colors::blue:
            string_color = "blue";
            break;
        case Stress_ball_colors::green:
            string_color = "green";
            break;
        case Stress_ball_colors::yellow:
            string_color = "yellow";
            break;
        }
        std::cout << "(" << string_color << ", " << string_size << ")\n";
    }
}

// To directly access a stress ball in a collection, overload operator[]. It will access a stress ball in
// array at position i where i starts from 0 through size-1:
Stress_ball &Collection::operator[](int i)
{
    return array[i];
}

const Stress_ball &Collection::operator[](int i) const
{
    return array[i];
}

// check if a stress ball of a given color and size is in the collection; return true if it is there and
// false otherwise.
bool Collection::contains(const Stress_ball &sb) const
{
    for (int x = 0; x < size; x++)
    {
        if (array[x] == sb)
            return true;
    }
    return false;
}

// remove and return a random stress ball (you have no control which stress ball is selected):
Stress_ball Collection::remove_any_item()
{
    if (size == 0)
    {
        throw("error");
    }
    int random_index = std::rand() % size;
    Stress_ball random_ball = array[random_index];
    Stress_ball *array2 = new Stress_ball[capacity];
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
void Collection::remove_this_item(const Stress_ball &sb)
{
    if (size == 0)
    {
        throw("error");
    }
    for (int index = 0; index < size; index++)
    {
        if (array[index] == sb)
        {
            Stress_ball *stress = new Stress_ball[capacity];
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
istream &operator>>(istream &is, Collection &c)
{
    while (!is.eof())
    {
        Stress_ball_colors color;
        Stress_ball_sizes size;
        string string_color = "";
        string string_size = "";

        is >> string_color;
        if (string_color == "red")
            color = Stress_ball_colors::red;
        else if (string_color == "blue")
            color = Stress_ball_colors::blue;
        else if (string_color == "yellow")
            color = Stress_ball_colors::yellow;
        else if (string_color == "green")
            color = Stress_ball_colors::green;

        is >> string_size;
        if (string_size == "small")
            size = Stress_ball_sizes::small;
        if (string_size == "medium")
            size = Stress_ball_sizes::medium;
        if (string_size == "large")
            size = Stress_ball_sizes::large;
        c.insert_item(Stress_ball(color, size));
    }
    return is;
}

// prints to the ostream os all the collection items in format: (color, size), each in one line. Use
// cout for output.
ostream &operator<<(ostream &os, const Collection &c)
{
    string string_size = "";
    string string_color = "";
    for (int x = 0; x < c.total_items(); x++)
    {
        // size
        switch (c[x].get_size())
        {
        case Stress_ball_sizes::small:
            string_size = "small";
            break;
        case Stress_ball_sizes::medium:
            string_size = "medium";
            break;
        case Stress_ball_sizes::large:
            string_size = "large";
            break;
        }
        // colors
        switch (c[x].get_color())
        {
        case Stress_ball_colors::red:
            string_color = "red";
            break;
        case Stress_ball_colors::blue:
            string_color = "blue";
            break;
        case Stress_ball_colors::green:
            string_color = "green";
            break;
        case Stress_ball_colors::yellow:
            string_color = "yellow";
            break;
        }
        os << "(" << string_color << ", " << string_size << ")\n";
    }
    return (os);
}

// a union operation that combines the contents of two collections into a third collection
// (the contents of c1 and c2 are not changed):
Collection make_union(const Collection &c1, const Collection &c2)
{
    Collection newCollection(c1.total_items() + c2.total_items());
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

void swap(Collection &c1, Collection &c2)
{
    Collection temp = move(c1);
    c1 = move(c2);
    c2 = move(temp);
}
void sort_by_size(Collection &c, Sort_choice sort)
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
                    Stress_ball temp = c[x];
                    c[x] = c[x + 1]; //swapping
                    c[x + 1] = temp;
                    swap = true;
                }
            }
        }
    }
}
