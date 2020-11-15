#include <ctime>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <list>


// defined in performance.cpp
void usage();


void list_test(const std::string* input_data, int input_count, const std::string &operation, std::string *output_data, int &output_count) {

  // HINT: declare your list like this:
  std::list<std::string> lst;
  //inputs the values into the list
  for(int i = 0; i < input_count; i++){
    lst.push_back(input_data[i]);
  }

//sorts the list
  if (operation == "sort") {
    lst.sort();
    std::list<std::string>::iterator it = lst.begin();
    output_count = 0;
    //iterate through list and 
    for(; it != lst.end(); it++){
      output_data[output_count] = *it;
      output_count++;
    }
    
    //removes duplicates but keeps the same order of the list
  } else if (operation == "remove_dups_same_order") {
    //two iterators created to step through list and find duplicates
      std::list<std::string>::iterator it = lst.begin();
      for(;it != lst.end(); it++){
        std::list<std::string>::iterator it2 = lst.begin();
        for(;it2 != lst.end(); it2++){
          //checks if the iterators point to the same word
          if(it != it2 && *it == *it2){
            it2 = lst.erase(it2);//erase the word from the list
            //decrement the iterator
            it2--;
          }
        }
      }
      output_count = 0;
      //outputs the list without duplicaties in output_data
      std::list<std::string>::iterator it3 = lst.begin();
      for(; it3 != lst.end(); it3++){
        output_data[output_count] = *it3;
        output_count++;
      }

      //removes duplicates 
  } else if (operation == "remove_dups_any_order") {
    lst.sort();//sort list so duplicates are next to each other
    std::list<std::string>::iterator it = lst.begin();
    for(;it != lst.end(); it++){
      //check value with the value next to it
      if(*it == *(++it)){
        //erase and decrement the iterator
        it = lst.erase(it);
        it--;
      }
    }
    output_count = 0;
    //put values in output_data
    std::list<std::string>::iterator it3 = lst.begin();
    for(; it3 != lst.end(); it3++){
      output_data[output_count] = *it3;
      output_count++;
    }

    //finds most reoccuring string in list
  } else if (operation == "mode") {
      lst.sort();
      int current_count = 1;
    std::string mode;
    int mode_count = 0;
    // keep track of two pointers into the structure
    std::list<std::string>::iterator current = lst.begin();
    ++current;
    std::list<std::string>::iterator previous = lst.begin();
    for (; current != lst.end(); ++current, ++previous) {
      if (*current == *previous) {
  // if they are the same increment the count
        current_count++;
      } else if (current_count >= mode_count) {
        // found a new mode!
        mode = *previous;
        mode_count = current_count;
        current_count = 1;
      } else {
        current_count = 1;
      }
    }
    if (current_count >= mode_count) {
      // last entry is a new mode!
      mode = *previous;
      mode_count = current_count;
    }
    // save the mode to the output vector
    output_count = 1;
    output_data[0] = mode;

  } else {
    std::cerr << "Error: Unknown operation: " << operation << std::endl;
    usage();
  }
}
