// A simple "caller ID" program

#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

// add a number, name pair to the phonebook
void add(std::map<int, std::string> &phonebook, int number, string const& name) {
  phonebook[number] = name;
}

// given a phone number, determine who is calling
void identify(const std::map<int, std::string> &phonebook, int number) {

  if(phonebook.find(number) == phonebook.end()){
  //if (phonebook[number] == "UNASSIGNED") 
    cout << "unknown caller!" << endl;
  }
  else 
    cout << phonebook.find(number)->second << " is calling!" << endl;
}


int main() {
  // create the phonebook; initially all numbers are unassigned
  //vector<string> phonebook(10000, "UNASSIGNED");
  std::map<int, std::string> phonebook;
  // add several names to the phonebook
  add(phonebook, 1111, "fred");
  add(phonebook, 2222, "sally");
  add(phonebook, 3333, "george");

  // test the phonebook
  identify(phonebook, 2222);
  identify(phonebook, 4444);
  return 0;
  
}
//constructing the phonebook is O(n)
//add function is O(1)
//identify is O(1)
//memory use is  O(N)
//it would get longer because you have to add that much many numbers to the vector