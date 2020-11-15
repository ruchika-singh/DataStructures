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
		void print();
		void searchAcross(int row, const std::string& word, Point& ret);
		void searchDown(int col, const std::string& word, Point& ret);
		void print_one_sol(const std::vector<Point>& points);


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
void Board::print(){
	for(int i = 0; i < board.size(); i++){
		std::cout << board[i]<<std::endl;
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
void Board::print_one_sol(const std::vector<Point>& points){
	std::vector<std::vector<Point> > ptexp;
	for(int e = 0; e < points.size(); e++){
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

	for(int i = 0; i < board.size(); i++){
		for(int j = 0; j <board[0].size(); j++){
			// board[i][k]
			bool flag = false;
			for(int r = 0; r < ptexp.size(); r++){
				for(int s = 0; s < ptexp[r].size(); s++){
					if(i == ptexp[r][s].x && j == ptexp[r][s].y){
						flag = true;
					}
				}
			}
			if(flag == true){
				std::cout << board[i][j];
			}
			else{
				std::cout << "#";
			}
		}
		std::cout << "\n";
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
}
