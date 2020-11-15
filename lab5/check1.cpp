#include <iostream>
#include <string>
#include <vector>


template <class T>
void print(std::vector<T> &data, const std::string &label) {
  std::cout << label << " ";
  for (int i = 0; i < data.size(); i++) {
    std::cout << " " << data[i];
  }
  std::cout << std::endl;
}


template <class T>
void reverse(std::vector<T> &data) {
  int count = data.size()-1;
  for(int i = 0; i< data.size()/2; i ++){
    T temp = data[i];
    data[i] = data[count];
    data[count] = temp;
    count--;
  }
}


int main() {
  std::vector<int> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(4);
  data.push_back(5);
  data.push_back(6);
  data.push_back(7);

  print(data,"before:");
  reverse(data);
  print(data,"after: ");

  std::vector<int> data2;
  data2.push_back(1);
  data2.push_back(2);
  data2.push_back(3);
  data2.push_back(4);
  data2.push_back(5);
  data2.push_back(6);
  print(data2,"before:");
  reverse(data2);
  print(data2,"after: ");

  std::vector<int> data4;
  data4.push_back(1);
  print(data4,"before:");
  reverse(data4);
  print(data4,"after: ");

  std::vector<int> data5;
  data5.push_back(1);
  data5.push_back(2);
  print(data5,"before:");
  reverse(data5);
  print(data5,"after: ");

  std::vector<int> data6;
  print(data6,"before:");
  reverse(data6);
  print(data6,"after: ");


  std::vector<std::string> data3;
  data3.push_back("apple");
  data3.push_back("banana");
  data3.push_back("carrot");
  data3.push_back("date");

  print(data3,"before:");
  reverse(data3);
  print(data3,"after: ");
}