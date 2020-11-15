#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "newboard.h"
#include <list>
//function that compares the constraints and the number of
//words in the dictionary
bool compare(int* c, int* d, int max){
	for(int i = 0; i < max+1; i++){
		if(c[i] < d[i]){
			return true;
		}
	}
	return false;
}
//checks to see if a words has already been used
bool check_in(const std::vector<std::string>& used, const std::string& word){
	for(int i = 0; i < used.size(); i++){
		if (word == used[i]){
			return true;
		}
	}
	return false;
}

int main(int argc, char* argv[]){
	std::ifstream dic_str(argv[1]);
	std::ifstream grid_str(argv[2]);
	std::string sol_mode = argv[3];
	std::string out_mode = argv[4];
	std::string line;
	std::string word;
	int width;
	int height;
	//error check for inputing files
	if (!dic_str.good()) {
	    std::cerr << "Can't open " << argv[1] << " to read.\n"; 
	    exit(1);
  	}
  	if(!grid_str.good()){
  		std::cerr << "Can't open " << argv[2] << " to read.\n";
  		exit(1);
  	}
  	if(argc < 5){
  		std::cerr << "Not enough arguments";
  		exit(1);
  	}
  	std::vector<std::string> dict;
  	while(dic_str >> word){
  		dict.push_back(word);
  	}
  	std::vector<int> constraints;
  	std::vector<std::string> board;
  	while ( grid_str >> line ) 
  	{
        if(line[0] == '+'){
        	constraints.push_back(line[1]-'0');
        }
        if(line[0] != '!' && line[0] != '+'){
        	board.push_back(line);
        }
    }
    width = board[0].length();
    height = board.size();
    std::string stupid = "";
    for(int i  = 0;  i < width; i++){
    	stupid += " ";
    }
    Board b1 = Board(height, width, board, constraints);
    if(sol_mode == "one_solution"){
    	//if a constraint has been used
	    std::vector<bool> constraint_taken(constraints.size(),false);
	    std::vector<Point> points;
	    int counter = 0;
	    std::vector<std::string> used_words;
	    //goes through dictionary and constraints for each word 
	    for(int i = 0; i < dict.size(); i++){
	    	for(int j = 0; j< constraints.size();j++){
	    		//makes sure the it fits one of the constraints and that it hasnt been used
	    		//also check to see if word was already used 
	    		if(dict[i].length() == constraints[j] && constraint_taken[j] == false 
	    			&& !check_in(used_words, dict[i])){
	    			//create default point that will be changed by recursive function
	    			Point p1 = Point(0,0, 0,false);
	    			b1.searchAcross(0,dict[i], p1);
	    			//makes sure point it valid
	    			if(p1.x != -1 && p1.y != -1){
	    				//add it to list of points
	    				points.push_back(p1);
	    				constraint_taken[j] = true;
	    				used_words.push_back(dict[i]);
	    			}
	    			//check if it is a down word instead
	    			else if(!check_in(used_words, dict[i])){
	    				b1.searchDown(0,dict[i], p1);
	    				if(p1.x != -1 && p1.y != -1){
	    					points.push_back(p1);
	    					constraint_taken[j] = true;
	    					used_words.push_back(dict[i]);
	    				}
	    			}
				}
	    	}
	    }
	    //if there words in the dictionary and constraints
	    if(points.size() == constraints.size()){
		    std::vector<std::string> revec;
		    revec = b1.one_sol(points);
		    std::cout << "Number of solution(s): 1" <<std::endl;
		    if(out_mode == "print_boards")
		    	b1.print(revec);
		}
		else{
			std::cout << "Number of solution(s): 0" <<std::endl;
		} 
	}
	if(sol_mode == "all_solutions"){
		//finds max length of words in the dictionary 
		int max_length = 0;
		for(int i = 0; i < dict.size(); i++){
			if(dict[i].length() > max_length)
				max_length = dict[i].length();
		}
		//creates array of constraints
		int c[max_length+1];
		for(int z = 0; z < max_length+1; z++){
			c[z] = 0;
		}
		for(int i = 0; i < constraints.size(); i++){
			c[constraints[i]]++;
		}
		//creates array of dictionary word lengths
		int d[max_length+1];
		for(int z = 0; z < max_length+1; z++){
			d[z] = 0;
		}
		for(int z = 0; z <dict.size(); z++){
			d[dict[z].length()]++;
		}
		//create a copy of original dictionary as a list
		std::list<std::string> copy_dict;
		for(int i = 0; i < dict.size(); i++){
			copy_dict.push_back(dict[i]);
		}
		//makes a vector of the locations of each letter in each word
	    std::vector<std::vector<Point> > pointsbig;
	    //while the number of words is less than the number of constraints
	    //which means there are still more possible solutions
	    while(compare(c,d, max_length)){
	    	std::vector<Point> points;
			std::vector<std::string> used_words;
	    	std::vector<bool> constraint_taken(constraints.size(),false);
	    	//goes through copy dictionary and constraints for each word
		    for(std::list<std::string>::iterator itr = copy_dict.begin();
		     itr != copy_dict.end(); itr++){
		    	for(int j = 0; j< constraints.size();j++){
		    		//checks constraints and if it is used already and if the
		    		// word has been used
		    		if(itr->length() == constraints[j] && constraint_taken[j] == false
		    		 && !check_in(used_words, *itr)){
		    			Point p1 = Point(0,0, 0,false);
		    			b1.searchAcross(0,*itr, p1);
		    			if(p1.x == -1 && p1.x == -1){
		    				b1.searchDown(0,*itr,p1);
		    			}
		    			if(p1.x != -1 && p1.y != -1){ //if word is found
		    				points.push_back(p1);
		    				constraint_taken[j] = true;
		    				used_words.push_back(*itr);
		    				if(c[itr->size()] != d[itr->size()]){
		    					//decreases size of the copy dictionary
		    					//AKA removes that word from the dictionary
		    					d[itr->size()]--;
								itr = copy_dict.erase(itr);
								itr--;
							}
		    			}
					}
		    	}
		    }
		    //finds the solutions
		    std::vector<std::string> testvec = b1.one_sol(points);
		    //makes sure solutions follow constraints
		    if(b1.check_constraints(testvec, c, max_length + 1))
		    	//adds to big vector of points
		    	pointsbig.push_back(points);
		}
		//prints solutions
		std::cout << "Number of solution(s): " <<pointsbig.size()<<std::endl;
		for(int i = 0; i < pointsbig.size(); i++){
			std::cout << "Board:" <<std::endl;
			std::vector<std::string> revec;
			revec = b1.one_sol(pointsbig[i]);
			if(out_mode == "print_boards"){
				b1.print(revec);
				std::cout<<"\n";
			}
		} 
	} 	
	return 0;
}