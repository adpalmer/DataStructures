#include <iostream>
#include "List.h"

int main() {
  List<int> l;
  l.push_front(10); // 10
  l.push_front(11); // 11, 10
  l.push_back(9); // 11, 10, 9
  
  List<int>::iterator it;
  for(it = l.begin(); it!=l.end(); ++it)
    std::cout << *it << std::endl;

  it = l.begin();
  l.insert(it, 0); // 0, 11, 10, 9
  ++it;
  l.insert(it, 100); // 0, 11, 100, 10, 9

  // normal for loop
  std::cout << std::endl;
  for(it = l.begin(); it!=l.end(); ++it)
    std::cout << *it << std::endl;
  
  // ranged increment of list
  for(int &i : l)
    i++;

  // ranged for loop
  std::cout << std::endl;
  for(int i : l)
    std::cout << i << std::endl;
  return 0;
}
