// =======================================================
//
// IMPORTANT NOTE: Do not modify this file
//     (except to uncomment the provided test cases 
//     and add your test cases where specified)
//
// =======================================================

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cassert>
#include <vector>
#include "table.h"


// helper testing functions
void SimpleTest();
void StudentTests();
void BatchTest(const char* filename, int num);
void ExtraCreditTests();


int main(int argc, char* argv[]) {
  if (argc == 1) {
    SimpleTest();
    std::cout << "Simple test completed." << std::endl;
    StudentTests();
    std::cout << "Student tests completed." << std::endl;    
    
    //
    // uncomment if you have implemented the extra credit features
    //
    // ExtraCreditTests();
    //

 } else {
    if (argc != 3) {
      std::cerr << "Usage: " << argv[0] << " <filename> <num_iters>" << std::endl;
      exit(1);
    }
    BatchTest(argv[1],atoi(argv[2]));
    std::cout << "Batch test completed." << std::endl;
  }
}



void SimpleTest() {

  // create a table with dimensions 2x5, where all entries are '.'
  Table<char> t(2,5,'.');
  assert (t.get(0,0) == '.');
  assert (t.get(1,4) == '.');
  assert (t.get(1,2) == '.');
  assert (t.numRows() == 2);
  assert (t.numColumns() == 5);
  t.print();
  std::cout << "constructor test completed" << std::endl;
  
  // intialize the values in the table
  t.set(0,0,'a');
  t.set(0,1,'b');
  t.set(0,2,'c');
  t.set(0,3,'d');
  t.set(0,4,'e');
  t.set(1,0,'f');
  t.set(1,1,'g');
  t.set(1,2,'h');
  t.set(1,3,'i');
  t.set(1,4,'j');
  assert (t.get(0,0) == 'a');
  assert (t.get(1,2) == 'h');
  assert (t.get(1,4) == 'j');
  t.print();
  std::cout << "set & get tests completed" << std::endl;

  // =======================================================  
  // 
  //     UNCOMMENT THE SECTIONS BELOW AS YOU 
  //        COMPLETE THE IMPLEMENTATION
  //
  // =======================================================  

  
  // add a row
  std::vector<char> new_row; 
  new_row.push_back('A');
  new_row.push_back('B');
  new_row.push_back('C');
  new_row.push_back('D');
  new_row.push_back('E');
  t.push_back_row(new_row);
  assert (t.numRows() == 3);
  assert (t.numColumns() == 5);
  t.print();
  std::cout << "add row test completed" << std::endl;
  

  
  // remove a column
  t.pop_back_column();
  assert (t.numRows() == 3);
  assert (t.numColumns() == 4);
  t.print();
  std::cout << "remove column test completed" << std::endl;
  

  
  // add a column
  std::vector<char> new_col;
  new_col.push_back('X');
  new_col.push_back('Y');
  new_col.push_back('Z');
  t.push_back_column(new_col);
  assert (t.numRows() == 3);
  assert (t.numColumns() == 5);
  t.print();
  std::cout << "add column test completed" << std::endl;
  

  
  // remove a row
  t.pop_back_row();
  assert (t.numRows() == 2);
  assert (t.numColumns() == 5);
  t.print();
  std::cout << "remove row test completed" << std::endl;
  

  
  // example of the copy constructor
  Table<char> another(t);
  // the structures initially look the same
  assert (t.numRows() == another.numRows());
  assert (t.numColumns() == another.numColumns());
  for (unsigned  i = 0; i < t.numRows(); i++) {
    for (unsigned  j = 0; j < t.numColumns(); j++) {
      assert (t.get(i,j) == another.get(i,j));
    }
  }
  // but future edits show they are different!
  another.set(1,2,'Q');
  assert (t.get(1,2) != another.get(1,2));
  std::vector<char> new_row2; 
  new_row2.push_back('A');
  new_row2.push_back('B');
  new_row2.push_back('C');
  new_row2.push_back('D');
  new_row2.push_back('E');
  another.push_back_row(new_row2);
  assert (t.numRows()+1 == another.numRows());
  assert (t.numColumns() == another.numColumns());
  t.print();
  another.print();
  std::cout << "copy constructor test completed" << std::endl;

  // example of the assignment operator
  t = another;
  // again the structures look the same
  assert (t.numRows() == another.numRows());
  assert (t.numColumns() == another.numColumns());
  for (unsigned  i = 0; i < t.numRows(); i++) {
    for (unsigned  j = 0; j < t.numColumns(); j++) {
      assert (t.get(i,j) == another.get(i,j));
    }
  }
  std::cout << "assignment operator test completed" << std::endl;
  

  // Note: The Table destructor is implicitly called for the
  //   stack-allocated variables 't' and 'another' when we leave the
  //   function and it goes out of scope.

}

