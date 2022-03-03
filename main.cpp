#include "BlockChain.h"
#include <iostream>
#include <fstream>

void printValidity(const BlockChain & bc){
   for (size_t i = 0 ; i < bc.size(); ++i){
      std::cout << bc[i].display(bc.difficulty) << std::endl;
   }
   std::cout << "================================" << std::endl;
   std::cout << "Checking chain validity : \n" << (bc.isValidChain()?"OK":"FAILED") << std::endl;
   std::cout << "================================" << std::endl;
}

int main() {
   auto bc = BlockChain();

   for(size_t i = 0; i < 20; ++i){
      bc.addBlock(Block(bc.size(), "This Block data " + std::to_string(i)));
   }

   printValidity(bc);

   {
      std::ofstream ostr("save.bc", std::ios::out | std::ios::binary);
      bc.dump(ostr);
   }
   {
      std::ifstream istr("save.bc", std::ios::in | std::ios::binary);
      bc.load(istr);
   }

   std::cout << "Corrupting chain at block 5" << std::endl;
   bc[5].data() = "coucou"; // change data
   std::cout << bc[5].display(bc.difficulty) << std::endl;
   bc[5].mine(bc.difficulty); // forced mining again
   std::cout << bc[5].display(bc.difficulty) << std::endl;

   printValidity(bc);

   return 0;
}
