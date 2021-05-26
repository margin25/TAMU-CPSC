// my_string.cpp
#include <iostream>
#include "my_string.h"
#include "my_sstream.h"

// TODO(student): define all necessary my_string methods
// NOTE: some methods suggested here may not be required for you.
//       if you don't need a method, then you are not required to implement it
// NOTE: some methods not suggested here may be required for you.
//       if you need a method, then you are required to implement it (or re-engineer your solution to no longer need the method).

// my_string methods

// constructors
//   default (done for you.  you're welcome.)
my_string::my_string() : _data(new char[1]{0}), _capacity(1), _size(0) {}

//   rule of "3"
//    my_string copy constructor
my_string::my_string(const my_string &origString) : _data(new char[origString._capacity]), _capacity(origString._capacity), _size(origString._size)
{
    // Allocate sub-object
    // *_data = *(origString._data);
    for (size_t i = 0; i < _size; i++)
    {
        _data[i] = origString[i];
    }
}
//     my_string copy assignment
my_string &my_string::operator=(const my_string &other)
{
    // In general, any time you need to write your own custom copy
    //constructor, you also need to write a custom assignment operator

    if (this != &other)
    {
        this->_size = other._size;
        this->_capacity = other._capacity;
        delete[] _data;
        _data = new char[_capacity];
        for (size_t i = 0; i < this->_size; i++)
        {
            this->_data[i] = other[i];
        }
    }

    return *this;
}
//     destructor
my_string::~my_string()
{
    delete[] _data; // deallocating member bc of use of new.
}
//   c-string copy constructor (teams up with my_string copy assignment to handle c-string copy assignment)

my_string::my_string(const char *other) : _data(nullptr), _capacity(0), _size(0)
{
    //The constructor copies the contents from
    //a C-string (a null-terminated character array) to the new my_string object.
    for (size_t i = 0; other[i] != '\0'; ++i)
    {
        _size++;
    }
    _capacity = _size; //size+1
    _data = new char[_capacity];
    for (size_t j = 0; j < _size; j++)
    {
        _data[j] = other[j];
    }
}
// element access
//   at
char &my_string::at(my_string::size_type index) // return by reference
{
    return _data[index];
}

const char &my_string::at(size_type index) const
{
    return _data[index];
}
//   front

//////// || DO NOT NEED TO IMPLEMENT ||

//   operator[] : Not Working

const char &my_string::operator[](size_type index) const
{
    return (_data[index]);
}
char &my_string::operator[](size_type index)
{
    return (_data[index]);
}

// capacity

//   empty
bool my_string::empty() const
{
    if (_size == 0)
    {
        return true;
    }
    return false;
}
//   size
my_string::size_type my_string::size() const { return _size; }
my_string::size_type my_string::capacity() const { return _capacity; }
char *my_string::data() const { return _data; }
//void my_string::set_data(char *data) {}
void my_string::set_capacity(my_string::size_type cap) // setter function : lets us change the private data member
//w/o making compiler angry?
{
    _capacity = cap;
}

// operations
//   concatenation

my_string operator+(my_string lhs, const my_string &rhs)
{
    for (size_t i = 0; i < rhs._size; i++)
    {
        lhs = lhs + rhs[i];
    }
    return (lhs);
}
//     my_string + c-string (non-member, friend)

my_string operator+(my_string lhs, const char *rhs)
{
    size_t curr_char = 0;
    while (rhs[curr_char] != '\0')
    {
        lhs = lhs + rhs[curr_char];
    }
    return (lhs);
}
my_string operator+(my_string lhs, char rhs)
{

    if (lhs._capacity == lhs._size)
    {
        size_t temp_cap = 2 * lhs._capacity;
        char *temp = new char[temp_cap];
        for (size_t i = 0; i < lhs._size; i++)
        {
            temp[i] = lhs[i];
        }
        delete[] lhs._data;
        lhs._data = temp;
        lhs._capacity = temp_cap;
    }
    lhs._data[lhs._size] = rhs;
    lhs._size++;

    return (lhs);
}

my_string operator+(const char *lhs, const my_string &rhs)
{
    return my_string(lhs) + rhs;
}

