// sorting items from the heaviest to lightest
// by selecting the heaviest item at each time

#include <iostream>
#include <vector>

using namespace std;

int comparisons = 0;

ostream &operator<<(ostream &out, vector<int> &v)
{
  for (int x = 0; x < v.size(); x++)
  {
    if (x == (v.size() - 1))
    {
      out << v[x];
    }
    else
    {
      out << v[x] << ",";
    }
  }
  return out;
}

void sort_heaviest(vector<int> &v)
{
  //selection sort algo
  for (int i = 0; i < v.size() - 1; i++)
  {
    int min = i;
    for (int j = i + 1; j < v.size(); j++)
    {
      comparisons++;
      if (v[j] > v[min])
      {
        min = j;
      }
      //swapping done here
      int temp = v[min];
      v[min] = v[i];
      v[i] = temp;
    }
  }
}

int main()
{

  cout << "//////Test 2 for vector v ///////////////////////////////" << endl;
  vector<int> v{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

  cout << "initial vector v:\n";
  // use overloaded output operator to display vector's elements
  // use comma to separate the vector's elements
  cout << v;
  cout << endl;
  // call the sorting function for vector v
  sort_heaviest(v);
  cout << "# of comparisons to sort v: " << comparisons << endl
       << endl;
  cout << "vector v after sorting:\n";
  // use overloaded output operator to display elements of sorted vector
  // use comma to separate the vector's elements
  cout << v;
  cout << endl;

  cout << "//////Test 2 for vector v1 ///////////////////////////////" << endl;

  vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  cout << "initial vector v1:\n";
  // use overloaded output operator to display vector's elements
  // use comma to separate the vector's elements
  cout << v1;
  cout << endl;
  // call the sorting function for vector v2
  sort_heaviest(v1);
  cout << "# of comparisons to sort v1: " << comparisons << endl
       << endl;
  cout << "vector v1 after sorting:\n";
  // use overloaded output operator to display elements of sorted vector
  // use comma to separate the vector's elements
  cout << v1;
  cout << endl;
  return 0;
}
