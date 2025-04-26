#include <stdlib.h>

#include "sponge.h"
#include "keccak_f.h"

uint8_t *sponge(uint8_t *M, int32_t size)
{
  // For SHA3-256, rate = 136 bytes, word length w = 8 bytes
  int32_t r = 136;
  int32_t w = 8;

  /* Padding */
  if ((size % r) != 0)
  { 
    M = padding(M, &size);
  }
  uint64_t *nM = (uint64_t *)M;

  /* Initialization: Initialize a 5x5 state matrix S */
  uint64_t **S = (uint64_t **)calloc(5, sizeof(uint64_t *));
  for (uint64_t i = 0; i < 5; i++)
    S[i] = (uint64_t *)calloc(5, sizeof(uint64_t));

  /* Absorbing Phase */
  int32_t words_per_block = r / w;  // for SHA3-256, words_per_block = 136/8 = 17
  for (int32_t i = 0; i < size / r; i++)
  {
    for (int32_t y = 0; y < 5; y++)
    {
      for (int32_t x = 0; x < 5; x++)
      {
        if ((x + 5 * y) < words_per_block)
        {
          S[x][y] ^= *(nM + i * words_per_block + x + 5 * y);
        }
      }
    }
    // After one round of absorption, perform Keccak-f permutation
    S = keccak_f(S);
  }

  /* Squeezing Phase */
  // SHA3-256 output is 256 bits, which is 4 64-bit words
  int output_words = 256 / 64;  // 4
  uint64_t *Z = (uint64_t *)calloc(output_words, sizeof(uint64_t));
  int32_t b = 0;
  //Extract the rate part from the state matrix (in row-major order, i.e., in the order of x+5*y).
  for (int32_t y = 0; y < 5 && b < output_words; y++)
  {
    for (int32_t x = 0; x < 5 && b < output_words; x++)
    {
      if ((x + 5 * y) < words_per_block)
      {
        Z[b] = S[x][y];
        b++;
      }
    }
  }
  return (uint8_t *)Z;
}

uint8_t *padding(uint8_t *M, int32_t *S)
{
  int32_t i = *S;
  // The rate of SHA3-256 is 136 bytes.
  int32_t newS = (*S + 136 - (*S % 136));
  uint8_t *nM = malloc(newS);
  for (int32_t j = 0; j < *S; j++)
  {
    *(nM + j) = *(M + j);
  }
  // first byte to SHA3-256 padding: 0x06
  *(nM + i) = 0x06;
  i++;
  while (i < (newS - 1))
  {
    *(nM + i) = 0x00;
    i++;
  }
  // final byte：0x80
  *(nM + i) = 0x80;
  i++;
  *S = i;
  return nM;
}