#include <iostream>

int path(int x, int y){
    if(x == 0 && y ==0){
      return 1;
    }
    int count = 0;
    if(x > 0){
      count += path( x-1,y);
    }
    if(y > 0){
      count+= path(x, y-1);
    }
    return count;
  }

int main(){

  std::cout << "Number of paths from (2,2) to origin: "<<path(2,2)<<std::endl;
  std::cout << "Number of paths from (2,2) to origin: "<<path(2,1)<<std::endl;
  std::cout << "Number of paths from (2,2) to origin: "<<path(0,0)<<std::endl;
  return 0;
}