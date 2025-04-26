#ifndef SPONGE_H
#define SPONGE_H
#include <stdint.h>
uint8_t *sponge(uint8_t *, int32_t);
uint8_t *padding(uint8_t *, int32_t *);
#endif