#ifndef COURSE_OFFERINGS_H
#define COURSE_OFFERINGS_H

#include <string>
#include "Course.h"
#include "Section.h"

class CourseOfferings
{
  const size_t npos = -1;

  Course course;
  unsigned int year;
  char semester;
  size_t nbSections;
  size_t capacity;
  Section *sectionList;

  size_t findSection(std::string section);

  // private member functions STUDENT will implement
  void increaseSectionListCapacity();

public:
  // RULE OF THREE
  // TODO-STUDENT: add the declaration of the Rule of Three member functions

  CourseOfferings(const CourseOfferings &CourseObject);                //copy constructor
  CourseOfferings &operator=(const CourseOfferings &tempCourseObject); // my_string copy assignment
  ~CourseOfferings();                                                  //destructor

  // other constructors and methods provided in the starter code
  CourseOfferings() : course(), year(0), semester('X'), nbSections(0),
                      capacity(0), sectionList(nullptr) {}
  CourseOfferings(Course c, unsigned int year, char semester);
  CourseOfferings(unsigned int i, char semester, const CourseOfferings &c);
  void addSection(const Section &section);
  std::string getInstructor(std::string section);
  void replaceInstructor(std::string sectionId, std::string instructor);

  // public member functions STUDENT will implement
  void clearSections();
  void fullClearSections();

  // getters
  unsigned int getYear() const { return year; }
  char getSemester() const { return semester; }
  Course getCourse() const { return course; }
  size_t getNumberSections() const { return nbSections; }
  Section *getSectionList() const { return sectionList; }
  size_t getSectionListCapacity() const { return capacity; }
};

// non-member functions
std::ostream &operator<<(std::ostream &os, const CourseOfferings &c);

bool operator==(const CourseOfferings &lhs, const CourseOfferings &rhs);

#endif