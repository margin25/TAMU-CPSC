#ifndef LIBRARY_H
#define LIBRARY_H
#include "Record.h"
#include "TemplatedDLList.h"
#include <vector>
#include <cctype>
using namespace std;

class Library
{
public:
    vector<Record> search(std::string title);
    string prompt_string(std::string prompt);
    string prompt_title();
    int prompt_menu(vector<string> options);
    Record prompt_record();
    char prompt_yes_no();
    bool add_record(Record b);
    void remove_record(Record b);
    int import_database(string filename);
    int export_database(std::string filename);
    void print_database();

private:
    std::vector<DLList<Record>> book_db = vector<DLList<Record>>(26);
};

#endif