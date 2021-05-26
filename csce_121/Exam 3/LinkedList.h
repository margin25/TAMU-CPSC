#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct Node
{
    // TODON'T(student): change the visibility, types, or names of the members
    // TOMAYBE(student): the optional-rest of the Node
    int data;
    Node *next;
    Node();
    // Node *nodes;
    void setNext(Node *other);

private:
    /**
     * Link to next node in linked list.
     */
    Node *_nextPtr;
};

class LinkedList
{
public:
    // Default constructor that initializes list size and node pointers.
    LinkedList();

    // Copy Constructor
    LinkedList(const LinkedList &LinkedList);

    // Copy Assignment Operator
    LinkedList &operator=(const LinkedList &objToCopy);

    // Destructor that deallocates node pointers
    ~LinkedList();

    // Get size of linked list.
    std::size_t size() const;

    // Get whether linked list is empty or not.

    bool empty();

    // Get head node of linked list.
    const Node *head() const;

    // Clears linked list of all nodes, if any.

    void clear();

    // Insert node into index of linked list with node data.

    bool insert(std::string name, int score, size_t index);

    // Display data of every node in linked list.

    void printList();

    void remove_duplicates();

    void push_back(int value);

    std::size_t length_max_decreasing() const;

    bool contains(int value) const;

    std::size_t find_last_of(int value) const;

    void remove(std::size_t index);

private:
    // Size of linked list.
    size_t _size;
    // Pointer to head node.
    Node *_headPtr;
    // Pointer to tail node.
    Node *_tailPtr;
    // Pointer to previous node to current marked node.
    Node *_prevPtr;
    // Pointer to current marked node.
    Node *_marker;
};

#endif // LINKEDLIST_H