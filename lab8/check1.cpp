#include <iostream>
#include <fstream>
#include <map>
#include <string>

int main(int argc, char* argv[]){
	std::ifstream in_str(argv[1]);
	int num;
	std::map<int, int> counters;
	if (!in_str.good()) {
	    std::cerr << "Can't open " << argv[1] << " to read.\n"; 
	    exit(1);
  	}
  	while(in_str >> num){
  		++counters[num];
  	}
  	std::map<int, int>::const_iterator it = counters.begin();
  	for (; it != counters.end(); ++it) {
  		if(it->second > 1)
    		std::cout << it->first << "\t" << it->second << std::endl;
  	}
	return 0;
}