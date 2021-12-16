#include <iostream>
#include <sstream>
#include <fstream>

using std::cin, std::cout, std::endl, std::string, std::getline,
      std::ifstream, std::istringstream;

int main() {
  string filename; // initiate file name
  cout << "Enter donation filename: "; //ask user for file name so we can use it
  cin >> filename; // user inputs file name
  ifstream ifs(filename); // ifstream used for file handling
  if (!ifs.is_open()) { // if we are unable to open fail message shared with user
    cout << "Failed to open file " << filename << "." << endl;
    return 1;//shows there is an error in file handling
  }
  double sum = 0; // initalize summation variable , double bc cents are a thing
  double maxTotalDonation = 0; //initialize the maximum value of total donation
  string maxTotalCollector; // initialize maximum total collector
  string line; // variable created to hold information in one line of the file
  string student_uin; // created to hold UIN
  int count_donations;  
  double maxDonate =0; 
  double num;
  string donations;
  int first_index;
  int second_index;
  
  while(!ifs.eof()){ // reading in each line when line exists
    getline(ifs,line); // gets line & puts it in the file stream
    student_uin = line.substr(0,9); // gets student uin
    if(line.length()==9 || line.length()==10) 
    // if line/uin is invalid length jumps out of while loopfor that variable
    {
      continue;
    }
    else{ 
      donations = line.substr(10,line.size()-9); //gets input in reverse order
      donations += ' ';
      first_index = 0;
      for(int i =0;i<donations.size();i++){
        if(donations.at(i) == ' '){
          second_index = i;
          num = std::stod(donations.substr(first_index,second_index));
          first_index = second_index;
          sum+=num;
          count_donations = count_donations +1;
        }
      }
       if (sum > maxDonate && count_donations > 1) {
            maxDonate = sum;
            maxTotalCollector = student_uin;
       }
            sum = 0;
            count_donations= 0;
    }
  }
  
  maxTotalDonation = maxDonate;
  if(maxTotalDonation == 0){
    cout <<"No donations."<<endl;
  }
  
  else{
    cout << "Highest donation total: " << maxTotalDonation << endl;
    cout << "-- collected by id: " << maxTotalCollector << endl;
  }
}

  
