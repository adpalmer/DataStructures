#include <iostream>
#include "Trie.h"
using namespace std;

int main() { 
   Trie t;
   Trie t3;

   t.insert("Alex");
   t.insert("Alexander");
   t.insert("David");
   t.insert("Nick");
   t.insert("Nicholas");
   t.insert("Kirsten");
   t.insert("Kate");
   t.insert("Katie");

   Trie t2 = t;
   t3 = t;

   t.insert("Katelyn");

   // prints using Trie
   t.print();



   // get list of all usernames
   auto l = t.getList();
   std::cout << std::endl;
   for(auto &str : l) {
     std::cout << str << std::endl;
   }

  // list from trie 2 should be missint Katelyn
  std::cout << std::endl;
  t2.print();
  std::cout << std::endl;
  t3.print();

  std::cout << "deleting katelyn:" << std::endl;
  t.del("Katelyn");
  t.print();

   cout << "------------\n";
   if( t.exists("alex") )
      cout << "'alex' Correctly exists!\n";
   if( !t.exists("ale") )
      cout << "'ale' Correctly doesn't exist!\n";

   return 0;
}
