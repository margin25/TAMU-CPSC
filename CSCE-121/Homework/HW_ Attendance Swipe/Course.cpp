#include <iostream>
#include <string>
#include "Course.h"
#include "Date.h"
#include "AttendanceRecord.h"

using std::string, std::ostream, std::endl, std::cout;

Course::Course(std::string id, std::string title, Date startTime, Date endTime) : id(id), title(title), startTime(startTime), endTime(endTime), attendanceRecords()
{
}

std::string Course::getID() const
{
    return (id);
}

std::string Course::getTitle() const
{
    return (title);
}

Date Course::getStartTime() const
{
    return (startTime);
}
Date Course::getEndTime() const
{
    return (endTime);
}

void Course::addAttendanceRecord(AttendanceRecord ar)
{
    bool start_checker;
    bool end_checker;
    //start checker
    if (ar.getDate().getHour() > startTime.getHour())
    {
        start_checker = true;
    }
    else if (ar.getDate().getHour() == startTime.getHour())
    {
        if (ar.getDate().getMin() > startTime.getMin())
        {
            start_checker = true;
        }
        else if (ar.getDate().getMin() == startTime.getMin())
        {
            if (ar.getDate().getSec() >= startTime.getSec())
            {
                start_checker = true;
            }
        }
    }
    //end checker
    if (ar.getDate().getHour() < endTime.getHour())
    {
        end_checker = true;
    }
    else if (ar.getDate().getHour() == endTime.getHour())
    {
        if (ar.getDate().getMin() < endTime.getMin())
        {
            end_checker = true;
        }
        else if (ar.getDate().getMin() == endTime.getMin())
        {
            if (ar.getDate().getSec() < endTime.getSec())
            {
                end_checker = true;
            }
        }
    }
    if (!start_checker || !end_checker)
    {
        throw std::invalid_argument("Invalid Argument");
    }
    else
    {
        attendanceRecords.push_back(ar);
    }
}

void Course::outputAttendance(std::ostream &os) const //used in output course attendance
{
    if (attendanceRecords.empty())
    {
        os << "No records" << endl;
    }
    else
    {
        for (unsigned int i = 0; i < attendanceRecords.size(); i++)
        {
            os << attendanceRecords.at(i).getDate().getDateTime() << ',' << attendanceRecords.at(i).getCourseID() << ',' << attendanceRecords.at(i).getStudentID() << endl;
        }
    }
}

void Course::outputAttendance(std::ostream &os, std::string student_id) const
{
    if (attendanceRecords.empty())
    {
        os << "No records" << endl;
    }
    else
    {
        bool isFound = false;
        for (unsigned int i = 0; i < attendanceRecords.size(); i++)
        {
            if (student_id == attendanceRecords.at(i).getStudentID())
            {
                isFound = true;
                os << attendanceRecords.at(i).getDate().getDateTime() << ',' << attendanceRecords.at(i).getCourseID() << ',' << attendanceRecords.at(i).getStudentID() << endl;
            }
        }
        if (attendanceRecords.size() != 0 && !isFound)
        {
            os << "No records " << endl;
        }
    }
}

std::ostream &operator<<(std::ostream &os, const Course &c)
{
    return os;
}
