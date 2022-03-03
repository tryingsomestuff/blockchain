#include "BlockChain.h"
#include <iostream>

void printValidity(const BlockChain & bc){
   for (size_t i = 0 ; i < 4; ++i){
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

   bc.addBlock(Block(1, "Block 1 Data"));
   bc.addBlock(Block(2, "Block 2 Data"));
   bc.addBlock(Block(3, "Block 3 Data"));

   printValidity(bc);

   bc[2].data() = "coucou";

   printValidity(bc);

   return 0;
}
