// implementation of the DLList class
#include <iostream>
#include <string>
#include "DLList.h"

DLList::DLList() : header(0), trailer(0) // default constructor
{
    header.next = &trailer;
    trailer.prev = &header;
}

DLList::DLList(DLList &&dll)
{
    header.next = dll.first_node();
    dll.first_node()->prev = &header;
    trailer.prev = dll.after_last_node()->prev;
    dll.after_last_node()->prev->next = &trailer;
    dll.trailer.prev = &dll.header;
    dll.header.next = &dll.trailer;
}

DLList::DLList(const DLList &dll)
{
    header.next = &trailer;
    trailer.prev = &header;
    DLListNode *new_node = dll.first_node();
    while (new_node != dll.after_last_node())
    {
        insert_last(new_node->obj);
        new_node = new_node->next;
    }
}

DLList::~DLList()
{
    DLListNode *curr = first_node();
    while (curr != after_last_node())
    {
        DLListNode *temp = curr;
        curr = curr->next;
        delete (temp);
    }
    header.next = &trailer;
    trailer.prev = &header;
}

// copy assignment operator
DLList &DLList::operator=(const DLList &dll)
{
    if (this != &dll)
    {
        if (!this->is_empty())
        {
            DLListNode *prev = header.next;
            DLListNode *new_node = header.next;
            while (new_node != &trailer)
            {
                prev = new_node;
                new_node = new_node->next;
                delete prev;
            }
        }
        trailer.prev = &header;
        header.next = &trailer;
        DLListNode *new_node = dll.first_node();
        while (new_node != dll.after_last_node())
        {
            insert_last(new_node->obj);
            new_node = new_node->next;
        }
    }
    return *this;
}

DLList &DLList::operator=(DLList &&dll)
{
    if (this != &dll)
    {
        DLListNode *marker = first_node();
        while (marker != after_last_node())
        {
            DLListNode *temp = marker;
            marker = marker->next;
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

DLListNode *DLList::first_node() const
{
    return header.next;
}

const DLListNode *DLList::after_last_node() const
{
    return trailer.prev->next; //pointer to trailer
}

bool DLList::is_empty() const
{
    return header.next == &trailer;
}

int DLList::first() const
{
    if (!is_empty())
        return header.next->obj;
    else
        throw invalid_argument("exception thrown");
}

int DLList::last() const
{
    if (!is_empty())
        return trailer.prev->obj;
    else
        throw invalid_argument("exception thrown");
}

void DLList::insert_first(int obj)
{
    DLListNode *node = new DLListNode(obj, &header, header.next);
    header.next->prev = node;
    header.next = node;
}

int DLList::remove_first()
{
    if (!is_empty())
    {
        DLListNode *curr = header.next;
        header.next = curr->next;
        curr->next->prev = &header;
        int value = curr->obj;
        delete (curr);
        return value;
    }
    else
        throw invalid_argument("exception thrown");
}

void DLList::insert_last(int obj)
{
    DLListNode *currnode = new DLListNode(obj, trailer.prev, &trailer);
    trailer.prev->next = currnode;
    trailer.prev = currnode;
}

int DLList::remove_last()
{
    if (!is_empty())
    {
        DLListNode *temp = trailer.prev;
        trailer.prev = temp->prev;
        temp->prev->next = &trailer;
        int value = temp->obj;
        delete (temp);
        return value;
    }
    else
        throw invalid_argument("exception thrown");
}

void DLList::insert_after(DLListNode &p, int obj)
{
    DLListNode *new_node = new DLListNode(obj, &p, p.next);
    p.next->prev = new_node;
    p.next = new_node;
}

void DLList::insert_before(DLListNode &p, int obj)
{
    DLListNode *new_node = new DLListNode(obj, p.prev, &p);
    p.prev->next = new_node;
    p.prev = new_node;
}

int DLList::remove_after(DLListNode &p)
{
    if (&p != &trailer && p.next != &trailer)
    {
        DLListNode *curr = p.next;
        p.next = curr->next;
        curr->next->prev = &p;
        int value = curr->obj;
        delete (curr);
        return value;
    }
    else
        throw invalid_argument("exception thrown");
}

int DLList::remove_before(DLListNode &p)
{
    if (&p != &header && &p != header.next)
    {
        DLListNode *curr = p.prev;
        p.prev = curr->prev;
        curr->prev->next = &p;
        int value = curr->obj;
        delete (curr);
        return value;
    }
    else
        throw invalid_argument("exception thrown");
}
ostream &operator<<(ostream &out, const DLList &dll)
{
    DLListNode *mark = dll.first_node();
    while (mark != dll.after_last_node()) // loops through full linked list
    {
        out << mark->obj << ", ";
        mark = mark->next;
    }
    return out;
}