void StudentTests() {

  // =======================================================  
  // 
  // YOU SHOULD ADD YOUR OWN TEST CASES HERE
  //
  // be sure to rigorously test:
  //   * tables that store types other than char
  //   * copy constructor
  //   * assignment operator
  //   * destructor
  //   * invalid requests (comment out for final submission)
  //
  // ======================================================= 
  //tests for type int
  std::cout << "\n\nInt type test" <<std::endl;
  Table<int> t(2,5,0);
  assert (t.get(0,0) == 0);
  assert (t.get(1,4) == 0);
  assert (t.get(1,2) == 0);
  assert (t.numRows() == 2);
  assert (t.numColumns() == 5);
  t.print();
  std::cout << "constructor test completed" << std::endl; 

  t.set(0,0,6);
  t.set(0,1,4);
  t.set(0,2,7);
  t.set(0,3,9);
  t.set(0,4,11);
  t.set(1,0,1);
  t.set(1,1,2);
  t.set(1,2,3);
  t.set(1,3,8);
  t.set(1,4,5);
  assert (t.get(0,0) == 6);
  assert (t.get(1,2) == 3);
  assert (t.get(1,4) == 5);
  t.print();
  std::cout << "set & get tests completed" << std::endl;

   // add a row
  std::vector<int> new_row; 
  new_row.push_back(4);
  new_row.push_back(5);
  new_row.push_back(2);
  new_row.push_back(0);
  new_row.push_back(6);
  t.push_back_row(new_row);
  assert (t.numRows() == 3);
  assert (t.numColumns() == 5);
  t.print();
  std::cout << "add row test completed" << std::endl;

  // remove a column
  t.pop_back_column();
  assert (t.numRows() == 3);
  assert (t.numColumns() == 4);
  t.print();
  std::cout << "remove column test completed" << std::endl;

  // add a column
  std::vector<int> new_col;
  new_col.push_back(3);
  new_col.push_back(7);
  new_col.push_back(4);
  t.push_back_column(new_col);
  assert (t.numRows() == 3);
  assert (t.numColumns() == 5);
  t.print();
  std::cout << "add column test completed" << std::endl;
  
  // remove a row
  t.pop_back_row();
  assert (t.numRows() == 2);
  assert (t.numColumns() == 5);
  t.print();
  std::cout << "remove row test completed" << std::endl;

 // example of the copy constructor
  Table<int> another(t);
  // the structures initially look the same
  assert (t.numRows() == another.numRows());
  assert (t.numColumns() == another.numColumns());
  for (unsigned  i = 0; i < t.numRows(); i++) {
    for (unsigned  j = 0; j < t.numColumns(); j++) {
      assert (t.get(i,j) == another.get(i,j));
    }
  }
  // but future edits show they are different!
  another.set(1,2,7);
  assert (t.get(1,2) != another.get(1,2));
  std::vector<int> new_row2; 
  new_row2.push_back(3);
  new_row2.push_back(4);
  new_row2.push_back(8);
  new_row2.push_back(1);
  new_row2.push_back(6);
  another.push_back_row(new_row2);
  assert (t.numRows()+1 == another.numRows());
  assert (t.numColumns() == another.numColumns());
  t.print();
  another.print();
  std::cout << "copy constructor test completed" << std::endl;

  // example of the assignment operator
  t = another;
  // again the structures look the same
  assert (t.numRows() == another.numRows());
  assert (t.numColumns() == another.numColumns());
  for (unsigned  i = 0; i < t.numRows(); i++) {
    for (unsigned  j = 0; j < t.numColumns(); j++) {
      assert (t.get(i,j) == another.get(i,j));
    }
  }
  std::cout << "assignment operator test completed" << std::endl;
  ///////////////////////////////////////////////////////////////
  ///NEW TEST(for string type)
  std::cout << "\n\nstring type test" <<std::endl;
  Table<std::string> t1(2,4,"hi");
  assert (t1.get(0,0) == "hi");
  assert (t1.get(1,3) == "hi");
  assert (t1.get(1,2) == "hi");
  assert (t1.numRows() == 2);
  assert (t1.numColumns() == 4);
  t1.print();
  std::cout << "constructor test completed" << std::endl; 

  t1.set(1,0,"what");
  t1.set(1,1,"do");
  t1.set(1,2,"you");
  t1.set(1,3,"like");
  assert (t1.get(1,3) == "like");
  assert (t1.get(1,2) == "you");
  assert (t1.get(1,0) == "what");
  t1.print();
  std::cout << "set & get tests completed" << std::endl;
  //add a row
  std::vector<std::string> string_row; 
  string_row.push_back("today");
  string_row.push_back("is");
  string_row.push_back("the");
  string_row.push_back("day");
  t1.push_back_row(string_row);
  assert (t1.numRows() == 3);
  assert (t1.numColumns() == 4);
  t1.print();
  std::cout << "add row test completed" << std::endl;
  // add a column
  std::vector<std::string> string_col;
  string_col.push_back("dum");
  string_col.push_back("dee");
  string_col.push_back("dum");
  t1.push_back_column(string_col);
  assert (t1.numRows() == 3);
  assert (t1.numColumns() == 5);
  t1.print();
  std::cout << "add column test completed" << std::endl;
  // remove a column
  t1.pop_back_column();
  assert (t1.numRows() == 3);
  assert (t1.numColumns() == 4);
  t1.print();
  std::cout << "remove column test completed" << std::endl;
   // remove a row
  t1.pop_back_row();
  assert (t1.numRows() == 2);
  assert (t1.numColumns() == 4);
  t1.print();
  std::cout << "remove row test completed" << std::endl;
  // example of the copy constructor
  Table<std::string> another1(t1);
  // the structures initially look the same
  assert (t1.numRows() == another1.numRows());
  assert (t1.numColumns() == another1.numColumns());
  for (unsigned  i = 0; i < t1.numRows(); i++) {
    for (unsigned  j = 0; j < t1.numColumns(); j++) {
      assert (t1.get(i,j) == another1.get(i,j));
    }
  }
  t1.print();
  another1.print();
  std::cout << "copy constructor test completed" << std::endl;

  // example of the assignment operator
  t1 = another1;
  // again the structures look the same
  assert (t1.numRows() == another1.numRows());
  assert (t1.numColumns() == another1.numColumns());
  for (unsigned  i = 0; i < t1.numRows(); i++) {
    for (unsigned  j = 0; j < t1.numColumns(); j++) {
      assert (t1.get(i,j) == another1.get(i,j));
    }
  }
  std::cout << "assignment operator test completed" << std::endl;
  //////////////////////////////////////////////////////////////
  /////NEW TEST(for bool type)
  std::cout << "\n\nbool type test" <<std::endl;
  Table<bool> t2(2,4,false);
  assert (t2.get(0,0) == false);
  assert (t2.get(1,3) == false);
  assert (t2.get(1,2) == false);
  assert (t2.numRows() == 2);
  assert (t2.numColumns() == 4);
  t2.print();
  std::cout << "constructor test completed" << std::endl; 

  t2.set(1,0,true);
  t2.set(1,1,true);
  t2.set(1,2,true);
  t2.set(1,3,true);
  assert (t2.get(1,3) == true);
  assert (t2.get(1,2) == true);
  assert (t2.get(1,0) == true);
  t2.print();
  std::cout << "set & get tests completed" << std::endl;
  //add a row
  std::vector<bool> bool_row; 
  bool_row.push_back(false);
  bool_row.push_back(true);
  bool_row.push_back(false);
  bool_row.push_back(true);
  t2.push_back_row(bool_row);
  assert (t2.numRows() == 3);
  assert (t2.numColumns() == 4);
  t2.print();
  std::cout << "add row test completed" << std::endl;
  // add a column
  std::vector<bool> bool_col;
  bool_col.push_back(false);
  bool_col.push_back(false);
  bool_col.push_back(false);
  t2.push_back_column(bool_col);
  assert (t2.numRows() == 3);
  assert (t2.numColumns() == 5);
  t2.print();
  std::cout << "add column test completed" << std::endl;
  // remove a column
  t2.pop_back_column();
  assert (t2.numRows() == 3);
  assert (t2.numColumns() == 4);
  t2.print();
  std::cout << "remove column test completed" << std::endl;
   // remove a row
  t2.pop_back_row();
  assert (t2.numRows() == 2);
  assert (t2.numColumns() == 4);
  t2.print();
  std::cout << "remove row test completed" << std::endl;
  // example of the copy constructor
  Table<bool> another2(t2);
  // the structures initially look the same
  assert (t2.numRows() == another2.numRows());
  assert (t2.numColumns() == another2.numColumns());
  for (unsigned  i = 0; i < t2.numRows(); i++) {
    for (unsigned  j = 0; j < t2.numColumns(); j++) {
      assert (t2.get(i,j) == another2.get(i,j));
    }
  }
  t2.print();
  another2.print();
  std::cout << "copy constructor test completed" << std::endl;

  // example of the assignment operator
  t2 = another2;
  // again the structures look the same
  assert (t2.numRows() == another2.numRows());
  assert (t2.numColumns() == another2.numColumns());
  for (unsigned  i = 0; i < t2.numRows(); i++) {
    for (unsigned  j = 0; j < t2.numColumns(); j++) {
      assert (t2.get(i,j) == another2.get(i,j));
    }
  }
  std::cout << "assignment operator test completed" << std::endl;
  /////////////////////////////////////////////////////////////
  //ERROR TESTS
  std::cout << "\n\nerror type test" <<std::endl;
  Table<int> t3(2,4,0);
  assert (t3.get(0,0) == 0);
  assert (t3.get(1,3) == 0);
  assert (t3.get(1,2) == 0);
  assert (t3.numRows() == 2);
  assert (t3.numColumns() == 4);

  //t3.set(1,5,8);
  //assert (t3.get(3,0) == 6);

  // std::vector<int> err_row; 
  // err_row.push_back(4);
  // err_row.push_back(2);
  // err_row.push_back(7);
  // t3.push_back_row(err_row);

  // std::vector<int> err_col;
  // err_col.push_back(3);
  // err_col.push_back(7);
  // err_col.push_back(4);
  // t3.push_back_column(err_col);

  // t3.pop_back_column();
  // t3.pop_back_column();
  // t3.pop_back_column();
  // t3.pop_back_column();
  // t3.pop_back_column();

  // remove a row
  // t3.pop_back_row();
  // t3.pop_back_row();
  // t3.pop_back_row();

}


