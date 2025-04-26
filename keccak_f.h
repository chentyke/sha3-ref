#ifndef KECCAK_F_H
#define KECCAK_F_H
#include <stdint.h>
#include <pthread.h>

// 原始的单线程版keccak_f函数
uint64_t **keccak_f(uint64_t **);

// 新增的线程相关数据结构和函数
typedef struct {
    uint64_t **state;      // 状态矩阵
    int start_round;       // 起始轮数
    int end_round;         // 结束轮数
} thread_data_t;

#endif
