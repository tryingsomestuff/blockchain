#include "Block.h"
#include "sha256.h"

#include <iostream>
#include <sstream>

Block::Block(const uint32_t index, const std::string &data): index_(index), data_(data), nonce_(0) {
   timeStamp_ = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());
   hash       = computeHash();
}

void Block::mine(const uint32_t difficulty) {
   std::cout << "Mining block ... (difficulty " << difficulty << "), data : " << data_ << std::endl;
   const std::string str(difficulty, '0');
   auto start = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());
   const decltype(nonce_) period = 50000;
   do {
      nonce_++;
      hash = computeHash();
      if( nonce_%period == 0){
         const auto now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());
         std::cout << period*1000. / (now-start).count() << "kilo hash/s" << std::endl;
         start = now;
      }
   } while (hash.substr(0, difficulty) != str);

   std::cout << "Block mined ! " << hash << std::endl;
}

bool Block::isSigned(const uint32_t difficulty) const {
   const std::string str(difficulty, '0');
   return hash.substr(0, difficulty) == str;
}

bool Block::isValid(const uint32_t difficulty) const { return computeHash() == hash; }

std::string Block::computeHash() const {
   std::stringstream ss;
   ss << index_ << prevHash << timeStamp_.count() << data_ << nonce_;
   return SHA256(ss.str());
}

std::string Block::display(const uint32_t difficulty)const{
   std::stringstream ss;
   ss << "************************"
      << "\nblock    " << index_
      << "\ndata     " << data_
      << "\nnonce    " << nonce_
      << "\ntime     " << timeStamp_.count()
      << "\nhash     " << hash 
      << "\nprevHash " << prevHash;
   if (difficulty){
      ss << "\nsigned?  " << (isSigned(difficulty)?"YES":"NO") 
         << "\nvalid?   " << (isValid(difficulty)?"YES":"NO");
   }
   ss << "\n************************";
   return ss.str();
}