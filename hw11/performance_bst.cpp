#include <ctime>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>


// defined in performance.cpp
void usage();


void bst_test(const std::string* input_data, int input_count, const std::string &operation, std::string *output_data, int &output_count) {

  // HINT: declare your binary search tree (BST) like this:
   std::map<std::string,int> mp;
   //input data into map with key as string and val as how many 
   //times it shows up
   for(int i =0; i < input_count; i++){
    mp[input_data[i]]++;
   }

   //sorts the bst
  if (operation == "sort") {
    std::map<std::string, int>::const_iterator it = mp.begin();
    output_count = 0;
    //iterate through map and add string to output_data
    for(; it != mp.end(); it++){
      //for every repeated string print it
      for(int i = 0; i < it->second; i++){
        output_data[output_count] = it->first;
        output_count++;
      }
      
    }

    //remove duplicates while keeping order of input
  } else if (operation == "remove_dups_same_order") {
    std::map<std::string, int>::iterator it;
    output_count = 0;
    for(int i = 0; i < input_count; i++){
      it = mp.find(input_data[i]);//find the key in the map
      if(it != mp.end()){
        //erase the value in the map, can't be repeated
        mp.erase(it);
        output_data[output_count] = input_data[i];//add it to the output data
        output_count++;
      }
    }

    //remove duplicates
  } else if (operation == "remove_dups_any_order") {
    output_count = 0;
    //map has no duplicates so add all keys to output data
      std::map<std::string, int>::const_iterator it = mp.begin();
      for(; it != mp.end(); it++){
        output_data[output_count] = it->first;
        output_count++;
      }

     //find the most reoccuring value in the bst 
  } else if (operation == "mode") {
    std::map<std::string, int>::const_iterator it = mp.begin();
    int highest = it->second;//holds how many time the string repeats
    std::string word;
    //go through map to find the largest amount of duplicates
    for(; it != mp.end(); it++){
      if(highest < it->second){
        highest = it->second;
        word = it->first;
      }
    }
    //add it to the ouput data
    output_count = 1;
    output_data[0] = word;


  } else {
    std::cerr << "Error: Unknown operation: " << operation << std::endl;
    usage();
  }
}
