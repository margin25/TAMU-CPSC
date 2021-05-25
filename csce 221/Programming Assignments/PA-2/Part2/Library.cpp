#include "Library.h"
#include "TemplatedDLList.h"
#include <fstream>
using namespace std;

std::vector<Record> Library::search(std::string title)
{
    // The user will be asked to input the title to start searching.
    // If the program does not find a book with the requested title,
    // the user will be asked to add this title to the database
    // and he/she needs to provide all the required book information.
    // If more than one book have the same title and author’s name, these records will be displayed,
    // and the user needs to decide which book edition to select.
    vector<Record> records_match;
    int index = toupper(title[0]) - 65;
    DLList<Record> recordlist = book_db[index];
    DLListNode<Record> *current = recordlist.first_node();
    while (current != recordlist.after_last_node())
    {
        if (title == current->obj.get_title())
        {
            records_match.push_back(current->obj);
        }
        current = current->next;
    }
    return records_match;
}

string Library::prompt_string(string prompt) // taking in string as input
{
    cout << prompt; // displaying string to user
    string input = "";
    getline(cin, input); // capture user input from cin
    cout << "\n";
    return input; // return user input
}

string Library::prompt_title()
{
    return prompt_string("Title: ");
}

int Library::prompt_menu(vector<string> options)
{
    /* 
    This test depends on *prompt_menu() prompt_menu() 
    should take in a vector of strings, show these 
    strings to the user, then take in a number for 
    their input, and return the corresponding index in the vector.
    Example case: *function input: {"Harry Potter", "Chronicles of Narnia",
    "C++ Programming Principles", "Add new record"} *possible cout output: 
    "Please select an option 1. Harry Potter 2. Chronicles of Narnia 3. 
    C++ Programming Principles 4. Add new Record" * user input from cin: 
    "3" * function's return value: 2
    */
    int user_input = 0;
    for (int x = 0; x < options.size(); x++)
    {
        cout << x + 1 << ". " << options[x] << "\n";
    }
    cout << "Enter option: ";
    cin >> user_input;
    int return_val = user_input - 1;
    return return_val;
}

Record Library::prompt_record()
{
    /*
 This test depends on *prompt_record() *get_author() *get_ISBN() *get_year() *get_title() *get_edition() 
 In order to pass this test your prompt_record() should take in five inputs from the user 
 and create a record with those five inputs. Before passing this test, make sure your record 
 accessor and mutator functions are not too restrictive. 
 For example, set_ISBN() should set any valid string, not just those with 13 characters and only numbers.
 */
    Record r;
    string title = prompt_string("Title: ");
    r.set_title(title);
    string author = prompt_string("Author: ");
    r.set_author(author);
    string ISBN = prompt_string("ISBN: ");
    r.set_ISBN(ISBN);
    string year = prompt_string("Year: ");
    r.set_year(year);
    string edition = prompt_string("Edition: ");
    r.set_edition(edition);
    return r;
}

char Library::prompt_yes_no()
{
    /* 
    your prompt_yes_no() function takes in user input, and returns the right character. 
    Make sure prompt_yes_no() and returns Y or N based on whether the user puts in a Y or an N
    */
    char user_input;
    cout << "Yes(Y) or No(N): ";
    cin >> user_input;
    if (user_input == 'Y' || user_input == 'y')
    {
        return 'Y';
    }
    else if (user_input == 'N' || user_input == 'n')
    {
        return 'N';
    }
    else
        return 'N';
}

bool Library::add_record(Record b)
{
    // Based on the first character of the record's title,
    // find the index of book_db which corresponds to that
    // character and insert the book into the linked list at that index of book_db.
    // For example, the books "C++ Programming Principles" and "clifford the Big Red Dog"
    // should be inserted in the linked list which is in the 2 index of book_bd.
    // Another example "Harry Potter" will go in the list in the 7 index since H is the 8th letter
    // of the alphabet. Furthermore, if the function's
    // argument is equal to a record already in the list, do not add it to the list.

    // return true if it is added and false otherwise

    if (b.get_title().empty() || b.get_ISBN().empty() || b.get_author().empty()) //invalid record entry
    {
        return false;
    }
    else // valid record entry
    {
        int index = toupper(b.get_title()[0]) - 65;
        DLList<Record> *record_list = &book_db[index];
        DLListNode<Record> *current = record_list->first_node();

        while (current != record_list->after_last_node())
        {
            if (current->obj == b)
            {
                return false;
            }
            current = current->next;
        }
        record_list->insert_first(b);
        return true;
    }
}

void Library::remove_record(Record b)
{
    int index = toupper(b.get_title()[0]) - 65;
    DLList<Record> *record_list = &book_db[index];
    DLListNode<Record> *current = record_list->first_node();
    while (current != record_list->after_last_node())
    {
        if (b.get_title() == current->obj.get_title() && b.get_author() == current->obj.get_author() && b.get_ISBN() == current->obj.get_ISBN() && b.get_year() == current->obj.get_year() && b.get_edition() == current->obj.get_edition())
        {
            record_list->remove_before(*current->next);
        }
        current = current->next;
    }
}

/* 
Read the contents of a properly formatted file of records (such as Book.txt) 
into your program, create a record for each book in the file, then add each book 
to the correct linked list in book_db
*/
int Library::import_database(string filename)
{
    ifstream fin(filename);
    int counter = 0;
    if (!fin.is_open())
        throw "didn't open";
    Record rec;
    while (fin >> rec)
    {
        if (add_record(rec))
            counter++;
    }

    return counter;
}
/* 
Write all of the contents of your database (all of the records from the linked lists from book_db) to 
the file whose name is specified in the function's argument
*/
int Library::export_database(std::string filename)
{
    int counter = 0;
    ofstream ofs(filename);
    for (DLList<Record> x : book_db)
    {
        DLListNode<Record> *current = x.first_node();
        while (current != x.after_last_node())
        {
            ofs << current->obj << "\n";
            counter++;
            current = current->next; // i++;
        }
    }
    return counter;
}

void Library::print_database()
{
    for (DLList<Record> list : book_db)
    {
        DLListNode<Record> *curr = list.first_node();
        while (curr != list.after_last_node())
        {
            cout << curr->obj << "\n";
            curr = curr->next;
        }
    }
}
