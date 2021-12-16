#include "BSTree.h"

#include <iostream>

#include <queue>

using namespace std;

///////////////////////////////////
// Already Implemented Functions //
///////////////////////////////////

// These functions are already implemented for you. Scroll below to
// see the functions that you have to implement

// constructors
BSTree::BSTree() : size(0), root(nullptr) {}

// input / output operators
ostream &operator<<(ostream &out, BSTree &tree)
{
  tree.print_level_by_level(out);
  return out;
}

ostream &operator<<(ostream &out, Node &node)
{
  return out << node.value << "[" << node.search_time << "] ";
}

istream &operator>>(istream &in, BSTree &tree)
{
  /*
      take input from the in stream, and build your tree
      input will look like
      4 
      2 
      6 
      1 
      3 
      5 
      7
    */
  int next;
  while (in >> next)
  {
    tree.insert(next);
  }
  return in;
}

// Example recursive function
// If you try to use it without care, you will get a memory leak.
void BSTree::copy_helper(Node *&newNode, const Node *sourceNode)
{
  //Don't copy if the node is nullptr
  if (sourceNode == nullptr)
    return;

  //Change the new node to a copy of sourceNode
  newNode = new Node(sourceNode->value);
  //Copy over the search cost
  newNode->search_time = sourceNode->search_time;

  //Copy left subtree
  if (sourceNode->left != nullptr)
    copy_helper(newNode->left, sourceNode->left);
  //Copy right subtree
  if (sourceNode->right != nullptr)
    copy_helper(newNode->right, sourceNode->right);
}

// recursive function
int BSTree::get_total_search_time(Node *node)
{
  if (node != nullptr)
  {
    return node->search_time + get_total_search_time(node->left) + get_total_search_time(node->right);
  }
  return 0;
}

// implemented
float BSTree::get_average_search_time()
{
  int total_search_time = get_total_search_time(root);
  if (total_search_time == 0)
    return -1;

  return ((float)total_search_time) / size;
}

///////////////////////////////////
//     Functions to Implement    //
///////////////////////////////////

// These are the functions you should implement
// Feel free to call the functions above or create new helper functions

// copy constructor
BSTree::BSTree(const BSTree &other)
{
  //cout << " in copy constructor" << endl;
  if (other.size == 0)
  {
    this->root = nullptr;
    size = 0;
  }
  else
  {
    this->size = other.size;             // copies over size
    copy_helper(this->root, other.root); // copies over node and all its values
  }
}

// move constructor
BSTree::BSTree(BSTree &&other)
{
  //cout << " in move constructor" << endl;
  this->root = other.root;
  other.root = nullptr;
  this->size = other.size;
  other.size = 0;
}

//copy assignment
BSTree &BSTree::operator=(const BSTree &other) // deep copy involving mem shit
{
  // cout << " in copy assignment" << endl;
  if (this != &other)
  {
    // deletes current tree
    if (this->root != nullptr)
    {
      this->~BSTree(); // allows for deep copy to occur
    }
    // deep copy other tree - when there are no values
    if (other.size == 0)
    {
      this->root = nullptr;
      size = 0;
    }
    else // deep copy when there are values
    {
      this->size = other.size;             // copies over size
      copy_helper(this->root, other.root); // copies over node and all its values
    }
  }
  return *this;
}

// move assignment
BSTree &BSTree::operator=(BSTree &&other)
{
  //cout << " in move assignment" << endl;
  if (this != &other)
  {
    if (this->root != nullptr)
    {
      this->~BSTree();
    }
    this->root = other.root;
    other.root = nullptr;
    this->size = other.size;
    other.size = 0;
  }
  return *this;
}

// destructor
BSTree::~BSTree()
{
  // Make sure to call delete on every node of the tree
  // You can use a recursive helper function to do this
  delete_node(this->root);
  //cout << " in destructor" << endl;
}

// delete for destructor : deletes node
void BSTree::delete_node(Node *&node)
{
  if (node != nullptr)
  {
    delete_node(node->right); //deletes right
    delete_node(node->left);  // deletes left
    node->left = nullptr;
    node->right = nullptr;
    delete node; // deallocates memory
    // cout << " in delete node" << endl;
  }
}

