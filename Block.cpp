#include "Block.h"
#include "sha256.h"

#include <iostream>
#include <sstream>

namespace{
auto epochMuSec(){
   return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());
}
}

Block::Block(const uint32_t index, const std::string &data): index_(index), data_(data), nonce_(0) {
   timeStamp_ = epochMuSec();
   hash       = computeHash();
}

void Block::mine(const uint32_t difficulty) {
   std::cout << "Mining block ... (difficulty " << difficulty << "), data : " << data_ << std::endl;
   const std::string str(difficulty, '0');
   auto start = epochMuSec();
   const decltype(nonce_) period = 50000;
   do {
      nonce_++;
      hash = computeHash();
      if( nonce_%period == 0){
         const auto now = epochMuSec();
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

void Block::dump(std::ostream & os)const{
   writeIt(os, index_);
   writeIt(os, nonce_);
   writeIt(os, timeStamp_.count());
   for(auto c:hash) writeIt(os, c); // 64 char
   for(auto c:prevHash) writeIt(os, c); // 64 char
   writeIt(os, data_.size());
   for(auto c:data_) writeIt(os, c);
}

void Block::load(std::istream & is){
   int64_t timeStamp = 0;
   readIt(is, index_);
   readIt(is, nonce_);
   readIt(is, timeStamp);
   timeStamp_ = std::chrono::microseconds(timeStamp);
   hash.resize(64);
   for(int i = 0; i < 64; ++i) readIt(is, hash[i]);
   prevHash.resize(64);
   for(int i = 0; i < 64; ++i) readIt(is, prevHash[i]);
   size_t s = 0;
   readIt(is, s);
   data_.resize(s);
   for(int i = 0; i < s; ++i) readIt(is, data_[i]);
}
