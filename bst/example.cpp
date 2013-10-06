#include <iostream>
#include <list>
#include "bst.h"

int main() {
  bst<int> tree;
  tree.insert(10);
  tree.insert(11);
  tree.insert(0);
  tree.insert(9);

  std::list<int> l = tree.getList();

  for(int i : l)
    std::cout << i << std::endl;

  return 0;
}
