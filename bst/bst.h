#include <iostream>
#include <list>
#include <functional>
#include <utility> // used for std::pair

// todo - constructors and destructor - must use order traversals

template <class Key, class T>
class bst {
private:
  class Node;
  Node *head;
  unsigned int size;

  void clear(Node*);
  void preOrder(Node*, std::function<void(const std::pair<Key,T>&)>);
  void inOrder(Node*, std::function<void(const std::pair<Key,T>&)>);
  void postOrder(Node*, std::function<void(const std::pair<Key,T>&)>);
  T& pvtInsert(const std::pair<Key,T>&);

public:
  bst() : head{nullptr}, size{0} {}
  bst(const bst& other); 
  bst(bst&& other);
  ~bst();

  class iterator;
  iterator begin() {
    Node *tmp = head;
    while(tmp->left != nullptr)
      tmp = tmp->left;
    return iterator{tmp};
  }
  iterator end() { return iterator{nullptr};}
  
  bst<Key,T>& operator=(const bst&);
  bst<Key,T>& operator=(bst&&);
  T& operator[](Key idx);
  //const T& operator[](Key idx) const;

  void clear();
  void insert(const std::pair<Key,T>&);
  iterator find(const Key& k);
  //iterator erase(const iterator& it);
  void preOrder(std::function<void(const std::pair<Key,T>&)>);
  void inOrder(std::function<void(const std::pair<Key,T>&)>);
  void postOrder(std::function<void(const std::pair<Key,T>&)>);
  std::list<std::pair<Key,T>> getList();

};


template <class Key, class T>
bst<Key,T>::bst(const bst& other) {
  preOrder(other.head, [this](const std::pair<Key,T>& d){insert(d);});
}

template <class Key, class T>
bst<Key,T>::bst(bst&& other) : head{other.head}, size{other.size} {
  other.size = 0;
  other.head = nullptr;
}

template <class Key, class T>
bst<Key,T>& bst<Key,T>::operator=(const bst& rhs) {
  if(*this != rhs) {
    rhs.preOrder(rhs.head, [this](const std::pair<Key,T>& d){insert(d);});
  }
  return *this;
}

template <class Key,class T>
bst<Key,T>& bst<Key,T>::operator=(bst&& rhs) {
  if(*this != rhs) {
    head = rhs.head;
    size = rhs.size;
    rhs.head = nullptr;
    rhs.size = 0;
  }
  return *this;
}

template <class Key, class T>
bst<Key,T>::~bst() {
  clear(head);
}

template <class Key, class T>
void bst<Key,T>::clear() {
  clear(head);
}

template <class Key, class T>
void bst<Key,T>::clear(Node *tmp) {
  if(tmp != nullptr) {
    clear(tmp->left);
    clear(tmp->right);
    delete tmp;
  }
}


// Node definition
template <class Key, class T>
class bst<Key,T>::Node {
public:
  std::pair<Key, T> *data;
  Node *left, *right, *parent;
  Node() {
    data = new std::pair<Key,T>;
    left = right = parent = nullptr;
  }
  ~Node() {
    if(data != nullptr)
      delete data;
  }
};

template <class Key, class T>
void bst<Key,T>::insert(const std::pair<Key,T>& d) {
  pvtInsert(d);
}

template <class Key, class T>
T& bst<Key,T>::pvtInsert(const std::pair<Key,T>& d) {
  Node *parent = nullptr;
  Node **tmp = &head;
  while(*tmp != nullptr) {
    parent = *tmp;
    if(d.first > (*tmp)->data->first) {
      tmp = &((*tmp)->right);
    } else if(d.first < (*tmp)->data->first) {
      tmp = &((*tmp)->left);
    } else { // already exists
      return ((*tmp)->data)->second;
    }
  }

  Node *data = new Node;
  data->data->first = d.first;
  data->data->second = d.second;
  data->left = data->right = nullptr;
  data->parent = parent;
  *tmp = data;
  size++;
  return data->data->second;
}

template <class Key, class T>
typename bst<Key,T>::iterator bst<Key,T>::find(const Key& k) {
  Node *tmp = head;
  while(tmp != nullptr && k != tmp->data->first) {
    if(k > tmp->data->first) {
      tmp = tmp->right;
    } else if(k < tmp->data->first) {
      tmp = tmp->left;
    }
  }
  return iterator{tmp};
}

