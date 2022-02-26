#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "School.h"
#include "AttendanceRecord.h"

using std::string, std::stoi, std::ostream, std::ifstream, std::istringstream, std::endl, std::cout;

// one method is provided to students; students implement all other methods
School::School() : courses(), students() {}
void School::addStudents(string filename)
{
  ifstream ifs(filename);
  if (!ifs.is_open())
  {
    throw std::invalid_argument("addStudents: can't open file");
  }
  while (!ifs.eof())
  {
    string line;
    getline(ifs, line);
    istringstream ss(line);
    string uin;
    getline(ss, uin, ',');
    string name;
    getline(ss, name);
    if (!ss.fail())
    {
      Student student(uin, name);
      bool exists = false;
      for (Student s : students)
      {
        if (s == student)
        {
          exists = true;
          break;
        }
      }
      if (!exists)
      {
        students.push_back(student);
      }
    }
  }
}
void School::addCourses(std::string filename)
{
  ifstream ifs(filename);
  if (!ifs.is_open())
  {
    throw std::invalid_argument("addStudents: can't open file");
  }

  string line;
  while (getline(ifs, line))
  {
    istringstream ss(line);
    string id;
    getline(ss, id, ',');
    // Start Time
    string start_hours;
    getline(ss, start_hours, ':');
    string start_mins;
    getline(ss, start_mins, ',');
    Date Start_Date(stoi(start_hours), stoi(start_mins));
    // End Time
    string end_hours;
    getline(ss, end_hours, ':');
    string end_mins;
    getline(ss, end_mins, ',');
    Date End_Date(stoi(end_hours), stoi(end_mins));
    // title
    string title;
    getline(ss, title);
    Course course(id, title, Start_Date, End_Date);
    courses.push_back(course);
  }
}
unsigned int School::addAttendanceData(std::string filename)
{
  unsigned int counter = 0;
  ifstream ifs(filename);
  if (!ifs.is_open())
  {
    throw std::invalid_argument("File cannot be opened");
  }
  while (!ifs.eof())
  {
    string line;
    getline(ifs, line);
    if (line.length() == 0)
    {
      break;
    }
    istringstream ss(line);
    string year;
    getline(ss, year, '-');
    string month;
    getline(ss, month, '-');
    string day;
    getline(ss, day, ' ');
    string hour;
    getline(ss, hour, ':');
    string min;
    getline(ss, min, ':');
    string sec;
    getline(ss, sec, ',');
    string courseId;
    getline(ss, courseId, ',');
    string studentId;
    getline(ss, studentId);
    Date date(stoi(year), stoi(month), stoi(day), stoi(hour), stoi(min), stoi(sec));
    if (date.isValid() && isEnrolled(studentId) && CourseFound(courseId))
    {
      try
      {
        unsigned int i;
        for (unsigned int j = 0; j < courses.size(); j++)
        {
          if (courseId == courses[j].getID())
          {
            i = j;
            break;
          }
        }
        courses[i].addAttendanceRecord(AttendanceRecord(courseId, studentId, date));
      }
      catch (const std::invalid_argument &e)
      {
        counter++;
      }
    }
    else
    {
      counter++;
    }
    ss.clear();
  }
  return counter;
}

void School::listCourses(std::ostream &os) const
{
  int start_hour;
  int end_hour;
  int start_min;
  int end_min;
  if (courses.size() == 0)
  {
    os << "No courses" << endl;
  }
  else
  {
    for (size_t i = 0; i < courses.size(); i++)
    {
      start_hour = courses.at(i).getStartTime().getHour();
      end_hour = courses.at(i).getEndTime().getHour();
      start_min = courses.at(i).getStartTime().getMin();
      end_min = courses.at(i).getEndTime().getMin();
      os << courses.at(i).getID() << ",";
      //start hour
      if (start_hour <= 9)
      {
        os << "0" << start_hour << ":";
      }

      else
      {
        os << start_hour << ":";
      }
      //start min
      if (start_min <= 9)
      {
        os << "0" << start_min << ",";
      }
      else
      {
        os << start_min << ",";
      }
      // end hour
      if (end_hour <= 9)
      {
        os << "0" << end_hour << ":";
      }
      else
      {
        os << end_hour << ":";
      }
      // end min
      if (end_min <= 9)
      {
        os << "0" << end_min << ",";
      }
      else
      {
        os << end_min << ",";
      }
      os << courses.at(i).getTitle() << endl;
    }
  }
}

bool School::isEnrolled(std::string student_id) const
{
  for (size_t i = 0; i < students.size(); i++)
  {
    if (student_id == students[i].get_id())
    {
      return true;
    }
  }
  return false;
}

void School::listStudents(std::ostream &os) const
{
  //TODO:
  if (students.size() == 0)
  {
    os << "No students" << endl;
  }
  else
  {
    for (size_t i = 0; i < students.size(); i++)
    {
      os << students[i]; //
    }
  }
}

void School::outputCourseAttendance(std::ostream &os, std::string course_id) const
{
  for (auto c : courses)
  {
    if (c.getID() == course_id)
    {
      c.outputAttendance(os);
      break;
    }
  }
}

void School::outputStudentAttendance(std::ostream &os, std::string student_id, std::string course_id) const
{
  for (auto c : courses)
  {
    // traversal for students vector
    if (c.getID() == course_id)
    {
      c.outputAttendance(os, student_id);
      break;
    }
  }
}

bool School::CourseFound(string course_id)
{
  bool coursefound = false;
  for (unsigned int i = 0; i < courses.size(); i++)
  {
    if (course_id == courses[i].getID())
    {
      coursefound = true;
      break;
    }
  }
  return coursefound;
}