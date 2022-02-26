#ifndef COURSE_DESCRIPTION_H
#define COURSE_DESCRIPTION_H

#include <string>

class Course {
  std::string id = "";
  std::string title = "";
public:
  Course() {}
  Course(std::string id, std::string title) :
        id(id), title(title) {}

  std::string getId() const { return id; }
  std::string getTitle() const {return title; }
};

#endif