#include <iostream>
#include <string>
#include "Course.h"
#include "Section.h"
#include "CourseOfferings.h"

using std::string, std::endl;

/* TODO-STUDENT: implement the Rule of Three member functions:
** copy constructor, copy assignment operator, destructor
*/

CourseOfferings::CourseOfferings(const CourseOfferings &CourseObject) // Copy Constructor
{
	semester = CourseObject.semester;
	year = CourseObject.year;
	course = CourseObject.course;
	nbSections = CourseObject.getNumberSections();
	capacity = CourseObject.getSectionListCapacity();
	sectionList = new Section[capacity]; // allocating sectionList mem size capacity
	for (size_t x = 0; x < nbSections; x++)
	{
		sectionList[x] = CourseObject.sectionList[x];
	}
}

CourseOfferings::~CourseOfferings() // destructor
{
	delete[] sectionList;
	sectionList = nullptr;
	capacity = 0;
	nbSections = 0;
}

CourseOfferings &CourseOfferings::operator=(const CourseOfferings &CourseObject)
{

	// You will declare and define a copy assignment operator (operator=). This is the code that will be executed  when doing assignments of CourseOffering objects such as below:
	// CourseOfferings co1( /*...*/);
	// CourseOfferings co2(/*...*/);
	// co1 = co2;
	// this will automatically invoke course1.operator+(course2)

	if (this != &CourseObject)
	{
		delete[] sectionList;			  // Deallocating sectionList mem
		semester = CourseObject.semester; //
		year = CourseObject.year;		  //
		course = CourseObject.course;	  //
		nbSections = CourseObject.getNumberSections();
		capacity = CourseObject.getSectionListCapacity();
		sectionList = new Section[capacity]; // allocating mem to sectionList
		for (size_t x = 0; x < nbSections; x++)
		{
			sectionList[x] = CourseObject.sectionList[x];
		}
	}
	return (*this);
}

/* TODO-STUDENT: implement this function
** Parameters: none
** Return value: none
** Functionality: It updates the object to increase the capacity
**                of the attribute member sessionList.
**                If capacity is zero, it becomes one.
**                If capacity is greater than zero, it is doubled.
*/
void CourseOfferings::increaseSectionListCapacity()
{
	if (capacity == 0) //If capacity is zero, it becomes one.
	{
		capacity = 1;
	}
	else
	{
		capacity = capacity * 2; //  If capacity is greater than zero, it is doubled.
	}
	// It updates the object to increase the capacity **of the attribute member sessionList.
	Section *section_object = new Section[capacity];
	if (section_object == nullptr)
	{
		throw std::runtime_error("Cannot allocate memory bc section_object == nullptr");
	}
	for (size_t x = 0; x < nbSections; x++)
	{
		section_object[x] = sectionList[x];
	}
	delete[] sectionList; // bc we have a new earlier
	sectionList = section_object;
	section_object = nullptr;
}

/* TODO-STUDENT: implement this function
** Parameters: none
** Return value: none
** Functionality: it updates the object so that nbSessions becomes zero.
*/
void CourseOfferings::clearSections()
{
	// student will implement this one
	nbSections = 0;
}

/* TODO-STUDENT: implement this function
** Parameters: none
** Return value: none
** Functionality: it updates the object so that nbSessions and capacity become zero,
**                updating sessionList accordingly.
*/
void CourseOfferings::fullClearSections()
{
	// student will implement this one

	// Public member function that fully deallocates sectionList from heap memory.
	nbSections = 0;
	capacity = 0;
}

/* TODO-STUDENT: implement this function
*/
std::ostream &operator<<(std::ostream &os, const CourseOfferings &co)
{
	// student will implement this one
	//os  = output stream
	os << co.getSectionList(); // putting all the section list data in the output stream.
	return os;
}

CourseOfferings::CourseOfferings(Course c, unsigned int year, char semester)
	: course(c), year(year), semester(semester)
{
	capacity = 0;
	nbSections = 0;
	sectionList = nullptr;
}

CourseOfferings::CourseOfferings(unsigned int year, char semester, const CourseOfferings &co) : CourseOfferings(co)
{
	this->year = year;
	this->semester = semester;
}

void CourseOfferings::addSection(const Section &s)
{
	if (nbSections == capacity)
	{
		increaseSectionListCapacity();
	}
	sectionList[nbSections++] = s;
}

size_t CourseOfferings::findSection(string section)
{
	for (size_t i = 0; i < nbSections; i++)
	{
		if (sectionList[i].getId() == section)
		{
			return i;
		}
	}
	return npos;
}

void CourseOfferings::replaceInstructor(string section, string instructor)
{
	size_t idx = findSection(section);
	if (idx == npos)
	{
		throw std::invalid_argument("section not found");
	}
	else
	{
		sectionList[idx].setInstructor(instructor);
	}
}

string CourseOfferings::getInstructor(string section)
{
	size_t idx = findSection(section);
	if (idx == npos)
	{
		throw std::invalid_argument("section not found");
	}
	else
	{
		return sectionList[idx].getInstructor();
	}
}

bool operator==(const CourseOfferings &lhs, const CourseOfferings &rhs)
{
	if (!(lhs.getYear() == rhs.getYear() && lhs.getSemester() == rhs.getSemester() && lhs.getCourse().getId() == rhs.getCourse().getId() && lhs.getCourse().getTitle() == rhs.getCourse().getTitle() && lhs.getNumberSections() == rhs.getNumberSections() && lhs.getSectionListCapacity() == rhs.getSectionListCapacity()))
	{
		return false;
	}

	// checking sections
	for (size_t i = 0; i < lhs.getNumberSections(); i++)
	{
		Section ls = lhs.getSectionList()[i];
		Section rs = rhs.getSectionList()[i];
		if (!(ls.getId() == rs.getId() && ls.getTime() == rs.getTime() && ls.getLocation() == rs.getLocation() && ls.getInstructor() == rs.getInstructor()))
		{
			return false;
		}
	}
	return true;
}
