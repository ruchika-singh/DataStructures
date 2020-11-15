#ifndef Table_h_
#define Table_h_
#include <vector>
#include <iostream>

template <class T> class Table{
	public:
		typedef char size_type;
		//CONSTRUCTORS, ASSIGNMENT, OPERATOR, & DESTRUCTOR
		Table(const int aRows, const int aCols, const T& n)
			{this -> create(aRows, aCols,n);}
		Table(const Table<T>& tabA){copy(tabA);}
		Table<T>& operator= (const Table& tabA);
		~Table() {dest();}//destructor
		//MEMBER FUNCTIONS AND OTHER OPERATORS
		void push_back_row(const std::vector<T>& row);
		void push_back_column(const std::vector<T>& col);
		void pop_back_row();
		void pop_back_column();
		T get(const unsigned int i, const unsigned int j);
		T** getValues()const {return values;} //access 2D array
		void set(const unsigned int i, unsigned int j, const T& new_val);
		int numRows()const {return rows;}
		int numColumns()const{return cols;}
		void print();
	private:
		void create(const int aRows, const int aCols,const T& n );
		void copy(const Table<T>& tabA);
		void dest();//destructor function
		T** values;
		unsigned int rows;
		unsigned int cols;
};

//create a 2D array filled with values of n
template <class T> void Table<T>::create(const int aRows, const int aCols, const T& n){
	rows = aRows;
	cols = aCols;
	values = new T*[rows];//creates array of pointers(rows)
	for(int i = 0; i <rows; i++)
	{
		*(values + i) = new T[cols];//creates arrays of columns
		for(int j = 0; j <cols; j++)
		{
			*(*(values + i) + j) = n;//fills with values
		}
	}
}
//destructor
template <class T> void Table<T>::dest(){
//deletes pointers
	for(int i = 0; i < rows; i++){
		if (values[i] != nullptr) {
			delete [] *(values + i);	
		}
	}
	delete []values;
}
//assign one array to abother, avoiding duplicate copying(assignment) 
template <class T> Table<T>& Table<T>::operator=(const Table<T>& tabA) {
  if (this != &tabA) {
  	for(int i = 0; i < rows; i++){
  		delete [] *(values+i);
  	}
    delete [] values;
    //deletes original data before new array is copied
    this -> copy(tabA);
  }
  return *this;
}
//copy constructor
template <class T> void Table<T>::copy(const Table<T>& tabA) {
  this->rows = tabA.numRows();
  this->cols = tabA.numColumns();
  this->values = new T*[this->rows];
  // Copy the data
  for (size_type i = 0; i < this->rows; i++){
  	this->values[i] = new T[this->cols];
  	for(int j = 0; j < this->cols; j++){
  		this->values[i][j] = tabA.values[i][j];
  	}
  } 
}
//adds a row to the end of new array that copies the old one
template <class T> void Table<T>::push_back_row(const std::vector<T>& row){
	//error check
	if(row.size() != cols) {
		std::cerr <<"ERR: push_back_row could not be completed"<< std::endl;
		exit(1);
	}
	//creates a new array with an added row
	T** newArr = new T*[rows+1];
	for(int i = 0; i < rows; i++){
		*(newArr + i) = *(values + i);//copies old values
	}
	delete [] values;//deletes old pointer
	T* a = new T[cols];
	for(int x = 0; x<row.size(); x++){
		*(a + x) = row[x];
	}
	newArr[rows] = a;//adds new row pointer
	values = newArr;
	rows ++;
}
//adds a column to a array that is one size bigger in columns
template <class T> void Table<T>::push_back_column(const std::vector<T>& col){
	//error check
	if(col.size() != rows) {
		std::cerr <<"ERR: push_back_column could not be completed"<< std::endl;
		exit(1);
	}
	//creates temp array with added column
	T** newArr = new T*[rows];
	for(int i = 0; i < rows; i++){
		*(newArr + i) = new T[cols + 1];
		for(int j = 0; j < cols; j++){
			*(*(newArr + i) + j) = *(*(values + i) + j);
		}
		delete [] *(values + i);
	}
	delete [] values;//deletes old pointers
	//adds new column
	for(int x = 0; x < rows; x++){
		*(*(newArr + x) + cols) = col[x];
	}
	values = newArr;
	cols++;
}
//removes a row from table
template <class T> void Table<T>::pop_back_row(){
	//error check
	if(rows == 0){
		std::cerr<<"Array is too small, cannot shrink size of rows(pop_back_row)"
		<< std::endl;
		exit(1);
	}
	rows--;
	//deletes old pointer
	delete [] values[rows];
}
//removes a column from the table
template <class T> void Table<T>::pop_back_column(){
	//error check
	if(cols == 0){
		std::cerr << "Array is too small, cannot shrink size of columns(pop_back_column)"
		 << std::endl;
		exit(1);
	}
	else{
		//creates new array that is a copy of the old one with one less row
		T** newArr = new T*[rows];
		for (int i = 0; i < rows; i++){
			*(newArr + i) = new T[cols];
			for(int j = 0; j < cols - 1; j++){
				*(*(newArr + i) + j) = *(*(values + i) + j);
			}
			//deletes old pointers
			delete [] values[i];
		}
		delete [] values;
		values = newArr;
	}
	cols--;
}
//access specific value in table
template <class T> T Table<T>::get(const unsigned int i, const unsigned int j){
	if(i > rows || j > cols){
		std::cerr << "ERR: Out of bounds(get)" << std::endl;
		exit(1);
	}
	return *(*(values + i) + j);
}
//modify values in table
template <class T> void Table<T>::set(const unsigned int i,
const unsigned int j, const T& new_val){
	if(i > rows || j > cols){
		std::cerr << "ERR: Out of bounds(set)" << std::endl;
		exit(1);
	}
	*(*(values + i) + j) = new_val;
}
//prints out table
template <class T> void Table<T>::print(){
	std::cout<<"table: "<<rows<<" rows, "<<cols<<" cols"<<std::endl;
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			std::cout <<  *(*(values + i) + j) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
#endif