/*
template <class Key, class T>
typename bst<Key,T>::iterator bst<Key,T>::erase(const bst<Key,T>::iterator& it) {
  Node *tmp = iterator.curptr;
  Node *trail;
  if(tmp->left != nullptr && tmp->right != nullptr) {
    tmp = tmp->right;
    while(tmp->left != nullptr) {
      trail = tmp;
      tmp = tmp->left;
    }
    trail->left = nullptr;
    tmp->parent = iterator.curptr->parent;
    tmp->left = iterator.curptr->left;
    tmp->right = nullptr;
    if(iterator.curptr->right != tmp)
      tmp->right = iterator.curptr->right;
  } else if(tmp->left != nullptr) {
    /************ MAKE DATA A UNIQUE_PTR (INCLUDE MEMORY) and swap data not pointers. simplifies things***********/


  // reset links to substitute node
//}

template <class Key, class T>
T& bst<Key,T>::operator[](Key idx) {
  std::pair<Key,T> tmp;
  tmp.first = idx;
  return pvtInsert(tmp);
}
/*
template <class Key, class T>
const T& operator[](Key idx) const {

}
*/
template <class Key, class T>
std::list<std::pair<Key,T>> bst<Key,T>::getList() {
  std::list<std::pair<Key,T>> l;
  inOrder(head, [&l](const std::pair<Key,T>& d){l.push_back(d);});
  return l;
}

template <class Key, class T>
void bst<Key,T>::preOrder(std::function<void(const std::pair<Key,T>&)> f) {
  preOrder(head, f);
}

template <class Key, class T>
void bst<Key,T>::preOrder(Node *curr, std::function<void(const std::pair<Key,T>&)> f) {
  if(curr != nullptr) {
    f(*(curr->data));
    preOrder(curr->left, f);
    preOrder(curr->right, f);
  }
}

// public in order traversal
template <class Key, class T>
void bst<Key,T>::inOrder(std::function<void(const std::pair<Key,T>&)> f) {
  inOrder(head, f);
}

// private recursive in order function that takes function pointer
template <class Key, class T>
void bst<Key,T>::inOrder(Node *curr, std::function<void(const std::pair<Key,T>&)> f) {
  if(curr != nullptr) {
    inOrder(curr->left, f);
    f(*(curr->data));
    inOrder(curr->right, f);
  }
}

template <class Key, class T>
void bst<Key,T>::postOrder(std::function<void(const std::pair<Key,T>&)> f) { 
  postorder(head, f);
}

template <class Key, class T>
void bst<Key,T>::postOrder(Node *curr, std::function<void(const std::pair<Key,T>&)> f) {
  if(curr != nullptr) {
    postOrder(curr->left, f);
    postOrder(curr->right, f);
    f(curr->data);
  }
}

template <class Key, class T>
class bst<Key,T>::iterator : public std::iterator<std::forward_iterator_tag, std::pair<Key,T>> {
protected:
  friend class bst;
  Node *curptr;
public:
  iterator() : curptr{nullptr} {}
  iterator(Node *p) : curptr{p} {}
  iterator(const iterator& it) : curptr{it.curptr}{}
  ~iterator() {}
  iterator& operator=(const iterator& other) {
    curptr = other.curptr;
    return *this;
  }
  bool operator==(const iterator& other) {return curptr == other.curptr;}
  bool operator!=(const iterator& other) {return !(*this == other); }
  
  iterator& operator++() {
    if(curptr != nullptr) {
      if(curptr->right != nullptr) {
        curptr = curptr->right;
        while(curptr->left != nullptr) {
          curptr = curptr->left;
        }
      } else if(curptr->parent->left == curptr) {
        curptr = curptr->parent;
      } else {
        while(curptr != nullptr)
          curptr = curptr->parent;
      }
    }
    return *this;
  }

  iterator& operator++(int) {
    iterator tmp(*this);
    operator++();
    return tmp;
  }

  std::pair<Key,T>& operator*() {
    return *(curptr->data);
  }
  
  std::pair<Key,T>* operator->() {
    return curptr->data;
  }
};
