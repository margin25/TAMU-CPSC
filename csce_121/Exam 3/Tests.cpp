#include <iostream>
#include <string>
#include "LinkedList.h"

int main()
{
    // TODO(student): the rest of the Tests
    LinkedList list;
    // LinkedList t1, t2;
    list.find_last_of(0);
    list.empty();
    list.clear();
    list.head();
    list.remove_duplicates();
    list.contains(2);
    list.push_back(8);
    list.remove_duplicates();
    list.push_back(6);
    list.remove_duplicates();
    list.push_back(7);
    list.remove_duplicates();
    list.push_back(3);
    list.push_back(5);
    list.push_back(3);
    list.push_back(0);
    list.push_back(9);
    // LinkedList list2 = list; // Copy constructor is called here
    // t2 = t1; // Copy Assignment Operator Called;
    list.head();
    list.contains(6);
    list.size();
    list.length_max_decreasing();
    list.remove_duplicates();
    list.find_last_of(5);
    list.push_back(1);
    list.push_back(7);
    list.push_back(2);
    list.push_back(7);
    list.push_back(7);
    list.push_back(3);
    list.push_back(7);
    list.push_back(7);
    list.push_back(4);
    list.push_back(7);
    list.push_back(5);
    if (list.contains(6))
    {
        std::cout << "true" << std::endl;
    }
    else
    {
        std::cout << "false" << std::endl;
    }

    list.remove_duplicates();
    //list.printList();
    std::cout << list.size() << std::endl;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(3);
    list.push_back(2);
    list.remove(3);
    list.push_back(1);
    list.empty();
    list.clear();
    list.remove_duplicates();
    // list.printList();
    list.push_back(11);
    list.push_back(9);
    list.push_back(3);
    list.push_back(8);
    list.push_back(7);
    list.push_back(5);
    list.push_back(2);
    list.push_back(1);
    list.push_back(4);
    list.push_back(3);
    list.push_back(9);
    list.push_back(8);
    list.remove_duplicates();
    LinkedList list2;
    list2.push_back(1);
    list2.remove_duplicates();
    list2.length_max_decreasing();
    list2.size();
    LinkedList list3;
    list3.push_back(1);
    list3.push_back(1);
    list3.push_back(1);
    list3.size();
    list3.length_max_decreasing();
    list3.remove_duplicates();
    LinkedList list4;
    list4.push_back(4);
    list4.push_back(3);
    list4.push_back(2);
    list4.push_back(1);
    list4.length_max_decreasing();
    list4.size();
    list4.remove_duplicates();
    list4.size();
    LinkedList list5;
    list5.size();
    LinkedList list6;
    list6.push_back(8);
    list6.push_back(6);
    list6.push_back(7);
    list6.push_back(5);
    list6.push_back(3);
    list6.push_back(0);
    list6.push_back(9);
    list6.length_max_decreasing();
    list6.size();
    list6.remove_duplicates();
    list6.size();
    list6.head();
    LinkedList list7;
    list7.push_back(5);
    list7.push_back(4);
    list7.push_back(3);
    list7.push_back(4);
    list7.push_back(5);
    list7.push_back(5);
    list7.push_back(4);
    list7.push_back(3);
    list7.push_back(2);
    list7.push_back(1);
    list7.push_back(10);
    list7.length_max_decreasing();
    list7.size();
    list7.remove_duplicates();
    list7.remove_duplicates();
    LinkedList list8;
    list8.push_back(3);
    list8.remove_duplicates();
    list8.size();
    list8.head();
    list8.length_max_decreasing();
    LinkedList list9;
    list9.push_back(10);
    list9.push_back(9);
    list9.push_back(10);
    list9.push_back(9);
    list9.length_max_decreasing();
    LinkedList list10;
    list10.push_back(4);
    list10.push_back(4);
    list10.remove_duplicates();

    //list.printList();
    // list.push_back(11);
    // std::cout << list.length_max_decreasing() << std::endl;
    // std::cout << list.find_last_of(2) << std::endl;
    // list.remove(0);
    // list.head();
    // list.printList();
    return 0;
}
