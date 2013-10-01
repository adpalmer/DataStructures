#ifndef _LIST
#define _LIST

#include <iostream>

template <class T>
class List {
private:
  struct Node {
    T data;
    Node *next, *previous;
    Node() : next{nullptr}, previous{nullptr} {}
    Node(T val) : data{val}, next{nullptr}, previous{nullptr} {}
  };
  Node *front;
  Node *back;
  int size;

public:
  List() : front(nullptr), back(nullptr), size(0) {}
  
  // Copy Constructor
  List(const List& other);
  
  // Move constructor
  List(List&& other);

  // copy assignment operator
  List& operator=(const List& rhs);
  
  // Move assignment operator
  List& operator=(List&& rhs);

  // push value to the front of the linked list
  void push_front(const T&);

  //push value to the back of the linked list
  void push_back(const T&);

  // pup value off the front of the linked list
  T pop_front();

  // pop value off the back of the linked list
  T pop_back();
  
  // returns the number of elements in the list
  int getSize();
  
  // forward iterator
  class iterator;

  // inserts value in front of provided iterator
  void insert(List<T>::iterator, const T&);

  // returns an iterator pointed at the beginning of the list
  iterator begin() { return iterator{front}; }

  // returns a null pointer signifying the end of the list
  iterator end() { return iterator{nullptr}; }
};


/******************* Class Implementation *******************/

// Copy Constructor
template <class T>
List<T>::List(const List& other) : front{nullptr}, back{nullptr}, size(0) {
  *this = other;
}

// Move constructor
template <class T>
List<T>::List(List&& rhs) {
  *this = std::move(rhs);
}

// copy assignment operator
template <class T>
List<T>& List<T>::operator=(const List& rhs) {
  if(this != &rhs) {
    Node *tmp = rhs.front;
    while(tmp != nullptr){
      push_back(tmp->data);
      tmp = tmp->next;
    }
  }
  return *this;
}

// Move assignment operator
template <class T>
List<T>& List<T>::operator=(List&& rhs) {
  if(this != &rhs) {
    front = rhs.front;
    back = rhs.back;
    size = rhs.size;
    rhs.size = 0;
    rhs.front = rhs.back = nullptr;
  }
  return *this;
}

template <class T>
void List<T>::push_front(const T& val) {
  Node *tmp = new Node{val};
  tmp->next = front;
  if(front != nullptr)
    front->previous = tmp;
  front = tmp;
  if(back == nullptr)
    back = front;
  size++;
}

template <class T>
void List<T>::push_back(const T& val) {
  Node *tmp = new Node{val};
  tmp->previous = back;
  if(back != nullptr)
    back->next = tmp;
  back = tmp;
  if(front == nullptr)
    front = back;
  size++;
}

template <class T>
T List<T>::pop_front() {
  T val;
  Node *tmp;
  if(size == 0)
    return val;
  val = front->data;
  tmp = front;
  front = front->next;
  delete tmp;
  if(size == 1)
    back = nullptr;
  size--;
  return val;
}

template <class T>
T List<T>::pop_back() {
  T val;
  Node *tmp;
  if(size == 0)
    return val;
  val = back->data;
  tmp = back;
  back = back->previous;
  delete tmp;
  if(size == 1)
    front = nullptr;
  size--;
  return val;
}

template<class T>
int List<T>::getSize() {
  return size;
}

template <class T>
class List<T>::iterator : public std::iterator<std::forward_iterator_tag, T> {
protected:
  friend class List;
  Node *curptr;
public:
  iterator() : curptr{nullptr} {}
  iterator(Node *p) : curptr{p} {}
  iterator(const iterator& it) : curptr{it.curptr} {}
  ~iterator() {}
  iterator& operator=(const iterator& other) {
    curptr = other.curptr;
    return *this;
  }
  bool operator==(const iterator& other) {return curptr == other.curptr;}
  bool operator!=(const iterator& other) {return curptr != other.curptr;}
  iterator& operator++() {
    if(curptr != nullptr)
      curptr = curptr->next;
    return *this;
  }
  iterator operator++(int) {
    iterator tmp(*this);
    operator++();
    return tmp;
  }
  T& operator*() {
    return curptr->data;
  }
  /*T* operator->() {
    return &curptr->data;
  }*/
};

template <class T>
void List<T>::insert(List<T>::iterator it, const T& val) {
  if(it.curptr != nullptr) {
    Node *tmp = new Node{val};
    tmp->next = it.curptr;
    tmp->previous = it.curptr->previous;
    if(it.curptr == front)
      front = tmp;
    else 
      it.curptr->previous->next = tmp;
    it.curptr->previous = tmp;
    size++;
  } else {
    throw "Null iterator";
  }
}

#endif
