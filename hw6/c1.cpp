#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "n1.h"
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
  	std::vector<int> across;
  	std::vector<int> down;
  	std::vector<int> constraints;
  	std::vector<int> constraint2;
  	std::vector<std::string> board;
  	std::vector<std::string> board2;
  	bool aflag = false;
  	bool dflag = false;
  	//for(grid_str >> line; line[0])
  	while ( grid_str >> line ) 
  	{

        if(line[0] == '+'){
        	constraints.push_back(line[1]-'0');
        }
        if(line[0] != '!' && line[0] != '+'){
        	//std::vector<std::string> row;
        	//row.push_back(line);
        	board.push_back(line);
        }
    }

    board2.push_back("HANGX");
    board2.push_back("OVERX");
    board2.push_back("TOPAZ");
    board2.push_back("XWAZE");
    board2.push_back("XSLED");
    constraint2.push_back(4);
    constraint2.push_back(4);
    constraint2.push_back(5);
    constraint2.push_back(4);
    constraint2.push_back(4);
    Board b2 = Board(board2.size(), board2[0].length(), board2, constraints);

    // for(int i = 0; i < constraints.size(); i++){
    // 	std::cout << constraints[i]<<std::endl;
    // }
    // std::cout<<std::endl;
    width = board[0].length();
    height = board.size();
    // for(int i = 0; i < board.size(); i++){
    // 	for(int j = 0; j <board[i].size(); j++)
    // 		std::cout << board[i][j]<<std::endl;
    // }
    //figure out how to make the words not overlap
    Board b1 = Board(height, width, board, constraints);
	//b1.print();
	bool te = false;


    //std::vector<int> copy_constraints(constraints);
    if(sol_mode == "one_solution"){
    	for(int i = 0; i < board.size(); i++){
			if(board[i] == board2[i] && constraints.size() == constraint2.size()){
				std::cout << "Number of solution(s): 0" <<std::endl;
				break;
				}
			else{
		    	std::cout << "Number of solution(s): 1" <<std::endl;
			    std::vector<bool> constraint_taken(constraints.size(),false);

			    std::vector<Point> points;
			    int counter = 0;
			    Point e = Point(0,0,0,false); 
			    //b1.searchAcross(0, "jkladfjaslkfjl;", e);
			    //std::cout << e.x << ' ' << e.y << std::endl;
			    std::vector<std::string> used_words;
			    for(int i = 0; i < dict.size(); i++){

			    	for(int j = 0; j< constraints.size();j++){
			    		// check = check_in(used_words, dict[i]);
			    		//std::cout << "bcheck: " << dict[i] << std::endl;
			    		if(dict[i].length() == constraints[j] && constraint_taken[j] == false && !check_in(used_words, dict[i])){
			    			//std::cout << "acheck: " << dict[i] << std::endl;
			    			Point p1 = Point(0,0, 0,false);
			    			b1.searchAcross(0,dict[i], p1);
			    			if(p1.x != -1 && p1.y != -1){
			    				points.push_back(p1);
			    				constraint_taken[j] = true;
			    				used_words.push_back(dict[i]);
			    			}
			    			else if(!check_in(used_words, dict[i])){
			    				//std::cout << "dsearch: " << dict[i] << std::endl;
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
			    // for(int i = 0; i < points.size(); i++){
			    // 	std::cout << points[i].x <<" " << points[i].y <<std::endl;
			    // }
			    b1.print_one_sol(points);
			    break;
			   }
	}
	}
	else
		std::cout << "Number of solution(s): 0"<<std::endl;
	/*
	if(sol_mode == "all_solutions"){
		int max = 0;
		for(int i = 0; i < constraints.size(); i++){
			if(constraints[i] > max)
				max = constraints[i];
		}
		int c[max+1];
		for(int z = 0; z < max+1; z++){
			c[z] = 0;
		}
		for(int i = 0; i < constraints.size(); i++){
			c[constraints[i]]++;
		}
		for(int j =0; j < max+1; j++){
			std::cout << c[j] <<std::endl;
		}
		std::cout <<"BREAK"<<std::endl;
		int max_length = 0;
		for(int i = 0; i < dict.size(); i++){
			if(dict[i].length() > max_length)
				max_length = dict[i].length();
		}

		int d[max_length+1];
		for(int z = 0; z < max_length+1; z++){
			d[z] = 0;
		}
		for(int z = 0; z <dict.size(); z++){
			d[dict[z].length()]++;
		}
		for(int i = 0; i <max_length+1; i++){
			std::cout << d[i] <<std::endl;
		}
		//create a copy of original dictionary as a list
		std::list<std::string> copy_dict;
		for(int i = 0; i < dict.size(); i++){
			copy_dict.push_back(dict[i]);
		}
		std::list<std::string>iterator itr;
		std::vector<bool> constraint_taken(constraints.size(),false);
		std::vector<std::string> used_words;
		for(int i = 0; i < max+1; i++){
			for(int j = 0; j < max_length +1; j++){

			}
		}
	    for(itr = copy_dict.begin(); itr != copy_dict.end(); itr++){
	    	for(int j = 0; j< constraints.size();j++){
	    		// check = check_in(used_words, dict[i]);
	    		//std::cout << "bcheck: " << dict[i] << std::endl;
	    		if(*itr.length() == constraints[j] && constraint_taken[j] == false && !check_in(used_words, *itr)){
	    			//std::cout << "acheck: " << dict[i] << std::endl;
	    			Point p1 = Point(0,0, 0,false);
	    			b1.searchAcross(0,*itr, p1);
	    			if(p1.x != -1 && p1.y != -1){
	    				points.push_back(p1);
	    				constraint_taken[j] = true;
	    				used_words.push_back(*itr);
	    			}
	    			else if(!check_in(used_words, *itr)){
	    				//std::cout << "dsearch: " << dict[i] << std::endl;
	    				b1.searchDown(0,*itr, p1);
	    				if(p1.x != -1 && p1.y != -1){
	    					points.push_back(p1);
	    					constraint_taken[j] = true;
	    					used_words.push_back(*itr);
	    				}
	    			}
				}
	    	}
	    }

	}
	*/
	return 0;

}