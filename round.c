#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define ROL64(x, n)  (((x) << (n)) | ((x) >> (64 - (n))))

// 预计算的rho偏移量
static const int rho_offsets[25] = {
    0, 1, 62, 28, 27,  // 对应位置(0,0), (1,0), (2,0), (3,0), (4,0)
    36, 44, 6, 55, 20, // 对应位置(0,1), (1,1), (2,1), (3,1), (4,1)
    3, 10, 43, 25, 39, // 对应位置(0,2), (1,2), (2,2), (3,2), (4,2)
    41, 45, 15, 21, 8, // 对应位置(0,3), (1,3), (2,3), (3,3), (4,3)
    18, 2, 61, 56, 14  // 对应位置(0,4), (1,4), (2,4), (3,4), (4,4)
};

// 取模5函数
int mod(int a, int b)
{
  if (b < 0)
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

    /* Theta步骤 - 完全循环展开 */
    // 计算每列的XOR结果
    C[0] = A[0][0] ^ A[0][1] ^ A[0][2] ^ A[0][3] ^ A[0][4];
    C[1] = A[1][0] ^ A[1][1] ^ A[1][2] ^ A[1][3] ^ A[1][4];
    C[2] = A[2][0] ^ A[2][1] ^ A[2][2] ^ A[2][3] ^ A[2][4];
    C[3] = A[3][0] ^ A[3][1] ^ A[3][2] ^ A[3][3] ^ A[3][4];
    C[4] = A[4][0] ^ A[4][1] ^ A[4][2] ^ A[4][3] ^ A[4][4];

    // 计算D数组
    D[0] = C[4] ^ ROL64(C[1], 1);
    D[1] = C[0] ^ ROL64(C[2], 1);
    D[2] = C[1] ^ ROL64(C[3], 1);
    D[3] = C[2] ^ ROL64(C[4], 1);
    D[4] = C[3] ^ ROL64(C[0], 1);

    // 应用theta变换 - 完全展开
    A[0][0] ^= D[0]; A[0][1] ^= D[0]; A[0][2] ^= D[0]; A[0][3] ^= D[0]; A[0][4] ^= D[0];
    A[1][0] ^= D[1]; A[1][1] ^= D[1]; A[1][2] ^= D[1]; A[1][3] ^= D[1]; A[1][4] ^= D[1];
    A[2][0] ^= D[2]; A[2][1] ^= D[2]; A[2][2] ^= D[2]; A[2][3] ^= D[2]; A[2][4] ^= D[2];
    A[3][0] ^= D[3]; A[3][1] ^= D[3]; A[3][2] ^= D[3]; A[3][3] ^= D[3]; A[3][4] ^= D[3];
    A[4][0] ^= D[4]; A[4][1] ^= D[4]; A[4][2] ^= D[4]; A[4][3] ^= D[4]; A[4][4] ^= D[4];

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

    /* Rho步骤 - 使用预计算的偏移量 */
    B[0][0] = A[0][0]; // Rho的第一个元素不变
    
    // 使用预计算的rho偏移量
    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            if (x == 0 && y == 0) continue; // 跳过(0,0)
            int index = x + 5*y;
            B[x][y] = ROL64(A[x][y], rho_offsets[index]);
        }
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

    /* Pi步骤 - 使用正确的坐标变换 */
    uint64_t tempB[5][5];
    memcpy(tempB, B, sizeof(tempB));
    
    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            B[y][mod(2*x + 3*y, 5)] = tempB[x][y];
        }
    }

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

    /* Chi步骤 - 循环展开 */
    for (int y = 0; y < 5; y++) {
        uint64_t t0 = B[0][y];
        uint64_t t1 = B[1][y];
        uint64_t t2 = B[2][y];
        uint64_t t3 = B[3][y];
        uint64_t t4 = B[4][y];

        A[0][y] = t0 ^ ((~t1) & t2);
        A[1][y] = t1 ^ ((~t2) & t3);
        A[2][y] = t2 ^ ((~t3) & t4);
        A[3][y] = t3 ^ ((~t4) & t0);
        A[4][y] = t4 ^ ((~t0) & t1);
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

    /* Iota步骤 - 只作用于A[0][0] */
    A[0][0] ^= RC;

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