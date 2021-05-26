#include <iostream>
#include <string>
#include "LinkedList.h"

using std::string, std::ostream, std::endl, std::cout;

// TODO(student): the rest of the LinkedList

LinkedList::LinkedList() : _size(0), _headPtr(nullptr), _tailPtr(nullptr), _prevPtr(nullptr), _marker(nullptr) // default constructor
{
    // default constructor makes an empty list (zero size, null head).
    // cout << "Default constructor called." << endl;
    _size = 0;
    _headPtr = nullptr;
    _tailPtr = nullptr;
    _prevPtr = nullptr;
    _marker = nullptr;
}

LinkedList::LinkedList(const LinkedList &LinkedList) : _size(0), _headPtr(nullptr), _tailPtr(nullptr), _prevPtr(nullptr), _marker(nullptr) //  Copy Constructor
{
    // FIX :
    // cout << "Copy constructor called." << endl;
    _size = LinkedList._size;       //
    _prevPtr = LinkedList._prevPtr; //
    _tailPtr = LinkedList._tailPtr; //
    _headPtr = LinkedList._headPtr; //
    _marker = LinkedList._marker;   //
}

LinkedList &LinkedList::operator=(const LinkedList &objToCopy) //Copy Assignment
{
    // FIX
    // cout << "Copy Assignment Operator called." << endl;
    if (this != &objToCopy)
    {
        _size = objToCopy._size;
        _headPtr = objToCopy._headPtr;
        _tailPtr = objToCopy._tailPtr;
        _prevPtr = objToCopy._prevPtr;
        _marker = objToCopy._marker;
    }
    return (*this);
}

LinkedList::~LinkedList() // Destructor
{
    // cout << "Destructor called." << endl;
    clear();
}

void LinkedList::clear()
{
    // Clears linked list of all nodes, if any.
    while (_headPtr != nullptr)
    {
        _marker = _headPtr->next;
        // next() : Access link to next node in linked list. * @return :	Next node.
        // we set _marker = next node so we can later remove the _headpointer
        delete _headPtr; //deallocate memory of headpointer
        // ^ essentially clearing linked list of current index
        _headPtr = _marker; // acts as index++ for while loop : link now pointing to next index.
    }
    _headPtr = nullptr;
    _size = 0; // size = 0 bc we just completed clearing
    _marker = nullptr;
    _tailPtr = nullptr;
}

std::size_t LinkedList::size() const
{
    int counter = 0;           // initialize the counter
    Node *current = _headPtr;  // initialize pointer that will traverse the list
    while (current != nullptr) // increment counter until pointer points to null
    {
        counter++;
        current = current->next;
    }
    return counter; // returns size
}

bool LinkedList::empty()
{
    return (_headPtr == nullptr);
}

const Node *LinkedList::head() const
{
    // returns pointer to the head of the list, or nullptr if the list is empty.
    // cout << "Head" << endl;
    if (size() == 0)
    {
        return (nullptr);
    }
    return _headPtr;
}

void LinkedList::push_back(int value)
{
    // cout << "push back" << endl;
    Node *new_node = new Node(); //create node
    new_node->data = value;      // copy value over to new node data
    new_node->next = nullptr;    // new node links to nullptr

    if (_headPtr == nullptr) // Base Case : size == 0 , Linked List is empty
    {
        _headPtr = new_node;
    }

    else // Linked List is NOT empty
    {
        Node *curr = _headPtr; // will be used to traverse through Linked List
        while (curr->next != nullptr)
        {
            curr = curr->next; // traversing through linked list
        }
        curr->next = new_node;
    }
}

void LinkedList::remove_duplicates()
{

    //Node *curr = _headPtr;
    Node *curr2 = nullptr;

    for (Node *curr = _headPtr; curr != nullptr; curr = curr->next)
    {
        curr2 = curr;                    // used to iterate through list & compare current index with all other values
        while ((curr2->next) != nullptr) // stop comparing when what curr2 points to hits nullptr
        {
            if (curr->data == ((curr2->next)->data)) // found duplicate
            {
                Node *after = curr2->next;       // we want to skip the value of duplicate
                curr2->next = curr2->next->next; // changing pointer path
                delete after;                    //removing duplicate
            }
            else
            {
                curr2 = curr2->next; // when duplicate not found continue on normally
            }
        }
    }
}

std::size_t LinkedList::length_max_decreasing() const
{
    Node *curr1 = _headPtr->next;
    Node *curr2 = nullptr;
    if (size() == 1)
    {
        return 1;
    }
    size_t counter = 1;
    size_t max_decreasing = 0;
    while ((curr1->next) != nullptr)
    {
        curr2 = curr1->next; // increment curr2
        if (curr1->data > (curr2->data))
        {
            counter++;
            if (counter > max_decreasing)
            {

                max_decreasing = counter;
            }
        }
        else // reset counter for next subsequence
        {
            counter = 1;
        }
        curr1 = curr1->next; // increment curr1
    }

    return (max_decreasing);

    /* size_t counter = 0;
    size_t max_decreasing = 0;
    for (Node *index = _headPtr; index != nullptr; index = index->next)
    {

        while ((index->next) != nullptr)
        {
            if (index->data > ((index->next)->data))
            {
                counter++;
                if (counter > max_decreasing)
                {
                    max_decreasing = counter;
                    counter = 0;
                }
            }
        }
    }
    return (max_decreasing); */
}

bool LinkedList::contains(int value) const
{

    if (_headPtr == nullptr) // Base Case : size == 0 , Linked List is empty
    {
        return false;
    }

    else // Linked List is NOT empty
    {
        Node *curr = _headPtr; // will be used to traverse through Linked List
        while (curr->next != nullptr)
        {
            if (curr->data == value)
            {
                return true;
                // curr = curr->next;
            }
            curr = curr->next;
        }
        return false;
    }
}

std::size_t LinkedList::find_last_of(int value) const
{
    // Finds the last element equal to the given value.
    size_t last = 0;
    size_t index = 0;
    size_t counter = 0;
    if (_headPtr == nullptr)
    {
        return -1;
    }
    else // Linked List is NOT empty
    {
        for (Node *i = _headPtr; i != nullptr; i = i->next)
        {

            if (i->data == value)
            {
                last = index;
                counter++;
            }
            index++;
        }
        if (counter >= 1)
        {
            return (last);
        }
        else
        {
            return -1;
        }
    }
}

void LinkedList::remove(std::size_t index)
{
    if (index >= size())
    {
        throw std::out_of_range("Invalid argument");
    }
    // Base Case
    if (index == 1)
    {
        Node *curr = _headPtr;
        _headPtr = _headPtr->next;
        curr->next = nullptr;
    }
    else
    {
        Node *past = _headPtr;
        size_t counter = 0;
        while (counter < index - 1)
        {
            past = past->next;
            counter++;
        }
        Node *now = past->next;
        past->next = now->next;
        delete now;
    }
}

/* void LinkedList::printList()
{
    _marker = _headPtr;
    if (_marker == nullptr)
    {
        cout << "Linked list is empty" << endl;
        return;
    }

    while (_marker != nullptr)
    {
        cout << "[ " << _marker->data << " ]" << endl;
        _marker = _marker->next;
    }
} */

// || NODE ||
Node::Node() : data(0), next(nullptr), _nextPtr(nullptr)
{
    _nextPtr = nullptr;
}
void Node::setNext(Node *other)
{
    _nextPtr = other;
}

/* Node *Node::next()
{
    return _nextPtr;
} */
