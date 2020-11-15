#include <string>
#include <vector>
#include <iostream>
//holds location of the word, the length, and if its across
class Point{
	public:
  		Point(int x0, int y0, int w_len, bool a) {x = x0; y = y0; len = w_len;
  		 across = a;}
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
};
class Board{
	public:
		Board(int height, int width, std::vector<std::string> grid,
		 std::vector<int> constraints);
		//ACESSORS
		int getRows() const{return rows;};
		int getCols() const{return columns;};
		//MUTATORS
		void print(const std::vector<std::string>& used_words);
		void searchAcross(int row, const std::string& word, Point& ret);
		void searchDown(int col, const std::string& word, Point& ret);
		bool check_constraints(const std::vector<std::string>& b, int* c, int cs);
		std::vector<std::string> one_sol(const std::vector<Point>& points);
	private:
		int rows;
		int columns;
		std::vector<int> constraints;
		std::vector<std::string> board;
};

Board::Board(int height, int width, std::vector<std::string> grid,
 std::vector<int> constraints){
	rows = height;
	columns = width;
	constraints = constraints;
	board = grid;
}
//prints the board
void Board::print(const std::vector<std::string>& used_words){
	for(int i = 0; i < used_words.size(); i++){
		std::cout << used_words[i]<<std::endl;
	}
}
//function that searches the rows for the word recursively and saves the location
void Board::searchAcross(int row, const std::string& word, Point& ret){
	//if the word hasn't been found in board
	if(row == rows){
		Point p2 = Point(-1,-1,0, false);
		ret = p2;
		return;
	}
	int len = word.length();
	//go through each row to try and find word
	for(int col = 0; col < columns-(len-1); col++){
		if(board[row].substr(col,len) == word){
			//save location
			Point p1 = Point(row,col, len, true);
			ret = p1;
			return;
		}
	}
	//if its not in current row
	if(row < rows){
		searchAcross(++row, word, ret);
	}
}
//function that searches the columns for the word recursively and saves the location
void Board::searchDown(int col, const std::string& word, Point& ret){
	//if the word hasn't been found in board
	if (col == columns){
		Point p2 = Point(-1,-1, 0,false);
		ret = p2;
		return;
	}
	int len = word.length();
	std::string str = "";
	//create string for each column
	for(int row = 0; row < rows; row++){
		str += board[row][col];
	}
	//go through each string to find word
	for(int l = 0; l < str.length()-(len-1); l++){
		if(str.substr(l,len) == word){
			Point p1 = Point(l, col, len, false);
			ret = p1;
			return;
		}
	}
	//if its not in the current column
	if(col < columns){
		searchDown(++col, word, ret);
	}
}
//checks solution to see if it maatches constraints
bool Board::check_constraints(const std::vector<std::string>& b, int* c, int cs){
	int compvec[cs];
	for(int k = 0; k < cs; k++){
		compvec[k] = 0;
	}
	std::string a = "";
	for(int i = 0; i < b.size(); i++){ //across check
		for(int j = 0; j < b[0].size(); j++){
			if(b[i][j] != '#') {
				if(j < b[0].size()){
					a += b[i][j];
				}
				//if the location is the last spot and it is a word
				else if(j == b[0].size() -1 && a.length() > 2){
					//increases counter for that length 
					compvec[a.length()]++;
					a = "";
					continue;
				}
				//not a word
				else{
					a = "";
				}
			}
			//it is a word
			else if(b[i][j] == '#' && a.length() > 2) {
				compvec[a.length()]++;
				a = "";
			} 
			//not a word
			else {
				a = "";
			}
		}
	}
	a = "";

	for(int i = 0; i < b[0].size(); i++){ //down check
		for(int j = 0; j < b.size(); j++){
			if(b[j][i] != '#') {
				if(j < b.size()){
					a += b[i][j];
				}
				else if(j == b.size() - 1 && a.length() > 2){
					compvec[a.length()]++;
					a = "";
				}
				else{
					a = "";
				}
			}
			//is a word
			else if(b[j][i] == '#' && a.length() > 2) {
				compvec[a.length()]++;
				a = "";
			} 
			//not a word
			else {
				a = "";
			}
		}
	}
	//if the word length match the constraints array return true
	for(int it = 0; it < cs; it++){
		if(compvec[it] != c[it])
			return true;
	}
	return false;
}
//finds each solution
std::vector<std::string> Board::one_sol(const std::vector<Point>& points){
	//vector of word locations and each letter in the word
	//creates a copy of the board
	std::vector<std::string> cboard(board);
	//each letter location
	std::vector<std::vector<Point> > letter;
	//go through location of each word
	for(int e = 0; e < points.size(); e++){
		std::vector<Point> revec;
		revec.push_back(points[e]);
		for(int z = 0; z < points[e].len; z++){
			//if its an across word add each letter location
			if(points[e].across) {
				Point apoint = Point(points[e].x, points[e].y+z, 0 , true);
				revec.push_back(apoint);
			}
			//for down word add each letter location
			else {
				Point apoint = Point(points[e].x+z, points[e].y, 0, false);
				revec.push_back(apoint);
			}
		}
		//add each letter to the word
		letter.push_back(revec);
	}
	//go through copy grid
	for(int i = 0; i < cboard.size(); i++){
		for(int j = 0; j < cboard[0].size(); j++){
			bool flag = false;
			//go through the word location and letter
			for(int r = 0; r < letter.size(); r++){
				for(int s = 0; s < letter[r].size(); s++){
					if(i == letter[r][s].x && j == letter[r][s].y){
						flag = true;
					}
				}
			}
			//not valid as part of word
			if(flag != true){
				cboard[i][j] = '#';
			}
		}
	}
	return cboard;
}