void ExtraCreditTests() {

  // =======================================================  
  // 
  //            UNCOMMENT THIS SECTION IF YOU 
  //      COMPLETE THE EXTRA CREDIT IMPLEMENTATION
  //
  // =======================================================  

  /*
  Table<char> x(2,5,'x');
  assert (x.numRows() == 2);
  assert (x.numColumns() == 5);
  x.set(0,0,'.');
  x.set(1,4,'X');
  x.print();

  Table<char> y(4,5,'y');
  y.set(0,0,'.');
  y.set(3,4,'Y');
  x.push_back_rows(y);
  assert (x.numRows() == 6);
  assert (x.numColumns() == 5);
  x.print();
  
  Table<char> z(6,2,'z');
  z.set(0,0,'.');
  z.set(5,1,'Z');
  x.push_back_columns(z);
  assert (x.numRows() == 6);
  assert (x.numColumns() == 7);
  x.print();

  assert (x.get(0,0) == '.');
  assert (x.get(1,0) == 'x');
  assert (x.get(0,1) == 'x');
  assert (x.get(1,4) == 'X');

  assert (x.get(2,0) == '.');
  assert (x.get(2,1) == 'y');
  assert (x.get(3,0) == 'y');
  assert (x.get(5,4) == 'Y');

  assert (x.get(0,5) == '.');
  assert (x.get(1,5) == 'z');
  assert (x.get(0,6) == 'z');
  assert (x.get(5,6) == 'Z');

  std::cout << "extra credit tests completed" << std::endl;
  */
}



