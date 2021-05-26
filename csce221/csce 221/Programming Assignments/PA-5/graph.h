#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>
#include <list>
#include <queue>
#include <sstream>
#include <fstream>

using namespace std;

//edits to this are likely not needed
template <class T>
struct Vertex
{
  T label; // unique int for a vertex
  vector<T> adj_list;
  int indegree;                           // Part 2: number of nodes pointing in
  int top_num;                            // Part 2: topological sorting number
  Vertex(T l) : label(l) { top_num = 0; } //Part 1
  // You may include default constructor optionally.
};

// optional, but probably helpful
// template <class T>
// ostream& operator<<(ostream &o, Vertex<T> v){};

// std::priority_queue may take takes three template parameters: <Type, ContainerType, Functor>
// syntax for custom compare functor
// Refer the instructions PDF last section for more information

template <class T>
class VertexCompare
{
public:
  bool operator()(Vertex<T> v1, Vertex<T> v2)
  {
    //todo - implement here
    return (v1.top_num > v2.top_num);
  }
};

template <class T>
class Graph
{
private:
  //c++ stl hash table
  unordered_map<T, Vertex<T>> node_set;
  //Use other data fields if needed
public:
  Graph(){

  };
  //No modification needed to default constructor. Can be used optionally if needed.
  ~Graph(){}; //No modification needed to destructor. Can be used optionally if needed.

  // build a graph - refer the instructions PDF for more information.
  void buildGraph(istream &input)
  {
    T data;
    T lvl;
    while (input >> lvl)
    {
      Vertex<T> v(lvl);
      string string_val;
      getline(input, string_val);
      stringstream sstream(string_val);
      while (sstream >> data)
      {
        v.adj_list.push_back(data);
      }
      sstream.clear();
      node_set.insert({lvl, v});
    }
  }

  // display the graph into o - refer the instructions PDF for more information.
  void displayGraph(ostream &o)
  {
    for (auto x = node_set.begin(); x != node_set.end(); x++)
    {
      T list = x->first;
      o << list << " : ";
      Vertex<T> vec = x->second;
      for (int x = 0; x < vec.adj_list.size(); x++)
      {
        o << vec.adj_list.at(x) << " ";
      }
      o << endl;
    }
  }

  //return the vertex at label, else throw any exception  - refer the instructions PDF for more information.
  Vertex<T> at(T label)
  {
    return node_set.at(label);
  }

  //return the graph size (number of verticies)
  int size()
  {
    int size = 0;
    for (auto x = node_set.begin(); x != node_set.end(); x++)
    {
      size++;
    }
    return size;
  }

  // topological sort
  // return true if successful, false on failure (cycle)
  bool topological_sort()
  {
    queue<Vertex<T>> que;
    int final = 0;
    for (auto i = node_set.begin(); i != node_set.end(); i++)
    {
      Vertex<T> v = i->second;
      if (v.indegree == 0)
      {
        que.push(v);
      }
    }
    while (!que.empty())
    {
      Vertex<T> v1 = que.front();
      que.pop();
      node_set.at(v1.label).top_num = final++;
      for (int x = 0; x < v1.adj_list.size(); x++)
      {
        T value = v1.adj_list[x];
        if (--node_set.at(value).indegree == 0)
        {
          que.push(node_set.at(value));
        }
      }
    }
    return (final == this->size());

  }; // Part 2

  // find indegree
  void compute_indegree()
  {
    for (auto x = node_set.begin(); x != node_set.end(); x++)
    {
      x->second.indegree = 0;
    }
    for (auto y = node_set.begin(); y != node_set.end(); y++)
    {
      Vertex<T> vec = y->second;
      for (int y = 0; y < vec.adj_list.size(); y++)
      {
        node_set.at(vec.adj_list[y]).indegree++;
      }
    }
  }; // Part 2

  // print topological sort into o
  //  if addNewline is true insert newline into stream
  void print_top_sort(ostream &o, bool addNewline = true)
  {
    //TODO - implement things here
    priority_queue<Vertex<T>, vector<Vertex<T>>, VertexCompare<T>> que;
    for (auto x = node_set.begin(); x != node_set.end(); x++)
    {
      que.push(x->second);
    }
    while (!que.empty())
    {
      o << que.top().label << " ";
      que.pop();
    }
    if (addNewline)
    {
      o << '\n';
    };
  }; // Part 2
};

#endif
