/*
 * CMSC 245 -- Fall 2017
 * Vector class
 * Exception stuff:
 * http://www.sanfoundry.com/cpp-program-demonstrate-user-defined-exceptions/
 */
#include <exception>
#include <iostream>

using namespace std;

#define DEBUG 0

class Vec_overflow : public exception {
public:
  const char *what() const throw()
  {
    return "Vector size overflow";
  }
};

// Pure virtual for now. We will implement on Wednesday
template<typename V>
class LLNode {
  
};

template<typename V>
class LLVector {
private: 
  LLNode<V> *head;

public:
  // The empty linked list vector
  LLVector()=0;

  // Cons
  // Should be O(1) time
  LLVector(V element, LLVector<V> rest)=0;

  // Copy constructor. Should be O(1)
  LLVector(LLVector &other)=0;
  
  // Copy operator. Should be O(1)
  LLVector<V> operator=(const LLVector<V> &other)=0;

  // Get the ith element
  // Will be O(n) time :-(
  V getIth(int i)=0;
};

template<typename V> 
class ArrayVector {
private:
  V *elements;
  int size;
  
public:
  // Create an empty vector
  // O(1)
  ArrayVector() : elements(NULL), size(0) { }

  // Initialzie an empty vector of size `size`
  ArrayVector(int size) : elements(new V[size]), size(size) { }
  
  // The operator= operation, happens when you see v = ... 
  // Look at function `benchmark_arrayvec` to see an example.
  ArrayVector<V> operator=(const ArrayVector<V> &other) {
    if (DEBUG)
      cout << "operator= running\n";
    return ArrayVector<V>(other);
  }

  // Copy constructor, runs implicitly by the compiler when you make a
  // copy of this object.
  // O(n)
  ArrayVector(const ArrayVector<int> &vother) : elements(NULL), size(vother.size)
  {
    if (vother.elements != NULL)
      elements = new V[vother.size];

    if (DEBUG)
      cout << "(Copy ctr) The other array's address was "
           << vother.elements 
           << " and the new address is "
           << elements << endl;
    
    for(int i = 0; i < vother.size; i++) {
      elements[i] = vother.elements[i];
    }
  }
  
  // This is the "extending" constructor, like cons
  // O(n)
  ArrayVector(V element, ArrayVector<V> v)
    : elements(new V[v.size+1]), size(v.size+1)
  {
    if (DEBUG)
      cout << "(Extending ctr) `elements` is " << elements << endl;
    elements[0] = element;
    for(int i = 0; i < v.size; i++) {
      elements[i+1] = v.elements[i];
    }
  }

  // This is the destructor.
  // O(1)
  virtual ~ArrayVector() {
    if(elements != NULL) {
      if (DEBUG)
        cout << "(Destructor) Should be deleting address " << elements << endl;
      delete elements;
      elements = NULL;
    }
  }

  // Simply delegates to the copy constructor 
  // O(n)
  virtual ArrayVector<V> cons(int i) {
    return ArrayVector<V>(i,*this);
  }
  
  // Get ith element, O(1)
  // This is where the linked list one starts to degrade badly
  virtual V getIth(unsigned int i) {
    if(i >= size) {
      Vec_overflow exn;
      throw exn;
    } else {
      return elements[i];
    }
  }
};