Node *BSTree::insert(int obj)
{
  /* insert a node into the tree
    first find where the node should go
    then modify pointers to connect your new node */
  int num_nodes = 1;
  Node *new_node = new Node(obj); // initializes new node
  Node *previous = nullptr;
  Node *marker = root;

  if (root == nullptr)
  {
    previous = nullptr;
    marker = nullptr;
    root = new_node;
    size = size + 1;
    // cout << "in root = nullptr" << endl;
    new_node->search_time = num_nodes;
    delete previous;
    delete marker;
    return new_node;
  }
  while (marker != nullptr)
  {
    if (obj > marker->value)
    {
      num_nodes = num_nodes + 1;
      previous = marker;
      marker = marker->right;
    }
    else if (obj < marker->value)
    {
      num_nodes = num_nodes + 1;
      previous = marker;
      marker = marker->left;
    }
    else
    {
      break;
    }
    //cout << "while loop : marker != nullptr" << endl;
  }
  if (marker == nullptr)
  {
    marker = new_node;
    if (obj > previous->value)
    {
      previous->right = marker;
    }
    else
    {
      previous->left = marker;
    }
    //cout << " if (marker == nullptr)" << endl;
    marker->search_time = num_nodes;
    size = size + 1;
    previous = nullptr;
    delete previous;
    new_node = nullptr;
    delete new_node;
    return marker;
  }
}

Node *BSTree::search(int obj)
{
  /* recursively search down the tree to find the node that contains obj
    if you don't find anything return nullptr */
  Node *temp = nullptr;
  if (this->root != nullptr)
  {
    temp = help_search(obj, this->root);
  }
  return temp;
}

Node *BSTree::help_search(int obj, Node *temp)
{
  if (temp->value < obj)
  {
    if (temp->right != nullptr)
    {
      help_search(obj, temp->right);
    }
  }
  else if (temp->value > obj)
  {
    if (temp->left != nullptr)
    {
      help_search(obj, temp->left);
    }
  }
  else
  {
    return temp;
  }
}

void BSTree::update_search_times()
{
  /* do a BFS or DFS of your tree and update the search times of all nodes at once
      The root has a search time of 1, and each child is 1 more than its parent */
  update_helper(1, this->root);
}

// timer node : search time assignment
void BSTree::update_helper(int time, Node *parent)
{
  parent->search_time = time;
  if (parent->right)
  {
    update_helper(time + 1, parent->right);
  }

  if (parent->left)
  {
    update_helper(time + 1, parent->left);
  }
}

void BSTree::inorder(ostream &out)
{
  /* print your nodes in infix order
    If our tree looks like this:

       4
     2   6
    1 3 5 7

    It should output:
    1[3] 2[2] 3[3] 4[1] 5[3] 6[2] 7[3]
    You can use the << operator to print the nodes in the format shown */
  printInOrder(out, this->root);
  out << endl;
}

// in order helper function
void BSTree::printInOrder(std::ostream &result, Node *parent)
{
  if (parent != nullptr)
  {
    printInOrder(result, parent->left);
    result << parent->value << "[" << parent->search_time << "] ";
    printInOrder(result, parent->right);
  }
}

void BSTree::print_level_by_level(ostream &out)
{

  /* Print the tree using a BFS so that each level contains the values for a level of the tree.
    Use X to mark empty positions. 
    
      if our tree looks like this:

       4
     2   6
    1   5 7
           9

    it should output:

    4[1]
    2[2] 6[2]
    1[3] X 5[3] 7[3]
    X X X X X X X 9[4]

    it might be helpful to do this part with the std::queue data structure.
    Hint: the Nth level contains 2^(N-1) nodes (with a value or with an X). Watch out
    for nodes like the left child of 6 above, and print the descendents of an empty
    node as also empty
    You can use the << operator to print nodes in the format shown */

  //PSEUDOCODE
  /*
  level by level(BinarySearchTree T)
  Queue q // This queue contains elements from a level and its children
  q.enqueue(T.root)
  elementsInLevel = 1 // Elements in the current level
  nonNullChild = false
  while (elementsInLevel > 0) do:
  TreeNode* node = q.dequeue()
  elementsInLevel--
  if node is not null:
  print node
  enqueue the children of node into q
  if at least one child is not null:
  nonNullChild = true
  else:
  print ’X’
  enqueue null // these nulls represent the descendants of the empty node
  enqueue null
  if elementsInLevel == 0 // We have reached the end of the current level
  print newline
  if nonNullChild == true: // The next level is non-empty
  nonNullChild = false
  elementsInLevel = q.size
    */
  queue<Node *> q;
  q.push(root);
  int elementsInLevel = 1;
  bool nonNullChild = false;
  while (elementsInLevel > 0)
  {
    Node *node = q.front(); // dequeue = q.front() + q.pop()
    q.pop();
    elementsInLevel--;
    if (node != nullptr)
    {
      out << *node;
      q.push(node->left);
      q.push(node->right);
      if (node->left != nullptr || node->right != nullptr)
        nonNullChild = true;
    }
    else
    {
      out << "X ";
      q.push(nullptr);
      q.push(nullptr);
    }
    if (elementsInLevel == 0)
    {
      out << std::endl;
      if (nonNullChild == true)
      {
        nonNullChild = false;
        elementsInLevel = q.size();
      }
    }
  }
}
