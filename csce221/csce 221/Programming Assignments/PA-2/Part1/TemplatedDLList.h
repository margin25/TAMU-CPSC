// header file for the templated DLList

#ifndef TEMPLATEDDLLIST_H
#define TEMPLATEDDLLIST_H

#include <iostream>
#include <stdexcept>

using namespace std;

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

//default constructor
template <typename T>
DLList<T>::DLList() : header(T()), trailer(T())
{
  header.next = &trailer;
  trailer.prev = &header;
}

// copy constructor
template <typename T>
DLList<T>::DLList(const DLList<T> &dll)
{
  header.next = &trailer;
  trailer.prev = &header;
  DLListNode<T> *mark = dll.first_node();
  while (mark != dll.after_last_node())
  {
    insert_last(mark->obj);
    mark = mark->next;
  }
}

//
template <typename T>
DLList<T>::DLList(DLList<T> &&dll)
{
  header.next = dll.first_node();
  dll.first_node()->prev = &header;
  trailer.prev = dll.after_last_node()->prev;
  dll.after_last_node()->prev->next = &trailer;
  dll.header.next = &dll.trailer;
  dll.trailer.prev = &dll.header;
}

// deconstructor
template <typename T>
DLList<T>::~DLList()
{
  DLListNode<T> *mark = first_node();
  while (mark != after_last_node())
  {
    DLListNode<T> *temp = mark;
    mark = mark->next;
    delete (temp);
  }
  header.next = &trailer;
  trailer.prev = &header;
}

//copy assignment
template <typename T>
DLList<T> &DLList<T>::operator=(const DLList<T> &dll)
{
  if (this != &dll)
  {
    DLListNode<T> *curr = first_node();
    while (curr != dll.after_last_node())
    {
      DLListNode<T> *temporary = curr;
      curr = curr->next;
      delete (temporary);
    }
    trailer.prev = &header;
    header.next = &trailer;
    curr = dll.first_node();
    while (curr != dll.after_last_node())
    {
      insert_last(curr->obj);
      curr = curr->next;
    }
  }
  return *this;
}

//
template <typename T>
DLList<T> &DLList<T>::operator=(DLList<T> &&dll)
{
  if (this != &dll)
  {
    DLListNode<T> *mark = first_node();
    while (mark != after_last_node())
    {
      DLListNode<T> *temp = mark;
      mark = mark->next;
      delete (temp);
    }

    header.next = dll.first_node();
    dll.first_node()->prev = &header;
    trailer.prev = dll.after_last_node()->prev;
    dll.after_last_node()->prev->next = &trailer;

    dll.header.next = &dll.trailer;
    dll.trailer.prev = &dll.header;
  }
  return *this;
}

// first()
template <typename T>
T DLList<T>::first() const
{
  if (!is_empty())
    return header.next->obj;
  else
    throw invalid_argument("the list is empty.");
}

// last()
template <typename T>
T DLList<T>::last() const
{
  if (!is_empty())
    return trailer.prev->obj;
  else
    throw invalid_argument("the list is empty");
}

// insert_first()
template <typename T>
void DLList<T>::insert_first(T obj)
{
  DLListNode<T> *new_node = new DLListNode<T>(obj, &header, header.next);
  header.next->prev = new_node;
  header.next = new_node;
}

// remove first()
template <typename T>
T DLList<T>::remove_first()
{
  if (!is_empty())
  {
    DLListNode<T> *temp = header.next;
    header.next = temp->next;
    temp->next->prev = &header;
    T value = temp->obj;
    delete (temp);
    return value;
  }
  else
    throw invalid_argument("the list is empty");
}

// insert last()
template <typename T>
void DLList<T>::insert_last(T obj)
{
  DLListNode<T> *new_node = new DLListNode<T>(obj, trailer.prev, &trailer);
  trailer.prev->next = new_node;
  trailer.prev = new_node;
}

// remove last()
template <typename T>
T DLList<T>::remove_last()
{
  if (!is_empty())
  {
    DLListNode<T> *temp = trailer.prev;
    trailer.prev = temp->prev;
    temp->prev->next = &trailer;
    T value = temp->obj;
    delete (temp);
    return value;
  }
  else
    throw invalid_argument("the list is empty");
}

// insert after()
template <typename T>
void DLList<T>::insert_after(DLListNode<T> &p, T obj)
{
  DLListNode<T> *new_node = new DLListNode<T>(obj, &p, p.next);
  p.next->prev = new_node;
  p.next = new_node;
}

// insert before
template <typename T>
void DLList<T>::insert_before(DLListNode<T> &p, T obj)
{
  DLListNode<T> *new_node = new DLListNode<T>(obj, p.prev, &p);
  p.prev->next = new_node;
  p.prev = new_node;
}

// remove after
template <typename T>
T DLList<T>::remove_after(DLListNode<T> &p)
{
  if (&p != trailer.next && &p != &trailer)
  {
    DLListNode<T> *temp = p.next;
    p.next = temp->next;
    temp->next->prev = &p;
    T data = temp->obj;
    delete (temp);
    return data;
  }
  else
    throw invalid_argument("last node");
}

// remove before
template <typename T>
T DLList<T>::remove_before(DLListNode<T> &p)
{
  if (&p != &header && &p != header.next)
  {
    DLListNode<T> *curr = p.prev;
    p.prev = curr->prev;
    curr->prev->next = &p;
    T value = curr->obj;
    delete (curr);
    return value;
  }
  else
    throw invalid_argument("first node");
}

// output operator
template <typename T>
ostream &operator<<(ostream &out, const DLList<T> &dll)
{
  DLListNode<T> *mark = dll.first_node();
  while (mark != dll.after_last_node())
  {
    out << mark->obj << ", ";
    mark = mark->next;
  }
  return out;
}

#endif
