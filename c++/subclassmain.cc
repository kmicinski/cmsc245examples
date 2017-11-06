// Subclassing and dynamic types lecture. Nov 6, 2017
/*
Here's an example of compiling and using this code...

kmicinski-17:c++ kmicinski$ g++ subclassmain.cc -std=c++1y -o subclasses
kmicinski-17:c++ kmicinski$ ./subclasses
Bark from ralph
Just an animal named ralph
Bark from ralph
Making all of my animals speak...
Bark from ralph
meow!
end of example
*/

#include <iostream>
#include <initializer_list>
#include <vector>
#include <list>
#include <map>

#include "subclassing.h"

using namespace std;

//std::map<string, CalculatorOp*> functionDefs;

int main(int argc, char **argv) {
  // This slightly-broken code intended to give hint on lab 4
  // AddOneOp addTwo(2);
  // SubtractOp subTwo(2);

  // functionDefs["+2"] = &addTwo;
  // functionDefs["-2"] = &subTwo;

  // int i = 23;
  // string x = "+2";
  // CalculatorOp* myOp = functionDefs[x];
  // x = myOp.performOp(x);

  // Begin subclassing example
  Dog ralph = Dog("ralph");
  ralph.speak();
  Animal ralph_again = ralph;
  ralph_again.speak();
  Animal *just_ralph = &ralph;
  just_ralph->speak();
  Cat matz = Cat("matz");
  Animal *just_matz = &matz;
  list<Animal*> myAnimals; 
  myAnimals.push_back(just_ralph);
  myAnimals.push_back(just_matz);
  cout << "Making all of my animals speak..." << endl;
  for (Animal* animal : myAnimals) {
    animal->speak();
  }
  cout << "end of example\n";
}
