#include "BlockChain.h"
#include <iostream>

void printValidity(const BlockChain & bc){
   for (size_t i = 0 ; i < bc.size(); ++i){
      std::cout << "block " << i 
                << " hash " << bc[i].hash 
                << " prevHash " << bc[i].prevHash 
                << " signed? " << bc[i].isSigned(bc.difficulty) 
                << " valid? " << bc.isValid(i) 
                << std::endl;
   }
   std::cout << "Checking chain validity : \n" << bc.isValid() << std::endl;
}

int main() {
   auto bc = BlockChain();

   bc.addBlock(Block(bc.size(), "Block 1 Data"));
   bc.addBlock(Block(bc.size(), "Block 2 Data"));
   bc.addBlock(Block(bc.size(), "Block 3 Data"));

   printValidity(bc);

   bc[2].data() = "coucou";

   printValidity(bc);

   return 0;
}
