#include <iostream>
#include "Trie.h"
using namespace std;

int main() { 
   Trie t;

   t.insert("Alex");
   t.insert("Alexander");
   t.insert("David");
   t.insert("Nick");
   t.insert("Nicholas");
   t.insert("Kirsten");
   t.insert("Kate");
   t.insert("Katie");
   t.insert("Katelyn");
   t.print();
   cout << "------------\n";
   if( t.exists("alex") )
      cout << "'alex' Correctly exists!\n";
   if( !t.exists("ale") )
      cout << "'ale' Correctly doesn't exist!\n";

   return 0;
}
