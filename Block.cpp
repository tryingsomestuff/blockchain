#include "Block.h"

#include "sha256.h"

Block::Block(const uint32_t index, const std::string &data): index_(index), data_(data), nonce_(0) {
   timeStamp_ = time(nullptr);
   hash       = computeHash_();
}

void Block::mine(const uint32_t difficulty) {
   std::cout << "Mining block ... difficulty " << difficulty << " : " << data_ << std::endl;
   const std::string str(difficulty, '0');
   do {
      nonce_++;
      hash = computeHash_();
   } while (hash.substr(0, difficulty) != str);

   std::cout << "Block mined: " << hash << std::endl;
}

bool Block::isSigned(const uint32_t difficulty) const {
   const std::string str(difficulty, '0');
   return hash.substr(0, difficulty) == str;
}

bool Block::isValid(const uint32_t difficulty) const { return computeHash_() == hash; }

std::string Block::computeHash_() const {
   std::stringstream ss;
   ss << index_ << prevHash << timeStamp_ << data_ << nonce_;
   return SHA256(ss.str());
}
