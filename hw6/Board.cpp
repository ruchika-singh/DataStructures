#include "Board.h"
#include <string>
#include <vector>
class Loc{
	public:
  		Loc(int x0, int y0) : x(x0), y(y0) {}
  		int x,y;
};

class Board{
	public:
		Board(int height, int width, std::vector<std::string> grid, std::vector<int> constraints);
		//ACESSORS
		int getRows() const{return rows;};
		int getCols() const{return columns;};
		//MUTATORS
		void print();
		void search();

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

	// int Board::getRows() const{
	// 	return rows;
	// }

	// int Board::getCols() const{
	// 	return cols;
	// }
}
void Board::print(){
	for(int i = 0; i < board.size(); i++){
		std::cout << board[i]<<std::endl;
	}
}

//always call searchAcross as (0, )
Loc Board::searchAcross(int row, const std::string& word){
	// std::string str = "";
	// for(int col = 0; col <columns; col++){
	// 	str += board[row][col];
	// }
	col_pos = board[row].find(word);
	if(col_pos != std::string::npos){
		Loc p1 = Loc(row, col_pos);
		return p1;
	}
	else if(row < rows)
		search(++row, word);
}

Loc Board::searchDown(int col, const std::string& word){
	std::string str = "";
	for(int row = 0; row < rows; row++){
		str += board[row][col];
	}
	row_pos = str.find(word);
	if(row_pos != std::string::npos){
		Loc p1 = Loc(row_pos, col);
		return p1;
	}
	else if(col < columns)
		search(col++, word);
}

// void findWordAcross(string word, int row, int col){
// 	int len = word.length();
// 	bool flag = false;
// 	int start_row;
// 	int start_col;
// 	for(int i = row; i < board.size(); i++){
// 		for(int j = col; j <board[i].size(); j++){
// 			if(word[0] == board[i][j]){
// 				start_row = i;
// 				start_col = j;
// 			}
// 		}
// 	}
// 	for(int k = 0; k < len; k++){
// 		if(word[k] != board[start_row][start_col + k]){
// 			flag = true;		
// 		}
// 	}
// 	if(flag == true)
// 		findWordAcross(word, start_row + 1, start_col + 1);
// 	else
// 		return 
// }
