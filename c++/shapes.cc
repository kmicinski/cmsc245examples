/* 
 * Example shapes and printing them
 */
#include "shapes.h"

double CartesianPoint::distanceFrom(const CartesianPoint &other) const {
  return 
    sqrt((x - other.getX()) * (x - other.getX())
         + (y - other.getY()) * (y - other.getY()));
}

double Triangle::area() const {
  return
    (point1.distanceFrom(point2) + point1.distanceFrom(point3)) / 2;
}

