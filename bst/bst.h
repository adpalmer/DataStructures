#include <iostream>
#include <list>
#include <functional>

// todo - constructors and destructor - must use order traversals

template <class T>
class bst {
private:
  struct Node;
  Node *head;
  unsigned int size;

  void clear(Node*);
  void preOrder(Node*, std::function<void(const T&)>);
  void inOrder(Node*, std::function<void(const T&)>);
  void postOrder(Node*, std::function<void(const T&)>);

public:
  bst() : head{nullptr}, size{0} {}
  bst(const bst& other); 
  bst(bst&& other);
  bst<T>& operator=(const bst&);
  bst<T>& operator=(bst&&);
  ~bst();

  void insert(const T&);
  void preOrder(std::function<void(const T&)>);
  void inOrder(std::function<void(const T&)>);
  void postOrder(std::function<void(const T&)>);
  std::list<T> getList();

};


template <class T>
bst<T>::bst(const bst& other) {
  other.preOrder(other.head, [this](const T& d){insert(d);});
}

template <class T>
bst<T>::bst(bst&& other) : head{other.head}, size{other.size} {
  other.size = 0;
  other.head = nullptr;
}

template <class T>
bst<T>& bst<T>::operator=(const bst& rhs) {
  if(*this != rhs) {
    rhs.preOrder(rhs.head, [this](const T& d){insert(d);});
  }
  return *this;
}

template <class T>
bst<T>& bst<T>::operator=(bst&& rhs) {
  if(*this != rhs) {
    head = rhs.head;
    size = rhs.size;
    rhs.head = nullptr;
    rhs.size = 0;
  }
  return *this;
}

template <class T>
bst<T>::~bst() {
  clear(head);
}

template <class T>
void bst<T>::clear(Node *tmp) {
  if(tmp != nullptr) {
    clear(tmp->left);
    clear(tmp->right);
    delete tmp;
  }
}


// Node definition
template <class T>
struct bst<T>::Node {
public:
  T data;
  Node *left, *right, *parent;
};

template <class T>
void bst<T>::insert(const T& d) {
  Node *parent = nullptr;
  Node **tmp = &head;
  while(*tmp != nullptr) {
    parent = *tmp;
    if(d > (*tmp)->data) {
      tmp = &((*tmp)->right);
    } else if(d < (*tmp)->data) {
      tmp = &((*tmp)->left);
    } else {
      return; // already exists
    }
  }

  Node *data = new Node;
  data->data = d;
  data->left = data->right = nullptr;
  data->parent = parent;
  *tmp = data;
  size++;
}

template <class T>
std::list<T> bst<T>::getList() {
  std::list<T> l;
  inOrder(head, [&l](const T& d){l.push_back(d);});
  return l;
}

template <class T>
void bst<T>::preOrder(std::function<void(const T&)> f) {
  preOrder(head, f);
}

template <class T>
void bst<T>::preOrder(Node *curr, std::function<void(const T&)> f) {
  if(curr != nullptr) {
    f(curr->data);
    preOrder(curr->left, f);
    preOrder(curr->right, f);
  }
}

// public in order traversal
template <class T>
void bst<T>::inOrder(std::function<void(const T&)> f) {
  inOrder(head, f);
}

// private recursive in order function that takes function pointer
template <class T>
void bst<T>::inOrder(Node *curr, std::function<void(const T&)> f) {
  if(curr != nullptr) {
    inOrder(curr->left, f);
    f(curr->data);
    inOrder(curr->right, f);
  }
}

template <class T>
void bst<T>::postOrder(std::function<void(const T&)> f) { 
  postorder(head, f);
}

template <class T>
void bst<T>::postOrder(Node *curr, std::function<void(const T&)> f) {
  if(curr != nullptr) {
    postOrder(curr->left, f);
    postOrder(curr->right, f);
    f(curr->data);
  }
}
