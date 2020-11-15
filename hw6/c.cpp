#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "n.h"
#include <list>
bool compare(int* c, int* d, int max){
	for(int i = 0; i < max+1; i++){
		if(c[i] < d[i]){
			return true;
		}
	}
	return false;
}
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
  	//std::vector<std::string> board2;
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



    // for(int i = 0; i < constraints.size(); i++){
    // 	std::cout << constraints[i]<<std::endl;
    // }
    // std::cout<<std::endl;
    width = board[0].length();
    height = board.size();
    std::string stupid = "";
    for(int i  = 0;  i < width; i++){
    	stupid += " ";
    }
    // for(int i = 0; i < board.size(); i++){
    // 	for(int j = 0; j <board[i].size(); j++)
    // 		std::cout << board[i][j]<<std::endl;
    // }
    //figure out how to make the words not overlap

    std::vector<std::string> board2(board);
    // for(int i = 0; i< board2.size(); i++){
    // 	std::cout << board2[i] <<std::endl;
    // }
   	//Board b2 = Board(board2.size(), board2[0].length(), board2, constraints);
   	Board b2 = Board(height, width, board2, constraints);
    Board b1 = Board(height, width, board, constraints);
    //Board b2 = Board(height, width, )
	//b1.print();
	bool te = false;


    //std::vector<int> copy_constraints(constraints);
    if(sol_mode == "one_solution"){

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
	    if(points.size() >= 1){
		    std::vector<std::string> revec;
		    revec = b1.print_one_sol(points);
		    std::cout << "Number of solution(s): 1" <<std::endl;
		    if(out_mode == "print_boards")
		    	b1.print(revec);
		}
		else{
			std::cout << "Number of solution(s): 0" <<std::endl;
		}
	 //   	else
		// std::cout << "Number of solution(s): 0"<<std::endl;
	   
	}
	if(sol_mode == "all_solutions"){
		// for(int j =0; j < max+1; j++){
		// 	std::cout << c[j] <<std::endl;
		// }

		int max_length = 0;
		for(int i = 0; i < dict.size(); i++){
			if(dict[i].length() > max_length)
				max_length = dict[i].length();
		}
		int c[max_length+1];
		for(int z = 0; z < max_length+1; z++){
			c[z] = 0;
		}
		for(int i = 0; i < constraints.size(); i++){
			c[constraints[i]]++;
		}
		int d[max_length+1];
		for(int z = 0; z < max_length+1; z++){
			d[z] = 0;
		}
		for(int z = 0; z <dict.size(); z++){
			d[dict[z].length()]++;
		}
		// for(int i = 0; i <max_length+1; i++){
		// 	std::cout << d[i] <<std::endl;
		// }
		//create a copy of original dictionary as a list
		std::list<std::string> copy_dict;
		for(int i = 0; i < dict.size(); i++){
			copy_dict.push_back(dict[i]);
		}
		// int deletable;
		// for(int i = 0; i < max+1; i++){
		// 	if(c[i] < d[i]){
		// 		deletable = i;
		// 	}
		// }
		// int x = 0;

		//std::vector<bool> constraint_taken(constraints.size(),false);

	    // std::vector<Point> points;
	    std::vector<std::vector<Point> > pointsbig;
		// while(x < deletable){
	    while(compare(c,d, max_length)){
	    	std::vector<Point> points;
			std::vector<std::string> used_words;
	    	std::vector<bool> constraint_taken(constraints.size(),false);
		    for(std::list<std::string>::iterator itr = copy_dict.begin(); itr != copy_dict.end(); itr++){
		    	// std::vector<bool> constraint_taken(constraints.size(),false);
		    	for(int j = 0; j< constraints.size();j++){
		    		// check = check_in(used_words, dict[i]);
		    		//std::cout << "bcheck: " << dict[i] << std::endl;
		    		if(itr->length() == constraints[j] && constraint_taken[j] == false && !check_in(used_words, *itr)){
		    			//std::cout << "acheck: " << dict[i] << std::endl;
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
		    					d[itr->size()]--;
								itr = copy_dict.erase(itr);
								itr--;
								// std::cout << 'a' << std::endl;
								// std::cout << max
								// std::cout<< max_length << std::endl;
								// std::cout << itr->size() << std::endl;
								// d[itr->size()]--;
							
							}
		    			}
					}
		    	}
		    }
		    std::vector<std::string> testvec = b1.print_one_sol(points);
		    if(b1.check_constraints(testvec, c, max_length + 1))
		    	//std::cout <<"HI"<<std::endl;
		    	pointsbig.push_back(points);

		    // std::cout << "Board:"<<std::endl;
		   	// b1.print_one_sol(points, b2);
	    	// b1.print(used_words);
		}
		std::cout << "Number of solution(s): " <<pointsbig.size()<<std::endl;
		//Board b3 = 
		for(int i = 0; i < pointsbig.size(); i++){
			//for(int j = 0; j < pointsbig[i].size(); j++){
				std::cout << "Board:" <<std::endl;
				std::vector<std::string> revec;
				revec = b1.print_one_sol(pointsbig[i]);
				// b1.check_constraints(revec);
				if(out_mode == "print_boards"){
					b1.print(revec);
					std::cout<<"\n";
				}
			//}
		} 

	} 



		    	// 		if(p1.x != -1 && p1.y != -1){
		    	// 			points.push_back(p1);
		    	// 			constraint_taken[j] = true;
		    	// 			used_words.push_back(*itr);
							// if(c[itr->size()] != d[itr->size()]){
							// 	//std::cout << "F" <<std::endl;
							// 	itr = copy_dict.erase(itr);
							// 	d[itr->size()]--;
							// 	//x++;
							// 	//break;
							// }
		    	// 		}
		    	// 		else if(!check_in(used_words, *itr)){
		    	// 			//std::cout << "dsearch: " << dict[i] << std::endl;
		    	// 			b1.searchDown(0,*itr, p1);
		    	// 			if(p1.x != -1 && p1.y != -1){
		    	// 				points.push_back(p1);
		    	// 				constraint_taken[j] = true;
		    	// 				used_words.push_back(*itr);
							// 	if(c[itr->size()] != d[itr->size()]){
							// 		//std::cout << "FU" <<std::endl;
							// 		itr = copy_dict.erase(itr);
							// 		d[itr->size()]--;
							// 		//x++;
							// 	}
		    	// 			}
		    	// 		}



	
	return 0;

}