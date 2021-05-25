#include <iostream>
#include <string>
#include <fstream>
#include "Record.h"

using namespace std;

void Record::set_title(string title) { this->title = title; }
void Record::set_author(string author) { this->author = author; }
void Record::set_ISBN(string ISBN) { this->ISBN = ISBN; }
void Record::set_year(string year) { this->year = year; }
void Record::set_edition(string edition) { this->edition = edition; }
string Record::get_title() const { return title; }
string Record::get_author() const { return author; }
string Record::get_ISBN() const { return ISBN; }
string Record::get_year() const { return year; }
string Record::get_edition() const { return edition; }

// a) input operator>> to enter the record from the input file Book.txt.
// b) output operator<< to print the record on screen.
// c) equal-to operator== to compare two records by title, author’s name and ISBN
// bool operator==(const Record& r1, const Record& r2)

istream &operator>>(istream &input, Record &r)
{
    string title;
    string author;
    string ISBN;
    string year;
    string edition;
    getline(input, title);
    getline(input, title);
    getline(input, author);
    getline(input, ISBN);
    getline(input, year);
    getline(input, edition);
    r.set_title(title);
    r.set_author(author);
    r.set_ISBN(ISBN);
    r.set_year(year);
    r.set_edition(edition);
    return input;
};

std::ostream &operator<<(std::ostream &os, Record &r)
{
    os << r.get_title() << "\n";
    os << r.get_author() << "\n";
    os << r.get_ISBN() << "\n";
    os << r.get_year() << "\n";
    os << r.get_edition() << "\n";
    return os;
}

bool operator==(const Record &r1, const Record &r2)
{
    if (r1.get_title() == r2.get_title() && r1.get_author() == r2.get_author() && r1.get_ISBN() == r2.get_ISBN())
    {
        return true;
    }
    return false;
};
