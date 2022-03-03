#include "BlockChain.h"
#include <iostream>

void printValidity(const BlockChain & bc){
   for (size_t i = 0 ; i < bc.size(); ++i){
      std::cout << bc[i].display(bc.difficulty) << std::endl;
   }
   std::cout << "================================" << std::endl;
   std::cout << "Checking chain validity : \n" << (bc.isValid()?"OK":"FAILED") << std::endl;
   std::cout << "================================" << std::endl;
}

int main() {
   auto bc = BlockChain();

   for(size_t i = 0; i < 20; ++i){
      bc.addBlock(Block(bc.size(), "This Block data " + std::to_string(i)));
   }

   std::cout << "Corrupting chain at block 5" << std::endl;
   printValidity(bc);

   bc[5].data() = "coucou";

   printValidity(bc);

   return 0;
}
