#include <iostream>
#include "Rectangle.h"
#include "Point2D.h"


int main(){
	Rectangle a = Rectangle(Point2D(4,3),Point2D(17,9));
	Rectangle b = Rectangle(Point2D(5,2),Point2D(4,9));
	//Rectangle c = Rectangle(Point2D(14,3),Point2D(7,9));
	Rectangle d = Rectangle(Point2D(10,3),Point2D(8,0));
	Rectangle e = Rectangle(Point2D(6,10),Point2D(11,7));
	
	Point2D one = Point2D(10,6);
	Point2D two = Point2D(2,0);

	a.add_point(one);
	a.add_point(one);
	b.add_point(one);
	a.add_point(two);
	print_rectangle(a);
	print_rectangle(b);
	//print_rectangle(c);
	print_rectangle(d);
	print_rectangle(e);
	std::vector<Point2D> both;
	both = points_in_both(a,b);
	for(int i = 0;i < both.size(); i++){
		std::cout << "Points inside both rec a and b" <<std::endl;
		std::cout << both[i].x() << "," << both[i].y() <<std::endl;
	}
}