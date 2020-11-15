#include <ctime>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>


// defined in performance.cpp
void usage();


void priority_queue_test(const std::string* input_data, int input_count,
 const std::string &operation, std::string *output_data, int &output_count) {

  // HINT: declare your priority_queue like this:
  std::priority_queue<std::string,std::vector<std::string> > 
  pq(input_data,input_data+input_count);
  //sortst the priority queue
  if (operation == "sort") {
    output_count = 0;
    while(!pq.empty()){//makes sure there are still things in the queue
      //adds beginning of pq to the output data
      output_data[output_count] = pq.top();
      pq.pop();//removes the first item in queue
      output_count++;
    }
    //outputs the output data in reverse order so it is in the right order
    for (unsigned int i = 0; i < output_count/2; i++) {
      std::string temp = output_data[i];//holds temp value
      //replaces first thing in array with last element-i
      output_data[i] = output_data[output_count-(1+i)];
      output_data[output_count-(1+i)] = temp;
    }

    //operation won't work with a priority queue
  } else if (operation == "remove_dups_same_order") {
      std::cerr<<"Won't work - not feasible/sensible"<<std::endl;

     //remove the duplicates of the priority queue 
  } else if (operation == "remove_dups_any_order") {
    output_count = 0;
    while(!pq.empty()){//while the priority queue still has values
      std::string word = pq.top();
      output_data[output_count] = pq.top();//add the top 
      pq.pop();//pop the top value
      //checks if the next values are the same that were just added
      while(pq.top() == word && !pq.empty()){
        pq.pop();//remove the duplicates
      }
      output_count++;
    }

    //finds the most occuring string
  } else if (operation == "mode") {
    int current_count = 1;
    std::string mode;
    int mode_count = 0;
    std::string prev;
    while(!pq.empty()) {
      prev = pq.top();//keep tracks of original val
      pq.pop();
      std::string curr = pq.top();
      if (prev == curr) {
        // if they are the same increment the count
        current_count++;
      } else if (current_count >= mode_count) {
        // found a new mode!
        mode = prev;
        mode_count = current_count;
        current_count = 1;
      } else {
        current_count = 1;
      }
    }
    if (current_count >= mode_count) {
      // last entry is a new mode!
      mode = prev;
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
