#pragma once

#include <iostream>
#include <string>

// high level API
std::string SHA256(const std::string & data);

// low level API
#ifndef uchar
#define uchar unsigned char
#endif
#ifndef uint
#define uint  unsigned int
#endif

std::string SHA256_(const char* data);

typedef struct {
  uchar data[64];
  uint  datalen;
  uint  bitlen[2];
  uint  state[8];
} SHA256_CTX; // contexte

void SHA256Transform(SHA256_CTX *ctx, uchar data[]);
void SHA256Update   (SHA256_CTX *ctx, uchar data[], uint len);
void SHA256Final    (SHA256_CTX *ctx, uchar hash[]);

