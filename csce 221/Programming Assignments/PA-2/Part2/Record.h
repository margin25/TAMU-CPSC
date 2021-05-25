#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#ifndef Record_H
#define Record_H
class Record
{
private:
    string title;
    string author;
    string ISBN;
    string year;
    string edition;
    Record *link;

public:
    void set_title(string title);
    void set_author(string author_num);
    void set_ISBN(string ISBN);
    void set_year(string year);
    void set_edition(string edition);
    string get_title() const;
    string get_author() const;
    string get_ISBN() const;
    string get_year() const;
    string get_edition() const;
};

istream &operator>>(istream &input, Record &r);
ostream &operator<<(ostream &os, Record &r);
bool operator==(const Record &r1, const Record &r2);

#endif