// Batch test will repeatedly load & process a file with Table
// operations.  If the program's working memory does not grow when the
// program is run many, many times on a large test case, the data
// structure is probably free of memory leaks.
void BatchTest(const char* filename, int iters) {

  if (iters <= 0) {
    std::cerr << "ERROR: iters should be > 0" << std::endl;
    exit(1);
  }

  while (iters > 0) {
    iters--;

    // open the file stream for reading
    std::ifstream istr(filename);
    if (!istr) {
      std::cerr << "ERROR: cannot open file " << filename << std::endl;
      exit(1);
    }

    std::string token;
    char c;
    int i,j,num;

    // create the initial table
    istr >> token >> i >> j >> c;
    assert (token == "create");
    // note: here we explicitly allocate memory for the Table object
    Table<char> *table = new Table<char>(i,j,c);

    // read in and perform various operations on the array
    while (istr >> token) {
      if (token == "set") {
        istr >> i >> j >> c;
        table->set(i,j,c);	
      } else if (token == "get") {
        istr >> i >> j >> c;
        char c2 = table->get(i,j);
        assert (c == c2);
      } else if (token == "push_back_row") {
        istr >> num;
        std::vector<char> tmp(num);
        for (int i = 0; i < num; i++) 
          istr >> tmp[i];
        table->push_back_row(tmp);
      } else if (token == "push_back_column") {
        istr >> num;
        std::vector<char> tmp(num);
        for (int i = 0; i < num; i++) 
          istr >> tmp[i];
        table->push_back_column(tmp);
      } else if (token == "pop_back_row") {
        table->pop_back_row();
      } else if (token == "pop_back_column") {
        table->pop_back_column();
      } else {
        std::cerr << "ERROR: unknown token " << token << std::endl;
        exit(1);
      }
    }

    if (iters == 0)
      table->print();

    // Because the Table memory was allocated explicitly (using new)
    // we need to explicitly deallocate the memory (using delete)
    delete table;
  }
}

