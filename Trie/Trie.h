#ifndef Trie_
#define Trie_

#include <iostream>
#include <functional>
#include <list>
using namespace std;

#define BRANCH_CNT 26

class Trie {
   private:
      class Node {
         public:
            bool valid;
            Node **children;
            Node *parent;
            int childrenCnt;
            Node() : parent{nullptr} {
               children = new Node*[BRANCH_CNT];
               for(int i=0; i<BRANCH_CNT; i++)
                 children[i] = nullptr;
               valid = false;
               childrenCnt = 0;
            }
            ~Node() {
               //delete[] *children;
               delete[] children;
            }
      };
      Node *head;

      void inOrder(Node *x, string s, std::function<void(std::string)> f);
      void clear(Node *t);

   public:
      Trie();
      Trie(const Trie&);
      Trie(Trie&&);
      Trie& operator=(const Trie&);
      Trie& operator=(Trie&&);
      ~Trie() {
        clear(head);
      }
      bool insert(string x);
      bool del(string x);
      bool exists(string x);
      bool partialMatch(string x);
      void print();
      // returns list of of all valid strings in the trie
      std::list<std::string> getList();
};

/*********** Trie Implementation *************/

Trie::Trie() : head{new Node} {}

// copy constructor
Trie::Trie(const Trie& other) : head{new Node} {
  inOrder(other.head, "", [this](std::string s){insert(s);});
}

// move constructor
Trie::Trie(Trie&& other) : head{new Node} {
  head = other.head;
  other.head = nullptr;
}

Trie& Trie::operator=(const Trie& other) {
  if(head != other.head) {
    if(head) {
      clear(head);
    }
    head = new Node;
    inOrder(other.head, "", [this](std::string s){ insert(s); });
  }
  return *this;
}

Trie& Trie::operator=(Trie&& other) {
  if(head != other.head) {
    if(head) {
      clear(head);
    }
    head = other.head;
    other.head = nullptr;
  }
}

void Trie::clear(Trie::Node *t) {
  if(t != NULL) {
    for(int i=0; i<BRANCH_CNT; i++) {
      clear(t->children[i]);
    }
    delete t;
  }
}

bool Trie::insert(string x) {
  // if head is a nullptr, someone must have moved using std::move
  if(!head)
    head = new Node;

  Node *tmp = head;
  int index;
  for( int i=0; i<x.length(); i++ ) {
    index = (int)tolower(x[i]) - 97;
    if( index < 0 || index >= BRANCH_CNT )
       return false;
    if( tmp->children[index] ) {
       tmp = tmp->children[index];
    } else {
       tmp->children[index] = new Node;
       tmp->children[index]->parent = tmp;
       tmp->childrenCnt++;
       if( !tmp->children[index] ) {
          return false;
       }
       tmp = tmp->children[index];
    }
  }
  tmp->valid = true;
  return true;
}

bool Trie::del(string x) {
  // if head is a nullptr, someone must have moved using std::move
  if(!head)
    return false;
  Node *tmp = head;
  Node *tmp2;
  int index;
  for(int i=0; i<x.length(); i++) {
    index = (int)tolower(x[i])-97;
    if(index < 0 || index >= BRANCH_CNT) 
      return false;
    if(tmp->children[index]) {
      tmp = tmp->children[index];
    }
  }
  tmp->valid = false;

  // while tmp (to prevent segfault), tmp is invalid and it has zero children. Delete and climb
  // the tree
  int cnt = 0; // cnt used to find correct index to reset to null
  while(tmp && !tmp->valid && tmp->childrenCnt == 0) {
    tmp2 = tmp->parent;
    delete tmp;
    tmp = tmp2;
    // just deleted a child so decrement count
    tmp->childrenCnt--;
    cnt++;
  }
  index = (int)tolower(x[x.length()-cnt])-97;
  tmp->children[index] = nullptr;
  return true;

}

bool Trie::partialMatch(string x) {
  // if head is a nullptr, someone must have moved using std::move
  if(!head)
    return false;

   Node *tmp = head;
   int index;
   for( int i=0; i<x.length(); i++ ) {
      index = (int)tolower(x[i]) - 97;
      if(index < 0 || index >= 26 )
         return false;
      if( tmp->children[index] ) {
         tmp = tmp->children[index];
      } else {
         return false;
      }
   }
   return true;
}

bool Trie::exists(string x) {
  // if head is a nullptr, someone must have moved using std::move
  if(!head)
    return false;

   Node *tmp = head;
   int index;
   for( int i=0; i<x.length(); i++ ) {
      index = (int)tolower(x[i])- 97;
      if( index < 0 || index >= 26 )
         return false;
      if( tmp->children[index] ) 
         tmp = tmp->children[index];
      else
         return false;
   }
   if( tmp->valid )
      return true;
   return false;
}

// returns list of of all valid strings in the trie
std::list<std::string> Trie::getList() {
  std::list<std::string> l;
  inOrder(head, "", [&l](std::string s){l.push_back(s);});
  return l;
}

// For each valid string print the string followed by a newline
// this is done in alphabetical order
void Trie::print() {
   inOrder(head, "", [](std::string s){std::cout << s << std::endl;});
}

// recursive function takes function f and operates on it in order. Can be used for anything from printing to list building
// input: Node*, string, std::function<void(std::string)>
void Trie::inOrder(Node *x, string s, std::function<void(std::string)> f) {
   if( x->valid ) {
      f(s);
   }
   for( int i=0; i<BRANCH_CNT; i++ ) {
      if( x->children[i] ) {
         inOrder(x->children[i], s + char(i+97), f);
      }
   }
}


#endif
