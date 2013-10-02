#ifndef Trie_
#define Trie_

#include <iostream>
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

      void print(Node *x, string s);

   public:
      Trie() {
         head = new Node;
      }
      ~Trie() {
        clear(head);
      }
      void clear(Node *t);
      bool insert(string x);
      bool exists(string x);
      bool partialMatch(string x);
      void print();
      class iterator;
};

void Trie::clear(Trie::Node *t) {
  if(t != NULL) {
    for(int i=0; i<BRANCH_CNT; i++) {
      clear(t->children[i]);
    }
    delete t;
  }
}

bool Trie::insert(string x) {
   Node *tmp = head;
   int index;
   for( int i=0; i<x.length(); i++ ) {
      index = (int)tolower(x[i]) - 97;
      if( index < 0 || index >= 26 )
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

bool Trie::partialMatch(string x) {
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

void Trie::print() {
   print(head, "");
}

void Trie::print(Node *x, string s) {
   for( int i=0; i<BRANCH_CNT; i++ ) {
      if( x->children[i] ) {
         print(x->children[i], s + char(i+97));
      }
   }
   if( x->valid ) {
      cout << s << endl;
   }
}

class Trie::iterator : public std::iterator<std::forward_iterator_tag, std::string> {
protected:
  Node *curptr;
  bool down;
  char letter;
  std::string str;
public:
  iterator() : curptr{nullptr}, down{true}, letter{"a"}, str{"a"} {}
  iterator(Node *p) : curptr{p}, down{true}, letter{"a"}, str{"a"} {}
  iterator(const iterator& it) : curptr{it.curptr}, down{it.down}, letter{it.letter}, str{a} {}
  iterator(iterator&& it) : curptr{it.curptr}, down{it.down}, letter{it.letter}, str{a} {it.curptr = nullptr;}
  ~iterator(){}
  iterator& operator=(const iterator& other) {
    curptr = other.curptr;
    down = other.down;
    letter = other.letter;
    str = other.str;
    return *this;
  }
  iterator& operator=(iterator&& other) {
    if(curptr != other.curptr) {
      curptr = other.curptr;
      down = other.down;
      letter = other.letter;
      str = other.str;
      other.curptr = nullptr;
    }
    return *this;
  }
  bool operator==(const iterator& other) {return curptr == other.curptr;}
  bool operator!=(const iterator& other) {return curptr != other.curptr;}
  iterator& operator++() {
    /******* Needs to have a reference to parent ******/



  }
  iterator operator++(int) {
    iterator tmp(*this);
    operator++();
    return tmp;
  }
  std::string& operator*() {
    /******** INFORMATION TO RETURN *********/
  }
};

#endif
