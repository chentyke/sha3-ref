#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "round.h"
#include "keccak_f.h"

// 预计算的24个轮常量，导出为其他文件可用
const uint64_t ROUND_CONSTANTS[24] = {
	0x0000000000000001ULL, 0x0000000000008082ULL, 0x800000000000808aULL,
	0x8000000080008000ULL, 0x000000000000808bULL, 0x0000000080000001ULL,
	0x8000000080008081ULL, 0x8000000000008009ULL, 0x000000000000008aULL,
	0x0000000000000088ULL, 0x0000000080008009ULL, 0x000000008000000aULL,
	0x000000008000808bULL, 0x800000000000008bULL, 0x8000000000008089ULL,
	0x8000000000008003ULL, 0x8000000000008002ULL, 0x8000000000000080ULL,
	0x000000000000800aULL, 0x800000008000000aULL, 0x8000000080008081ULL,
	0x8000000000008080ULL, 0x0000000080000001ULL, 0x8000000080008008ULL
};

// 线程执行函数 - 执行指定轮数的SHA3变换
void* process_rounds(void* arg) {
    thread_data_t* data = (thread_data_t*)arg;
    uint64_t** state = data->state;
    
    // 执行指定范围的轮数
    for (int i = data->start_round; i < data->end_round; i++) {
        state = sha3_round(state, ROUND_CONSTANTS[i], i);
    }
    
    return NULL;
}

// 标准的keccak_f函数 - 使用单线程处理
uint64_t **keccak_f(uint64_t **A) {
    // 使用单线程处理 - 所有24轮
    for (int i = 0; i < 24; i++) {
        A = sha3_round(A, ROUND_CONSTANTS[i], i);
    }
    return A;
}

// 注意：这个文件中虽然包含了多线程代码，但实际实现中没有使用多线程。
// 因为这个SHA3算法在单个哈希计算时，大部分时间都花在内存访问上，
// 多线程的开销会抵消加速效果。真正的多线程加速在sponge.c中实现，
// 通过同时处理多个消息来提高整体吞吐量。
