/*
 * Author:      Alexander Born
 * Course:      Fall 2020 CSCE 221 502
 * Date:        2020-10-06
 * Assignment:  PA2
 */

#ifndef _TEMPLATED__DLLIST_H
#define _TEMPLATED__DLLIST_H

#include <iostream>
#include <stdexcept>

using namespace std;

// Exception from notes
struct EmptyDLinkedListException : std::logic_error
{

    EmptyDLinkedListException()
        : std::logic_error("Empty Double Linked List")
    {
    }
};

struct MutatedOutOfBounds : std::out_of_range
{
    MutatedOutOfBounds()
        : std::out_of_range("Attempted to mutate node which is out of bounds."){};
};

template <typename T>
class DLList; // class declaration

// doubly linked list node
template <typename T>
struct DLListNode
{
    T obj;
    DLListNode<T> *prev, *next;
    // constructor
    DLListNode(T e = T(), DLListNode *p = nullptr, DLListNode *n = nullptr) : obj(e), prev(p), next(n) {}
};

// doubly linked list class
template <typename T>
class DLList
{
private:
    DLListNode<T> header, trailer;

public:
    DLList();                                   // default constructor
    DLList(const DLList<T> &dll);               // copy constructor
    DLList(DLList<T> &&dll);                    // move constructor
    ~DLList();                                  // destructor
    DLList<T> &operator=(const DLList<T> &dll); // copy assignment operator
    DLList<T> &operator=(DLList<T> &&dll);      // move assignment operator
    // return the pointer to the first node
    DLListNode<T> *first_node() const { return header.next; }
    // return the pointer to the trailer
    const DLListNode<T> *after_last_node() const { return &trailer; }
    // return if the list is empty
    bool is_empty() const { return header.next == &trailer; }
    T first() const;          // return the first object
    T last() const;           // return the last object
    void insert_first(T obj); // insert to the first node
    T remove_first();         // remove the first node
    void insert_last(T obj);  // insert to the last node
    T remove_last();          // remove the last node
    void insert_after(DLListNode<T> &p, T obj);
    void insert_before(DLListNode<T> &p, T obj);
    T remove_after(DLListNode<T> &p);
    T remove_before(DLListNode<T> &p);
};

template <typename T>
std::ostream &operator<<(std::ostream &stream, const DLList<T> &dll)
{
    const DLListNode<T> *cursor = dll.first_node();

    while ((cursor = cursor->next) != nullptr)
        stream << cursor->prev->obj << ", ";

    return stream;
}

template <typename T>
DLList<T>::DLList()
{
    header.next = &trailer;
    trailer.prev = &header;
}

/*
  Copies a chain of heap nodes
  Returns the last nodes in the chain

  Last node next pointer remains null
  First node prev pointer is unset
*/
template <typename T>
DLListNode<T> *realloc_heap_nodes(const DLListNode<T> *src, DLListNode<T> *dst)
{

    const DLListNode<T> *cursor = src->next;

    while ((cursor = cursor->next) != nullptr)
    {
        DLListNode<T> *n = new DLListNode<T>(cursor->prev->obj, dst);
        dst->next = n;
        dst = dst->next;
    }

    return dst;
}

template <typename T>
void del_heap_nodes(const DLListNode<T> *src)
{
    const DLListNode<T> *cursor = src->next;

    // Delete all heap allocated nodes
    while ((cursor = cursor->next) != nullptr)
        delete cursor->prev;
}

template <typename T>
DLList<T>::~DLList()
{
    del_heap_nodes(&header);
}

template <typename T>
DLList<T>::DLList(const DLList<T> &dll)
{
    trailer.prev = realloc_heap_nodes<T>(&dll.header, &header);
    trailer.prev->next = &trailer;
}

template <typename T>
DLList<T> &DLList<T>::operator=(const DLList<T> &dll)
{
    del_heap_nodes<T>(&header);

    trailer.prev = realloc_heap_nodes<T>(&dll.header, &header);
    trailer.prev->next = &trailer;

    return *this;
}

// Move macro
// src: source list object (reference)
// dst: destination list pointer
//
// this is ugly -- avoiding modifying the header to ensure compatibility
#define MOVE_DLL_CONTENT(src, dst)                   \
    {                                                \
        if (!src.is_empty())                         \
        {                                            \
            dst->header = src.header;                \
            dst->trailer = src.trailer;              \
                                                     \
            /* Rewire stack pointers */              \
            dst->header.next->prev = &dst->header;   \
            dst->trailer.prev->next = &dst->trailer; \
                                                     \
            /* Husk old object */                    \
            src.header.next = &src.trailer;          \
            src.trailer.prev = &src.header;          \
        }                                            \
        else                                         \
        {                                            \
            /*                                       \
             * construct to avoid wiring             \
             * destination head to source tail       \
             * during reassignment                   \
             *                                       \
             */                                      \
            dst->header.next = &dst->trailer;        \
            dst->trailer.prev = &dst->header;        \
        }                                            \
    }

template <typename T>
DLList<T>::DLList(DLList<T> &&dll)
{
    MOVE_DLL_CONTENT(dll, this);
}

template <typename T>
DLList<T> &DLList<T>::operator=(DLList<T> &&dll)
{
    if (&dll != this)
    {
        del_heap_nodes<T>(&header);

        MOVE_DLL_CONTENT(dll, this);
    }

    return *this;
}

template <typename T>
T DLList<T>::first() const
{
    if (is_empty())
        throw EmptyDLinkedListException();

    return header.next->obj;
}

template <typename T>
T DLList<T>::last() const
{
    if (is_empty())
        throw EmptyDLinkedListException();

    return trailer.prev->obj;
}

/* Removal */

// Helper
template <typename T>
T remove_node(DLListNode<T> *r)
{
    T obj = r->obj;

    // Rewire pointers
    r->prev->next = r->next;
    r->next->prev = r->prev;
    delete r;

    return obj;
}

template <typename T>
T DLList<T>::remove_after(DLListNode<T> &p)
{
    if (is_empty())
        throw EmptyDLinkedListException();
    else if (&p == &trailer || p.next == &trailer)
        throw MutatedOutOfBounds();

    return remove_node<T>(p.next);
}

// Should be const to permit removal of the last node from trailer
template <typename T>
T DLList<T>::remove_before(DLListNode<T> &p)
{
    if (is_empty())
        throw EmptyDLinkedListException();
    else if (&p == &header || p.prev == &header)
        throw MutatedOutOfBounds();

    return remove_node<T>(p.prev);
}

template <typename T>
T DLList<T>::remove_first() { return remove_after(header); }

template <typename T>
T DLList<T>::remove_last() { return remove_before(trailer); }

/* Insertion */

// Helper
template <typename T>
void insert_node(DLListNode<T> *at, T new_obj)
{
    DLListNode<T> *n = new DLListNode<T>(new_obj, at, at->next);
    n->prev->next = n;
    n->next->prev = n;
}

template <typename T>
void DLList<T>::insert_after(DLListNode<T> &p, T obj)
{
    insert_node<T>(&p, obj);
}

template <typename T>
void DLList<T>::insert_before(DLListNode<T> &p, T obj)
{
    insert_node<T>(p.prev, obj);
}

template <typename T>
void DLList<T>::insert_last(T obj)
{
    insert_before(trailer, obj);
}

template <typename T>
void DLList<T>::insert_first(T obj)
{
    insert_after(header, obj);
}

#endif