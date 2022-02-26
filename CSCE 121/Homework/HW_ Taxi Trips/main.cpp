#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "taxi_trips.h"
using std::string, std::ifstream, std::cin, std::cout, std::endl, std::istringstream;

int main()
{

  // TODO(student): implement
  int list_length;            //Final length we used to print stuff
  int count_error = 0;        //counts errors
  string line;                //used with istringstream and to collect data for the arrays
  ifstream inFS;              // Input file stream
  string file_name;           // Data value from file
  string ID_taxi[50000];      //initalize array that will hold taxi IDs
  double trip_miles[50000];   //initalize array that will hold trip miles
  double trip_sec[50000];     //initalize array that will hold trip seconds
  double trip_fare[50000];    //initalize array that will hold trip fare
  double trip_tip[50000];     //initalize array that will hold trip tip
  string payment_type[50000]; //initalize array that will hold payment_type
  int length = 0;
  //read in file
  cout << "Enter name of input file: "; //prompts user to input file name
  cin >> file_name;                     // User inputs file name
  inFS.open(file_name);                 // open file
  if (inFS.is_open())                   // do when file is open
  {
    while (getline(inFS, line)) // get line while file exists
    {
      istringstream inSS(line);        // read until whitespace is reached or until the stream fails
      inSS >> ID_taxi[length];         // reads in element in string "line" up until next whitespace (repeats until while condition is invalid) & inputs value into the iniatizled array
      inSS >> trip_sec[length];        // same process^
      inSS >> trip_miles[length];      // same process^
      inSS >> trip_fare[length];       // same process^
      inSS >> trip_tip[length];        // same process^
      inSS >> payment_type[length];    // same process^
      if (trip_sec[length] > 86400.00) //  Cleaning up values by "removing" values of trip secs that exceed 24 hours (24 hrs = 86400 seconds)
      {
        count_error = count_error + 1; //increase count error if trip_sec at that position is >24 hrs
        ID_taxi[length] = {};
        trip_sec[length] = {};
        trip_miles[length] = {};
        trip_fare[length] = {};
        trip_tip[length] = {};
        payment_type[length] = {};
        length = length - 1; //accounts for shift
      }
      else if (trip_miles[length] > 1500.0) //  Cleaning up values by "removing/ignoring" that exceed 1500 miles.
      {
        count_error = count_error + 1;
        ID_taxi[length] = {};
        trip_sec[length] = {};
        trip_miles[length] = {};
        trip_fare[length] = {};
        trip_tip[length] = {};
        payment_type[length] = {};
        length = length - 1;
      }
      else if ((trip_fare[length] + trip_tip[length]) > 5000.0)
      {
        count_error = count_error + 1;
        ID_taxi[length] = {};
        trip_sec[length] = {};
        trip_miles[length] = {};
        trip_fare[length] = {};
        trip_tip[length] = {};
        payment_type[length] = {};
        length = length - 1;
      }

      else if (payment_type[length] != "Cash" && payment_type[length] != "CreditCard" && payment_type[length] != "Unknown" && payment_type[length] != "NoCharge")
      {
        count_error = count_error + 1;
        ID_taxi[length] = {};
        trip_sec[length] = {};
        trip_miles[length] = {};
        trip_fare[length] = {};
        trip_tip[length] = {};
        payment_type[length] = {};
        length = length - 1;
      }
      length = length + 1; // normal increment to go to the next position in the array
    }
    list_length = length; // sets final length variable equivalent to the value of the variable we used to cycle through the valid and invalid DATA
    inFS.close();
    cout << "Number of trips: " << list_length << endl;
    cout << "Number of trips with invalid data: " << count_error << endl;
    cout << "Duration: "
         << "max " << max(trip_sec, list_length) << " min " << min(trip_sec, list_length) << " avg " << average(trip_sec, list_length) << " mode " << mode(trip_sec, list_length) << endl;
    cout << "Distance: "
         << "max " << max(trip_miles, list_length) << " min " << min(trip_miles, list_length) << " avg " << average(trip_miles, list_length) << " mode " << mode(trip_miles, list_length) << endl;
    cout << "Fare: "
         << "max " << max(trip_fare, list_length) << " min " << min(trip_fare, list_length) << " avg " << average(trip_fare, list_length) << " mode " << mode(trip_fare, list_length) << endl;
    cout << "Tip: "
         << "max " << max(trip_tip, list_length) << " min " << min(trip_tip, list_length) << " avg " << average(trip_tip, list_length) << " mode " << mode(trip_tip, list_length) << endl;
    cout << "Length of longest sequence without tips: " << length_longest_seq_zeros(trip_tip, list_length) << endl;
  }
  else
  {
    cout << "Can't open " << file_name << endl; // Only goes here if the file doesnt exist, filen name is invalid, or is corrupt.
  }
  return 0; //have to do this bc its int main
}