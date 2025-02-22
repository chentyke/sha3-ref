#include "round.h"

uint64_t **keccak_f(uint64_t **A)
{
	uint64_t RC[24];
	uint8_t LFSR = 0x01;

	// Generate 24 round constants
	for (int i = 0; i < 24; i++)
	{
		RC[i] = 0;
		for (int j = 0; j < 7; j++)
		{
			uint8_t bit = LFSR & 1;
			if (bit)
			{
				RC[i] |= (uint64_t)1 << ((1 << j) - 1);
			}
			uint8_t temp = LFSR;
			LFSR <<= 1;
			if (temp & 0x80)
			{
				LFSR ^= 0x71;
			}
		}
		A = sha3_round(A, RC[i], i);
	}
	return A;
}
