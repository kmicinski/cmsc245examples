#include <iostream>
#include <string>

using namespace std;

class Animal {
private:
  string mName;
  
public:
  Animal(string name) : mName(name) {};
  virtual void speak() {
    cout << "Just an animal named " << mName << endl;
  }
};

class Dog : public Animal {
private:
  string mName;

public:
  Dog(string name) : Animal(name), mName(name) { }

  string getName() {
    return mName;
  }
  
  void bark() {
    cout << "Bark from " << mName << endl;
  }

  virtual void speak() {
    bark();
  }
};

class Cat : public Animal {
public:
  Cat(string name) : Animal(name) { }

  void meow() {
    cout << "meow!\n";
  }
  
  virtual void speak() {
    meow();
  }
};

// The following code is intended to give a hint on Lab 4 in the style
// of the above example. Please don't ask me to flesh it out too far
// beyond this, since I think this is already a pretty significant
// amount of help. 
// 
// I've also talked to a few people who did the lab another way. This
// is more than fine: in fact, I encourage you to do the lab in a way
// that makes sense to you. I really included this mostly because it
// seemed like a good time to introduce subclasses and do some
// collaborative hacking in class.

/*
class CalculatorOp {
  virtual int performOp(int input) = 0;
};

class AddOneOp : public CalculatorOp {
private:
  int mNum;
public:
  AddOneOp(int number) : mNum(number) { }

  virtual int performOp(int input) {
    return intput + mNum;
  };
};

class SubtractOp : public CalculatorOp {
private:
  int mNum;
public:
  AddOneOp(int number) : mNum(number) { }

  virtual int performOp(int input) {
    return intput - mNum;
  };
};
*/
