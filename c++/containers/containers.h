/*
 * CMSC 245 -- Fall 2017
 * Vector class
 * Exception stuff:
 * http://www.sanfoundry.com/cpp-program-demonstrate-user-defined-exceptions/
 */
#include <exception>
#include <iostream>
#include <functional>

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
private:
  V element;
  LLNode<V> *next;

public:
  LLNode(V elem, LLNode<V> *next)
    : element(elem), next(next) { }

  LLNode(V elem)
    : element(elem), next(NULL) { }

  V getElement() { return element; }

  void setNext(LLNode<V> *n) { next = n; }
  
  LLNode<V> *getNext() { return next; }
  
  bool hasNext() { return next != NULL; }
};

template<typename V>
class LLVector {
private: 
  LLNode<V> *head;

public:
  // The empty linked list vector
  LLVector() : head(NULL) { }

  // Cons
  // Should be O(1) time
  // Note: copies the linked list of the memory in rest
  LLVector(V element, LLVector<V> rest)
    : head(rest.head)
  {
    addToFront(element);
  }
  
  // Add something to the front of this linked list
  void addToFront(V element) {
    LLNode<V> *new_node = new LLNode<V>(element);
    new_node->setNext(head);
    head = new_node;
  }

  // Copy constructor. Should be O(1)
  LLVector(LLVector &other) : head(other.head) {
    cout << "Warning: copy constructor is simply copying head\n";
  }
  
  // Copy operator. Should be O(1)
  LLVector<V> operator=(const LLVector<V> &other) {
    cout << "Warning: copy constructor is simply copying head\n";
    head = other.head;
  }

  LLNode<V>* first() { return head; }

  // Get the ith element
  // Will be O(n) time :-(
  V getIth(int i) {
    LLNode<V> *n = head;
    while (i > 0 && n) {
      n = n->getNext();
    }
    if (n) {
      return n->getElement();
    } else {
      throw Vec_overflow();
    }
  }
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

// Key-value pair
template<typename K, typename V>
struct KVPair {
public:
  K key;
  V value;
  
  KVPair(K key, V value) : key(key), value(value) { }
};

template<typename K>
class Not_in_dictionary : public exception {
private:
  K key;
  
public:
  Not_in_dictionary(K key) : key(key) { }

  const char *what() const throw()
  {
    return "Key not in dictionary";
  }
};

template<typename K, typename V>
class Dictionary {
private:
  typedef KVPair<K,V> pair;
  LLVector<pair> *table;
  unsigned int size;

  std::size_t bucket(K key) {
    return std::hash<K>(key) % 256;
  }

public:
  // Initialize a vector containing an empty list
  Dictionary()
    : table(new LLVector<KVPair<K,V>>[256])
      , size(256) { }

  void insert(K key, V value) {
    pair p(key,value);
    table[bucket(key)].addToFront(p);
  }

  // Look up value corresponding to `key`.
  // Throws: Not_in_dictionary if `key` not in dictionary
  V lookup(K key) {
    for (pair *ptr = table[bucket(key)].first(); ptr != NULL; ptr = ptr->next) {
      if (ptr->key == key) {
        return ptr->value;
      }
    }
    throw Not_in_dictionary<K>(key);
  }
};
