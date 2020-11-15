#include <ctime>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <unordered_map>


// defined in performance.cpp
void usage();


void hash_table_test(const std::string* input_data, int input_count, const std::string &operation, std::string *output_data, int &output_count) {

  // HINT: declare your hash table like this:
  std::unordered_map<std::string,int> ht(input_count);
  //inputs values into unordered_map
  //key is string and value is how many times its repeated
  for(int i =0; i < input_count; i++){
    ht[input_data[i]]++;
   }

   //cannot sort an unordered map
  if (operation == "sort") {
    std::cerr<<"Won't work - not feasible/sensible"<<std::endl;

    //remove the dupicates while keeping same order as input data
  } else if (operation == "remove_dups_same_order") {
    std::unordered_map<std::string, int>::iterator it;
    output_count = 0;
    //iterate through input data
    for(int i = 0; i < input_count; i++){
      it = ht.find(input_data[i]);//find the value in the map
      if(it != ht.end()){
        ht.erase(it);//erase the value in the map
        //add it to the output_data
        output_data[output_count] = input_data[i];
        output_count++;
      }
    }

    //removes all the duplicates in the list
  } else if (operation == "remove_dups_any_order") {
    //map doesn't have any duplicates
    std::unordered_map<std::string, int>::iterator it = ht.begin();
    output_count = 0;
    //output data into array
    for(;it != ht.end(); it++){
      output_data[output_count] = it->first;
      output_count++;
    }

    //find most reoccuring value in the list 
  } else if (operation == "mode") {
    std::unordered_map<std::string, int>::const_iterator it = ht.begin();
    int highest = it->second;//get the amount of times string shows up
    std::string word;
    //figure out which string is repeated the most
    for(; it != ht.end(); it++){
      if(highest < it->second){
        highest = it->second;
        word = it->first;
      }
    }
    //ouput value
    output_count = 1;
    output_data[0] = word;
  } else {
    std::cerr << "Error: Unknown operation: " << operation << std::endl;
    usage();
  }
}
