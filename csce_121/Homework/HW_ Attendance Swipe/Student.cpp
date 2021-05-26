#include <iostream>
#include <string>
#include "Student.h"
#include <fstream>
#include <sstream>

using std::string, std::ostream, std::ifstream, std::istringstream, std::endl, std::cout;

Student::Student(std::string student_id, std::string name) : id(student_id), name(name), course_ids({})
{
}

std::ostream &operator<<(std::ostream &os, const Student &s)
{
    os << s.get_id() << ',' << s.get_name() << endl;
    return os;
}

std::string Student::get_id() const
{
    return id;
}
std::string Student::get_name() const
{
    return name;
}

void Student::addCourse(std::string course_id)
{
    //If the course being added already exists, throws std::invalid_argument
    for (size_t i = 0; i < course_ids.size(); i++)
    {
        if (course_id == course_ids[i])
        {
            throw std::invalid_argument("Invalid Argument!");
        }
    }
    course_ids.push_back(course_id);
}

void Student::listCourses(std::ostream &os) const
{
    //TODO:
    os << "Courses for " << id << endl;
    if (course_ids.size() == 0)
    {
        os << "No courses" << endl;
    }
    else
    {
        for (size_t i = 0; i < course_ids.size(); i++)
        {
            os << course_ids[i] << endl;
        }
    }
}

/* int main()
{
    Student moo = Student("1231122", "Mualla");
    moo.addCourse("121");
    moo.addCourse("100");
    moo.addCourse("300");
    moo.listCourses(cout); //cout = ostream variable
    return (1);
} */