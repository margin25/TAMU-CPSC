#include "linked_list.h"
#include <iostream>
#include <string>
using std::cout, std::endl, std::string;

void MyList::add(string name, int score)
{
    MyNode *node = new MyNode(name, score);
    if (size() == 0)
    {
        _headPtr = node; //then headpointer = tailpointer
        _tailPtr = node;
        _size++; // increase size from 0 to 1
    }

    else //if size == 0
    {

        //
        //following module logic
        // need to use -> to access with pointer :
        // C++ Documentation : (pointer_name)->(variable_name)
        // Note: -> is kinda like .() except its for accesing members using a pointers

        _tailPtr->setNext(node); //Modify link to next node in linked list.
        _tailPtr = node;         //tailpointer is now the new node
        _size++;                 // increase size to account for new node
    }
}

void MyList::clear()
{
    // Clears linked list of all nodes, if any.
    while (_headPtr != nullptr)
    {
        _marker = _headPtr->next();
        // next() : Access link to next node in linked list. * @return :	Next node.
        // we set _marker = next node so we can later remove the _headpointer
        delete _headPtr; //deallocate memory of headpointer
        // ^ essentially clearing linked list of current index
        _headPtr = _marker; // acts as index++ for while loop : link now pointing to next index.
    }
    _headPtr = nullptr;
    _marker = nullptr;
    _tailPtr = nullptr;
    _size = 0; // size = 0 bc we just completed clearing
}

bool MyList::remove(string name)
{
    /**
     * Remove node from linked list with name data.
     * @param       Name data of node to remove.
     * @return      Whether node was removed from name data. 
    
    */

    // 3 possible places that NODES can be removed form in a Linked List
    // * front
    // * middle
    // * rear
    // TODO : consider each case.
    _prevPtr = nullptr;     // initializing prev ptr to null just in case
    _marker = _headPtr;     //initalizing marker start point to index 0
    if (_marker == nullptr) // can't do anything if marker is initially nullptr
    {
        return false;
    }
    if (_marker->name() == name) // if node needed to be removed is found in linked list @ current index
    {
        if (_tailPtr == _headPtr) // removing when linked list length = 1
        {
            _headPtr = nullptr; // set to null ptr bc we are going to delete marker later
            _tailPtr = nullptr; // set to null ptr bc we are going to delete marker later
        }
        else // _tailPtr != _headPtr : linked list length > 1
        {
            _headPtr = _marker->next();
        }
        delete _marker;
        _size -= 1;  // need to decrease size because marker index removed
        return true; // bc we succesfully removed
    }
    else // index we want to remove is not not found , we only update marker and previous pointer
    {
        _prevPtr = _marker;
        _marker = _marker->next();
    }
    while (_marker != nullptr) // traverses through Linked List
    {
        if (_marker->name() == name) // if node needed to be removed is found in linked list @ current index
        {
            if (_marker == _tailPtr) // rear case
            {
                _tailPtr = _prevPtr;
                _prevPtr->setNext(nullptr);
            }
            else
            {
                _prevPtr->setNext(_marker->next());
            }
            delete _marker;
            _size = _size - 1;
            return true;
        }
        _prevPtr = _marker;
        _marker = _marker->next();
    }
    // index not found
    return false;
}

bool MyList::insert(string name, int score, size_t index)
{
    return false;
}

MyList::MyList()
{
    _size = 0;
    _headPtr = nullptr;
    _tailPtr = nullptr;
    _prevPtr = nullptr;
    _marker = nullptr;
}

MyList::~MyList()
{
    clear();
}

size_t MyList::size()
{
    return _size;
}

bool MyList::empty()
{
    return _headPtr == nullptr;
}

MyNode *MyList::head()
{
    return _headPtr;
}

void MyList::printList()
{
    _marker = _headPtr;
    if (_marker == nullptr)
    {
        cout << "Linked list is empty" << endl;
        return;
    }

    while (_marker != nullptr)
    {
        cout << "[ " << _marker->name() << ", " << _marker->score() << " ]" << endl;
        _marker = _marker->next();
    }
}

MyNode::MyNode(std::string name, int score)
{
    _name = name;
    _score = score;
    _nextPtr = nullptr;
}

std::string MyNode::name()
{
    return _name;
}

int MyNode::score()
{
    return _score;
}

void MyNode::setNext(MyNode *other)
{
    _nextPtr = other;
}

MyNode *MyNode::next()
{
    return _nextPtr;
}