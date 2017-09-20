#include <vector>
#include <string>
#include <cmath>

using namespace std;

// Show this second
class Shape {
public:
  virtual double area() const = 0;
  virtual string name() const = 0;
};


// First
class Rectangle : public Shape {
private:
  const unsigned int length;
  const unsigned int width;

public:
  /*  Rectangle(unsigned int length, unsigned int width)
  : length(length), width(width)
  {
  }*/

  // Here's the copy constructor
  Rectangle(const Rectangle &other)
    : length(other.length), width(other.width)
  {
  }

  // I could also do this...
  Rectangle(unsigned int len, unsigned int wid)
    : length(len), width(wid)
  { }

  Rectangle(unsigned int len)
    : length(len), width(len)
  { }
  
  virtual double area() const {
    return (length * width);
  }
  
  virtual string name() const {
    return "rectangle";
  }
};


class MutableCartesianPoint {
private:
  int x;
  int y;

public:
  MutableCartesianPoint(int x, int y)
    : x(x), y(y)
  { }
  
  int getX() const {
    return x;
  }
  
  int getY() const {
    return y;
  }

  int moveX(int xprime) {
    x += xprime;
    return x;
  }

  int moveY(int yprime) {
    y += yprime;
    return y;
  }
};

class CartesianPoint {
private:
  const int x;
  const int y;
  
public:
  CartesianPoint(const CartesianPoint &o)
    : x(o.x), y(o.y) 
  { }

  CartesianPoint(int x, int y)
    : x(x), y(y)
  { }
  
  int getX() const {
    return x;
  }
  
  int getY() const {
    return y;
  }

  CartesianPoint operator+(CartesianPoint &other) {
    return CartesianPoint(x + other.x, y + other.y);
  }
  
  double distanceFrom(const CartesianPoint &other) const;
};

class Triangle : public Shape {
private:
  CartesianPoint point1;
  CartesianPoint point2;
  CartesianPoint point3;

public:
  Triangle(CartesianPoint point1, CartesianPoint point2, CartesianPoint point3)
    : point1(point1), point2(point2), point3(point3)
  { }

  double area() const;
  virtual string name() const {
    return "triangle";
  }
};
