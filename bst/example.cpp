#include <iostream>
#include <list>
#include "bst.h"

int main() {
  bst<std::string,int> tree;
  tree.insert(std::make_pair("Alex Palmer", 22));
  tree.insert(std::make_pair("Nick Palmer", 18));
  tree.insert(std::make_pair("Katelyn Palmer", 20));


  auto t2 = tree;
  tree["Alex Palmer"] = 23;

  std::list<std::pair<std::string, int>> l = tree.getList();
  for(std::pair<std::string, int> i : l)
    std::cout << i.first << " - " << i.second << std::endl;
  
  std::cout << std::endl;
  l = t2.getList();
  for(auto i : l)
    std::cout << i.first << " - " << i.second << std::endl;
  
  std::cout << std::endl;
  for(auto i : t2) {
    std::cout << i.first << " _ " << i.second << std::endl;
  }

  auto i = t2.find("Alex Palmer");
  i->second = 23;
  i = t2.find("Alex Palmer");
  std::cout << "Name: " << i->first << std::endl << "Age: " << i->second << std::endl;

  return 0;
}
