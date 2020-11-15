#include <iostream>
#include <string>
#include <list>


template <class T>
void print(std::list<T> &data, const std::string &label) {
  std::cout << label << " ";
  //std::list<T>::
  //for (int i = 0; i < data.size(); i++) {
    //std::cout << " " << data[i];
 // }
  typename std::list<T>::iterator itr;
  std::cout << std::endl;
  for (itr = data.begin(); itr != data.end(); ++itr) {
    std::cout << " " << *itr;
  }
  std::cout << std::endl;
}


template <class T>

void reverse(std::list<T> &data) {
  int count = data.size()-1;
  typename std::list<T>::reverse_iterator ri;
  typename std::list<T>::iterator i;
  i = data.begin();
  //back = data.end();
  //ri = data.end()
  int counter = 0;
  int half = data.size()/2;
  for( ri = data.rbegin(); ri!= data.rend(); ++ri ){
    if (counter == half)
      break;
    T temp;
    temp = *i;
    *i  = *ri;
    *ri = temp;
    i++;
    counter ++;
  }
}


int main() {
  std::list<int> data;
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
}