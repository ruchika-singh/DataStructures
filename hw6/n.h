#include <string>
#include <vector>
#include <iostream>
class Point{
	public:
		//Point(){x = 0; y = 0;}
  		Point(int x0, int y0, int w_len, bool a) {x = x0; y = y0; len = w_len; across = a;}
  		int x;
  		int y;
  		int len;
  		bool across;

  		Point& operator= (const Point& newp){

  			x = newp.x;
  			y = newp.y;
  			across = newp.across;
  			len = newp.len;
  			return *this;
  		}
  		// Point Point::operator=(const Point& old){

  		// }
};

class Board{
	public:
		Board(int height, int width, std::vector<std::string> grid, std::vector<int> constraints);
		//ACESSORS
		int getRows() const{return rows;};
		int getCols() const{return columns;};
		//MUTATORS
		void print(const std::vector<std::string>& used_words);
		void searchAcross(int row, const std::string& word, Point& ret);
		void searchDown(int col, const std::string& word, Point& ret);
		bool check_constraints(const std::vector<std::string>& b, int* c, int cs);
		std::vector<std::string> print_one_sol(const std::vector<Point>& points);


	private:
		int rows;
		int columns;
		std::vector<int> constraints;
		std::vector<std::string> board;
};

Board::Board(int height, int width, std::vector<std::string> grid, std::vector<int> constraints){
	rows = height;
	columns = width;
	constraints = constraints;
	board = grid;
}
void Board::print(const std::vector<std::string>& used_words){
	// while (i < board.size()){
	// //for(int i = 0; i < board.size(); i++){
	// 	bool flag = false;
	// 	int pos = board[i].find("#");
	// 	if(pos == std::string::npos){
	// 		flag = true;
	// 		std::string temp = board[i];
	// 	}
	// 	else{
	// 	//	std::cout << pos<< std::endl;
	// 		std::string temp = board[i].substr(i,pos);
	// 	}
	// 	std::cout <<temp<<std::endl;
	// 	for(int j = 0; j < used_words.size(); j++){
	// 		if(temp == used_words[j]){
	// 			break;
	// 		}
	// 	}
	// 	std::cout <<temp << std::endl;
	// 	i += pos + 1;
	// }
	for(int i = 0; i < used_words.size(); i++){

		std::cout << used_words[i]<<std::endl;
	}
}

void Board::searchAcross(int row,  const std::string& word, Point& ret){
	if(row == rows){
		Point p2 = Point(-1,-1,0, false);
		ret = p2;
		return;
	}
	int len = word.length();

	for(int col = 0; col < columns-(len-1); col++){
		if(board[row].substr(col,len) == word){
			Point p1 = Point(row,col, len, true);
			ret = p1;
			return;
		}
	}
	if(row < rows){
		searchAcross(++row, word, ret);
	}
}

void Board::searchDown(int col, const std::string& word, Point& ret){
	if (col == columns){
		Point p2 = Point(-1,-1, 0,false);
		ret = p2;
		return;
	}
	int len = word.length();
	// for(int row = 0; row < rows-(len-1); row++){
	// 	if(board[row].substr(col))
	// }
	std::string str = "";
	for(int row = 0; row < rows; row++){
		str += board[row][col];
	}
	for(int l = 0; l < str.length()-(len-1); l++){
		if(str.substr(l,len) == word){
			Point p1 = Point(l, col, len, false);
			ret = p1;
			return;
		}
	}
	if(col < columns){
		searchDown(++col, word, ret);
	}

}

