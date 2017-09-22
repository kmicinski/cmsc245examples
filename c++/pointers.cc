// compile with:
// g++ pointers.cc -o pointers
// run with:
// ./pointers

#include <iostream>

using namespace std;

void other() {
  int x = 12;
  cout << "x's value is " << x << endl;
  cout << "x's address is " << &x << endl;
  cout << "the size of x is " << sizeof(x) << endl;
}

void storingPtr() {
  int a = 23;
  int *pointerToA = &a;
  cout << "a's value is " << *pointerToA << endl;
  cout << "&a is " << &a << endl;
  cout << "pointerToA is " << pointerToA << endl;
  cout << "&pointerToA is " << &pointerToA << endl;
  cout << "sizeof(pointerToA) is " << sizeof(pointerToA) << endl;
  return;
}

int *returnsABadPointer() {
  int a = 23;
  int *ptr = &a;
  cout << "the value of *ptr is " << *ptr << endl;
  return &a;
}

void doSomethingBad() {
  int *ptr = returnsABadPointer();
  cout << "the value of *ptr is " << *ptr << endl;
  return;
}

int *newPointer() {
  int *a = new int;
  *a = 23;
  return a;
}

void doSomethingFine() {
  int *ptr = newPointer();
  cout << "the value of *ptr is " << *ptr << endl;
  (*ptr)++; // Be careful about *ptr++ as noted in video
  cout << "the value of *ptr is " << *ptr << endl;
  delete ptr;
}

void useAllMyMemory() {
  for (long long i = 0; i < 12346789000; i++) {
    int *ptr = new int;
  }
  return;
}

void dontUseAllMyMemory() {
  for (long long i = 0; i < 12346789000; i++) {
    int *ptr = new int;
    delete ptr;
  }
  return;
}

int main() {
  storingPtr();
  doSomethingBad();
  doSomethingFine();
  // Uncomment these to test
  //useAllMyMemory();
  //dontUseAllMyMemory();
  int a = 23;
  int b = 24;
  cout << "a's value is " << a << endl;
  cout << "a's address is " << &a << endl;
  cout << "the size of a is " << sizeof(a) << endl;
  cout << "b's value is " << b << endl;
  cout << "b's address is " << &b << endl;
  cout << "the size of b is " << sizeof(b) << endl;
  other();
  cout << "a's value is " << a << endl;
  cout << "a's address is " << &a << endl;
  cout << "the size of a is " << sizeof(a) << endl;
  cout << "b's value is " << b << endl;
  cout << "b's address is " << &b << endl;
  cout << "the size of b is " << sizeof(b) << endl;
}