my_string operator+(char lhs, my_string rhs)
{
    char add[2];
    add[0] = lhs;
    add[1] = '\0';
    return (add + rhs);
}

//     my_string + char (non-member, friend)
//     c-string + my_string (non-member, friend)
//     char + my_string (non-member, friend)
//     my_string += my_string
//     my_string += c-string
//     my_string += char

// search
//   find

// non-member functions
//   relational operators
//     my_string == my_string

//     my_string == c-string

//   stream operators

//     ostream insertion operator : cout

std::ostream &operator<<(std::ostream &os, const my_string &str)
{
    //use for loop: iterate through my_string
    for (size_t i = 0; i < str.size(); i++)
    {
        os << str.at(i);
    }
    return (os);
}

//     istream extraction operator

/* std::istream &operator>>(std::istream &os, my_string &str) // Help
{
    std::cout << "str.size():" << str.size() << std::endl;
    std::cout << "str.capacity():" << str.capacity() << std::endl;
     if (str.capacity() == 0)
    {
        str.set_capacity(10);
    } 

 for (size_t i = 0; i < str.size(); i++)
    {
        os >> str.at(i);
    } 

char x[100];
    os >> x;
    str._data = x;
    return (os); 
}
*/

bool operator==(const my_string &lhs, const my_string &rhs)
{
    if (lhs.size() != rhs.size())
    {
        return false;
    }
    for (size_t i = 0; i < lhs.size(); i++)
    {
        if (lhs.data()[i] != rhs.data()[i])
        {
            return false;
        }
    }
    return true;
}

bool operator==(const my_string &lhs, const char *rhs)
{
    size_t index = 0;
    while (rhs[index] != '\0')
    {
        index++;
    }
    if (lhs.size() != index)
    {
        return false;
    }
    for (size_t i = 0; i < lhs.size(); i++)
    {
        if (lhs.data()[i] != rhs[i])
        {
            return false;
        }
    }
    return true;
}

//     getline
/* std::istream &getline(std::istream &is, my_string &str, char delim = '\n')
{
} */
//   numeric conversions

//     to_string
/* my_string to_string(int val)
{
} */
// my_istringstream methods

// || erase() ||
/* my_string &my_string::erase(size_t pos, size_t len)
{
    // Erase characters from my_string
    // Erases part of the string, reducing its length:
    char *r = new char[_size - (len - pos)];
    for (size_t j = 0; j < (_size - (len - pos)); j++)
    {
        r[j] = _data[i];
    }
} */

// || substr() ||
// GET HELP
my_string my_string::substr(size_t pos) const
{
    // Returns a newly constructed string object with
    // its value initialized to a copy of a substring of this object.
    my_string ret;
    //char *r = new char[_size - pos + 1]; //+1 to account for null character
    for (size_t i = pos; i < _size; i++)
    {
        ret = ret + _data[i];
    }
    return ret;
}

// || insert() ||

/* my_istringstream::my_istringstream(const my_string& str) : _str(str), idx(0), state_fail(false), state_eof(str.empty()) {}

void my_istringstream::eat_whitespaces() {
    while (idx < _str.size() && isspace(_str[idx])) {
        idx++;
    }
}



my_istringstream& my_istringstream::operator>>(my_string& str) {
    eat_whitespaces();
    if (eof()) {
        state_fail = true;
    }
    if (fail()) {
        return *this;
    }
    my_string s;
    while (idx < _str.size() && !isspace(_str[idx])) {
        s += _str[idx++];
    }
    if (idx == _str.size()) {
        state_eof = true;
    }
    str = s;
    return *this;
}

my_istringstream& my_istringstream::operator>>(char& c) {
    eat_whitespaces();
    if (eof()) {
        state_fail = true;
    }
    if (fail()) {
        return *this;
    }
    if (idx < _str.size()) {
        c = _str[idx++];
    }
    if (idx == _str.size()) {
        state_eof = true;
    }
    return *this;
}

bool my_istringstream::good() const { return !(state_fail || state_eof); }
bool my_istringstream::fail() const { return state_fail; }
bool my_istringstream::eof() const { return state_eof; }
 */
// TODO(student): define other my_istringstream methods, if any
