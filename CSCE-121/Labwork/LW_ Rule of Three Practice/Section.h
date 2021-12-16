#ifndef SECTION_H
#define SECTION_H

#include <string>

class Section {
	std::string id = "n/a";
	std::string time = "n/a";
	std::string location = "n/a";
	std::string instructor = "n/a";
public:
	Section() {}
	Section(std::string id, std::string time, std::string loc, std::string name) 
			: id(id), time(time), location(loc), instructor(name) {}

	std::string getId() const { return id; }
	void setId(std::string id) {this->id = id; }
	std::string getTime() const { return time; }
	void setTime(std::string t)  { time = t; }
	std::string getLocation() const { return location; }
	void setLocation(std::string l) { location = l;}
	std::string getInstructor() const { return instructor;}
	void setInstructor(std::string instr) { instructor = instr;}
};

#endif