#include <iostream>
#include <string>
#include "Course.h"
#include "CourseOfferings.h"
#include "Section.h"

using std::string, std::cout, std::endl;

int main() {
  Course csce121("CSCE121", 
  	"Introduction to Program Design and Concepts");

  Section section597("597", "N/A", "web-based", "Michael Moore");
  Section section521("521", "TR 1:30 2:45 pm", "ONLINE", "Philip Ritchey");
  Section section512("512", "MW 5:35 - 6:50 pm", "ZACH 310", "Paul Taele");
  Section section508("508", "TR 8:00 - 9:15 am", "ONLINE", "Dilma Da Silva");  

  CourseOfferings fall20(csce121, 2020, 'C');
  fall20.addSection(section597);
  fall20.addSection(section521);
  fall20.addSection(section512);
  fall20.addSection(section508);

  cout << "fall20 object: " << endl << fall20 << endl;

  CourseOfferings spring21(2021, 'A', fall20);
  cout << "spring21 object: " << endl << spring21 << endl;
  spring21.replaceInstructor("521", "Andrew Nemac");
  spring21.replaceInstructor("508", "Shawn Lupoli");
  cout << "Fall 20 instrutor for section 521 is " 
        << fall20.getInstructor("521")  << endl;
  cout << "Spring 21 instructor for section 521 is " 
      << spring21.getInstructor("521") << endl;
  cout << "Fall 20 instrutor for section 508 is " 
      << fall20.getInstructor("508")  << endl;
  cout << "Spring 21 instructor for section 508 is " 
      << spring21.getInstructor("508") << endl;

  Section section528("528", "5:00 - 6:15 pm", "ONLINE", "Seth Polsley");
  spring21.addSection(section528);
  cout << "After addSection() spring21 now has " 
        << spring21.getNumberSections() << " sections." << endl;

  fall20.clearSections();
  cout << "After clearSections() fall20 now has " 
        << fall20.getNumberSections() << " sections and capacity is " 
        << fall20.getSectionListCapacity() << endl;

  fall20.fullClearSections();
  cout << "After fullClearSections() fall20 now has " 
        << fall20.getNumberSections() << " sections and capacity is " 
        << fall20.getSectionListCapacity() << endl;
  return 0;
}
