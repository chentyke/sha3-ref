#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define ROL64(x, n)  (((x) << (n)) | ((x) >> (64 - (n))))

int mod(int a, int b)
{
  if (b < 0) // you can check for b == 0 separately and do what you want
    return mod(-a, -b);
  int ret = a % b;
  if (ret < 0)
    ret += b;
  return ret;
}

uint64_t **sha3_round(uint64_t **A, uint64_t RC, int round)
{
  uint64_t C[5];
  uint64_t D[5];
  uint64_t B[5][5];

  /* Theta step */
  for (uint8_t x = 0; x < 5; x++)
  {
    C[x] = A[x][0] ^ A[x][1] ^ A[x][2] ^ A[x][3] ^ A[x][4];
  }
  for (uint8_t x = 0; x < 5; x++)
  {
    D[x] = C[(x + 4) % 5] ^ ((C[(x + 1) % 5] << 1) | (C[(x + 1) % 5] >> 63));
  }
  for (uint8_t x = 0; x < 5; x++)
  {
    for (uint8_t y = 0; y < 5; y++)
    {
      A[x][y] = A[x][y] ^ D[x];
    }
  }

#ifdef DEBUG
  printf("[DEBUG] Round %d - After Theta step:\n", round);
  for (uint8_t ix = 0; ix < 5; ix++) {
    for (uint8_t iy = 0; iy < 5; iy++) {
      printf("A[%u][%u] = %016llx ", ix, iy, (unsigned long long) A[ix][iy]);
    }
    printf("\n");
  }
  printf("\n");
#endif

  /* Rho step */
  B[0][0] = A[0][0];
  uint8_t x = 1, y = 0;
  for (uint8_t t = 0; t < 24; t++) {
      B[x][y] = ROL64(A[x][y], ((t + 1) * (t + 2) / 2) % 64);
      uint8_t newX = y;
      uint8_t newY = (2 * x + 3 * y) % 5;
      x = newX;
      y = newY;
  }

#ifdef DEBUG
  printf("[DEBUG] Round %d - After Rho step:\n", round);
  for (uint8_t ix = 0; ix < 5; ix++) {
    for (uint8_t iy = 0; iy < 5; iy++) {
      printf("B[%u][%u] = %016llx ", ix, iy, (unsigned long long) B[ix][iy]);
    }
    printf("\n");
  }
  printf("\n");
#endif

  /* Pi step */
  uint64_t T[5][5];
  for (uint8_t px = 0; px < 5; px++) {
    for (uint8_t py = 0; py < 5; py++) {
      T[py][mod((2 * px + 3 * py), 5)] = B[px][py];
    }
  }
  memcpy(B, T, sizeof(T));

#ifdef DEBUG
  printf("[DEBUG] Round %d - After Pi step:\n", round);
  for (uint8_t ix = 0; ix < 5; ix++) {
    for (uint8_t iy = 0; iy < 5; iy++) {
      printf("B[%u][%u] = %016llx ", ix, iy, (unsigned long long) B[ix][iy]);
    }
    printf("\n");
  }
  printf("\n");
#endif

  /* Xi state */
  for (uint8_t xx = 0; xx < 5; xx++)
  {
    for (uint8_t yy = 0; yy < 5; yy++)
    {
      A[xx][yy] = B[xx][yy] ^ ((~B[mod((xx + 1), 5)][yy]) & B[mod((xx + 2), 5)][yy]);
    }
  }

#ifdef DEBUG
  printf("[DEBUG] Round %d - After Xi step:\n", round);
  for (uint8_t ix = 0; ix < 5; ix++) {
    for (uint8_t iy = 0; iy < 5; iy++) {
      printf("A[%u][%u] = %016llx ", ix, iy, (unsigned long long) A[ix][iy]);
    }
    printf("\n");
  }
  printf("\n");
#endif

  /* Last step */
  A[0][0] = A[0][0] ^ RC;

#ifdef DEBUG
  printf("[DEBUG] Round %d - After last step (RC):\n", round);
  for (uint8_t ix = 0; ix < 5; ix++) {
    for (uint8_t iy = 0; iy < 5; iy++) {
      printf("A[%u][%u] = %016llx ", ix, iy, (unsigned long long) A[ix][iy]);
    }
    printf("\n");
  }
  printf("\n");
#endif

  return A;
}