bool Board::check_constraints(const std::vector<std::string>& b, int* c, int cs){
	int compvec[cs];
	for(int k = 0; k < cs; k++){
		compvec[k] = 0;
	}
	std::string a = "";
	//std::cout << a.length();
	for(int i = 0; i < b.size(); i++){ //across check
		for(int j = 0; j < b[0].size(); j++){
			if(b[i][j] != '#' && j < b[0].size()) {
				//a is the word in the line 
				//word is the length of the row 
				a += b[i][j];
				//std::cout <<a<<std::endl;
				if(j == b[0].size() -1 && a.length() > 2){
					//std::cout<<"Fuk"<<std::endl;
					//increases counter for that length 
					//std::cout <<a<<std::endl;
					compvec[a.length()]++;
					a = "";
					continue;
				}
				else if(j == b[0].size() -1){
					a = "";
				}
				// else
				// 	a += b[i][j]; 
			}
			// if(j == b[0].size() -1 && a.length() >1){
			// 		std::cout<<"Fuk"<<std::endl;
			// 		//increases counter for that length 
			// 		std::cout <<a<<std::endl;
			// 		compvec[a.size()]++;
			// 		a = "";
			// 		//continue;
			// 	}
			else if(b[i][j] == '#' && a.length() > 2) {
				//std::cout <<a<<std::endl;
				compvec[a.length()]++;
				a = "";
			} 
			else {
				a = "";
			}
		}
		//a = "";
	}
	a = "";


	for(int i = 0; i < b[0].size(); i++){ //down check
		for(int j = 0; j < b.size(); j++){
			//std::cout << i <<", "<<j<<std::endl;
			if(b[j][i] != '#') {
				a += b[j][i];
				//std::cout<<a<<std::endl;
				if(j == b.size() - 1 && a.length() > 2){
					//std::cout<<a<<std::endl;
					compvec[a.length()]++;
					a = "";
				}

				else if(j == b.size() -1){
					a = "";
				}
				// else
				// 	a += b[i][j]; 
			}
			else if(b[j][i] == '#' && a.length() > 2) {
				//std::cout<<a<<std::endl;
				compvec[a.length()]++;
				a = "";
			} 
			else {
				a = "";
			}
		}
		a = "";
		//std::cout << "new col"<<std::endl;	
	}
	//std::cout <<"DONE"<<std::endl;
	for(int it = 0; it < cs; it++){
		//std::cout << compvec[it] << ',' << it << ' '<<std::endl;
		if(compvec[it] != c[it])
			return true;
	}
	//std::cout<<"THE ONE"<<std::endl;
	return false;
	//std::cout << "\n";

}

std::vector<std::string> Board::print_one_sol(const std::vector<Point>& points){
	//vector of word locations and each letter in the word
	std::vector<std::string> cboard(board);
	std::vector<std::vector<Point> > ptexp;
	for(int e = 0; e < points.size(); e++){
		//letter
		std::vector<Point> revec;
		revec.push_back(points[e]);
		for(int z = 0; z < points[e].len; z++){
			if(points[e].across) {
				Point apoint = Point(points[e].x, points[e].y+z, 0 , true);
				revec.push_back(apoint);
			} else {
				Point apoint = Point(points[e].x+z, points[e].y, 0, false);
				revec.push_back(apoint);
			}
		}
		ptexp.push_back(revec);
	}

	for(int i = 0; i < cboard.size(); i++){
		for(int j = 0; j < cboard[0].size(); j++){
			bool flag = false;
			for(int r = 0; r < ptexp.size(); r++){
				for(int s = 0; s < ptexp[r].size(); s++){
					if(i == ptexp[r][s].x && j == ptexp[r][s].y){
						flag = true;
					}
				}
			}
			//if(flag == true){
			//	cboard[i][j] = board[i][j];
			// 	//std::cout << board[i][j];
			// }
			if(flag != true){
				cboard[i][j] = '#';
				//std::cout << "#";
			}
		}
		//std::cout << "\n";
	}
	return cboard;
}
// 		for(int j = 0; j < points.size(); j++){
	// 			if(i == points[j].x  && (k >= points[j].y || k < k+points[j].len) && points[j].across)
	// 				std::cout << board[i][k];
	// 			else if((i >= points[j].x || i < points[j].len) && (k == points[j].y) && !points[j].across){
	// 				std::cout << board[i][k];
	// 			}
	// 			else
	// 				std::cout << "#";
	// 		}
	// 	}
	// 	std::cout <<"\n";
	// }