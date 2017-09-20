#include <iostream>
#include <initializer_list>
#include <vector>

#include "shapes.h"

using namespace std;

void printShape(const Shape &shape) {
  cout << "This shape is a " << shape.name()
       << " and its area is " << shape.area() << endl;
}

int main() {
  Rectangle myRectangle = Rectangle(12,14);
  Rectangle myOtherRectangle(myRectangle);
  CartesianPoint a = CartesianPoint(1,2);
  Triangle myTriangle = Triangle(a,
                                 CartesianPoint(3,5),
                                 CartesianPoint(6,8));

  printShape(myRectangle);
  printShape(myOtherRectangle);
  printShape(myTriangle);

  return 0;
}
