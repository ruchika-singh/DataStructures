#include <iostream>
#include <vector>
#include <string>
#include ""
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