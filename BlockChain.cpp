#include "BlockChain.h"

#include <cassert>
#include <iostream>

BlockChain::BlockChain(const uint32_t difficulty): difficulty(difficulty > 0 ? difficulty : defaultDifficulty_) {
   Block b0(0, "Zero!");
   b0.mine(BlockChain::difficulty);
   chain_.push_back(b0);
}

void BlockChain::addBlock(Block&& b) {
   b.prevHash = last_().hash;
   b.mine(difficulty);
   chain_.push_back(b);
}

Block BlockChain::last_() const { return chain_.back(); }

Block& BlockChain::operator[](const size_t index) {
   assert(index < chain_.size());
   return chain_[index];
}

const Block& BlockChain::operator[](const size_t index) const {
   assert(index < chain_.size());
   return chain_[index];
}

bool BlockChain::isValidBlock(const size_t index) const {
   assert(index < chain_.size());
   return chain_[index].isValid(difficulty);
}

bool BlockChain::isValidChain() const {
   bool ret = true;
   for (size_t i = 0; i < chain_.size(); ++i) {
      ret &= chain_[i].isValid(difficulty);
      if (i > 0) { ret &= chain_[i].prevHash == chain_[i - 1].computeHash(); }
      if (!ret) std::cout << "Invalid block in chain at position " << i << std::endl;
   }
   return ret;
}
