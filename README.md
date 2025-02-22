# SHA-3 Implementation in C

## NOTICE
**This project is the baseline code for the COMP4023 Computer and Network Security, and all students can only modify `round.c/h` and `keccak_f.c/h` to optimize the software implementation.**

## Overview

This project implements the SHA-3 cryptographic hash function in C. The main functionality includes performing rounds of the SHA-3 algorithm on a given state array and a sponge construction for hashing messages.

## Files

- `round.c`: Contains the implementation of the SHA-3 round function and a utility function for modulus calculation.
- `round.h`: Header file for `round.c`.
- `sponge.c`: Contains the implementation of the sponge construction for hashing messages.
- `sponge.h`: Header file for `sponge.c`.

## Functions

### `int mod(int a, int b)`

Computes the modulus of two integers, handling negative values correctly.

**Parameters:**
- `a`: The dividend.
- `b`: The divisor.

**Returns:**
- The result of `a % b`, adjusted to be non-negative.

### `uint64_t **sha3_round(uint64_t **A, uint64_t RC, int round)`

Performs a single round of the SHA-3 algorithm on the given state array.

**Parameters:**
- `A`: The state array to be transformed.
- `RC`: The round constant for the current round.
- `round`: The current round number.

**Returns:**
- The transformed state array.

### `uint8_t *sponge(uint8_t *M, int32_t size)`

Implements the sponge construction for hashing messages.

**Parameters:**
- `M`: The message to be hashed.
- `size`: The size of the message in bytes.

**Returns:**
- The hash of the message.

### `uint8_t *padding(uint8_t *M, int32_t *S)`

Pads the message to make its length a multiple of the rate.

**Parameters:**
- `M`: The message to be padded.
- `S`: The size of the message in bytes.

**Returns:**
- The padded message.

## DEBUG
If you want to debug, please set the compilation flag to
`CFLAGS = -Wall -g -march=native -std=c11 -DDEBUG` in the `Makefile` file.

- In debug mode, a hash will be performed on the message `debug test`, and the results after completing the five steps of `Theta`,`Rho`, `pi`, `Chi` and `Iota` in the 24 rounds will be printed.
- In non-debug mode, the hash calculation will be executed, and then compared with the known results. Finally, the hash execution speed will be calculated.

**The intermediate results of the `debug test` are as follows:**
```
Running sha3 with sample message...
./sha3
[DEBUG] Round 0 - After Theta step:
A[0][0] = 65742067756e8d83 A[0][1] = 00000000000ce8e7 A[0][2] = 00000000000ce8e7 A[0][3] = 00000000000ce8e7 A[0][4] = 00000000000ce8e7 
A[1][0] = 6574206775641117 A[1][1] = 6574206775626564 A[1][2] = 6574206775626564 A[1][3] = e574206775626564 A[1][4] = 6574206775626564 
A[2][0] = 8000000000067473 A[2][1] = 8000000000067473 A[2][2] = 8000000000067473 A[2][3] = 8000000000067473 A[2][4] = 8000000000067473 
A[3][0] = 0000000000000000 A[3][1] = 0000000000000000 A[3][2] = 0000000000000000 A[3][3] = 0000000000000000 A[3][4] = 0000000000000000 
A[4][0] = cae840ceeac4cac8 A[4][1] = cae840ceeac4cac8 A[4][2] = cae840ceeac4cac8 A[4][3] = cae840ceeac4cac8 A[4][4] = cae840ceeac4cac8 

[DEBUG] Round 0 - After Rho step:
B[0][0] = 65742067756e8d83 B[0][1] = 00ce8e7000000000 B[0][2] = 0000000000674738 B[0][3] = 19d1ce0000000000 B[0][4] = 00000033a39c0000 
B[1][0] = cae840ceeac8222e B[1][1] = 2656465742067756 B[1][2] = d0819dd589959195 B[1][3] = 4cac9cae840ceeac B[1][4] = 95d0819dd5899591 
B[2][0] = e000000000019d1c B[2][1] = 00000000019d1ce0 B[2][2] = 33a39c0000000000 B[2][3] = 000000033a39c000 B[2][4] = 700000000000ce8e 
B[3][0] = 0000000000000000 B[3][1] = 0000000000000000 B[3][2] = 0000000000000000 B[3][3] = 0000000000000000 B[3][4] = 0000000000000000 
B[4][0] = 7756265646574206 B[4][1] = 0ceeac4cac8cae84 B[4][2] = 6265646574206775 B[4][3] = e840ceeac4cac8ca B[4][4] = 1033bab132b232ba 

[DEBUG] Round 0 - After Pi step:
B[0][0] = 65742067756e8d83 B[0][1] = 0000000000000000 B[0][2] = cae840ceeac8222e B[0][3] = 7756265646574206 B[0][4] = e000000000019d1c 
B[1][0] = 2656465742067756 B[1][1] = 0ceeac4cac8cae84 B[1][2] = 00000000019d1ce0 B[1][3] = 00ce8e7000000000 B[1][4] = 0000000000000000 
B[2][0] = 33a39c0000000000 B[2][1] = 0000000000674738 B[2][2] = 0000000000000000 B[2][3] = d0819dd589959195 B[2][4] = 6265646574206775 
B[3][0] = 0000000000000000 B[3][1] = 4cac9cae840ceeac B[3][2] = e840ceeac4cac8ca B[3][3] = 000000033a39c000 B[3][4] = 19d1ce0000000000 
B[4][0] = 1033bab132b232ba B[4][1] = 700000000000ce8e B[4][2] = 00000033a39c0000 B[4][3] = 0000000000000000 B[4][4] = 95d0819dd5899591 

[DEBUG] Round 0 - After Xi step:
A[0][0] = 74d5b867756e8d83 A[0][1] = 0000000000634138 A[0][2] = cae840ceeac8222e A[0][3] = a75737d3cfc2d393 A[0][4] = 826564657421fa69 
A[1][0] = 2656465742067756 A[1][1] = 404230e228840600 A[1][2] = e840ceeac557d42a A[1][3] = 00ce8e7232284000 A[1][4] = 19908a0000000000 
A[2][0] = 239026b132b232ba A[2][1] = 300000000067473a A[2][2] = 0000001123140000 A[2][3] = d0819dd589959195 A[2][4] = e66565f8a1a9f2e4 
A[3][0] = 65440046454c8d01 A[3][1] = 4cac9cae840ceeac A[3][2] = 22a88e268c8aeae4 A[3][3] = 775626557c6e8206 A[3][4] = 79d1ce000000080c 
A[4][0] = 1231fca130b240ee A[4][1] = 7ceeac4cac8c600a A[4][2] = 00000033a2891cc0 A[4][3] = 0088882000000000 A[4][4] = 95d0819dd5899591 

[DEBUG] Round 0 - After last step (RC):
A[0][0] = 74d5b867756e8d82 A[0][1] = 0000000000634138 A[0][2] = cae840ceeac8222e A[0][3] = a75737d3cfc2d393 A[0][4] = 826564657421fa69 
A[1][0] = 2656465742067756 A[1][1] = 404230e228840600 A[1][2] = e840ceeac557d42a A[1][3] = 00ce8e7232284000 A[1][4] = 19908a0000000000 
A[2][0] = 239026b132b232ba A[2][1] = 300000000067473a A[2][2] = 0000001123140000 A[2][3] = d0819dd589959195 A[2][4] = e66565f8a1a9f2e4 
A[3][0] = 65440046454c8d01 A[3][1] = 4cac9cae840ceeac A[3][2] = 22a88e268c8aeae4 A[3][3] = 775626557c6e8206 A[3][4] = 79d1ce000000080c 
A[4][0] = 1231fca130b240ee A[4][1] = 7ceeac4cac8c600a A[4][2] = 00000033a2891cc0 A[4][3] = 0088882000000000 A[4][4] = 95d0819dd5899591 

[DEBUG] Round 1 - After Theta step:
A[0][0] = a147995fa5abeece A[0][1] = d5922138d0a62274 A[0][2] = 1f7a61f63a0d4162 A[0][3] = 72c516eb1f07b0df A[0][4] = 57f7455da4e49925 
A[1][0] = f7b0505215da9dda A[1][1] = 91a426e77f58ec8c A[1][2] = 39a6d8ef928b3ea6 A[1][3] = d128987765f4aa8c A[1][4] = c8769c0557dcea8c 
A[2][0] = bf156faacc07d140 A[2][1] = ac85491bfed2a4c0 A[2][2] = 9c85490adda1e3fa A[2][3] = 4c04d4ce7720726f A[2][4] = 7ae02ce35f1c111e 
A[3][0] = b73e6c0caaccc89b A[3][1] = 9ed6f0e46b8cab36 A[3][2] = f0d2e26c630aaf7e A[3][3] = a52c4a1f93eec79c A[3][4] = ababa24aef804d96 
A[4][0] = 21e95004495bcd70 A[4][1] = 4f3600e9d565ed94 A[4][2] = 33d8ac96db60915e A[4][3] = 3350248579e98d9e A[4][4] = a6082d38ac60180f 

[DEBUG] Round 1 - After Rho step:
B[0][0] = a147995fa5abeece B[0][1] = 0a62274d5922138d B[0][2] = fbd30fb1d06a0b10 B[0][3] = 0f61bee58a2dd63e B[0][4] = 1576939264955fdd 
B[1][0] = ef60a0a42bb53bb5 B[1][1] = 8ec8c91a426e77f5 B[1][2] = 9b63be4a2cfa98e6 B[1][3] = 95519a25130eecbe B[1][4] = 21da70155f73aa33 
B[2][0] = 2fc55beab301f450 B[2][1] = 215246ffb4a9302b B[2][2] = 0f1fd4e42a4856ed B[2][3] = 6a673b903937a602 B[2][4] = cf5c059c6be38223 
B[3][0] = caaccc89bb73e6c0 B[3][1] = 9b4f6b787235c655 B[3][2] = d8c6155efde1a5c4 B[3][3] = 43f27dd8f394a589 B[3][4] = 96ababa24aef804d 
B[4][0] = 224ade6b810f4a80 B[4][1] = 0e9d565ed944f360 B[4][2] = b048af19ec564b6d B[4][3] = 50248579e98d9e33 B[4][4] = 0b4e2b180603e982 

[DEBUG] Round 1 - After Pi step:
B[0][0] = a147995fa5abeece B[0][1] = caaccc89bb73e6c0 B[0][2] = ef60a0a42bb53bb5 B[0][3] = 224ade6b810f4a80 B[0][4] = 2fc55beab301f450 
B[1][0] = 8ec8c91a426e77f5 B[1][1] = 0e9d565ed944f360 B[1][2] = 215246ffb4a9302b B[1][3] = 0a62274d5922138d B[1][4] = 9b4f6b787235c655 
B[2][0] = 0f1fd4e42a4856ed B[2][1] = fbd30fb1d06a0b10 B[2][2] = d8c6155efde1a5c4 B[2][3] = 9b63be4a2cfa98e6 B[2][4] = b048af19ec564b6d 
B[3][0] = 43f27dd8f394a589 B[3][1] = 95519a25130eecbe B[3][2] = 50248579e98d9e33 B[3][3] = 6a673b903937a602 B[3][4] = 0f61bee58a2dd63e 
B[4][0] = 0b4e2b180603e982 B[4][1] = cf5c059c6be38223 B[4][2] = 1576939264955fdd B[4][3] = 96ababa24aef804d B[4][4] = 21da70155f73aa33 

[DEBUG] Round 1 - After Xi step:
A[0][0] = a0508dbb8dabeec6 A[0][1] = 3beec528bb59eed0 A[0][2] = 37e4b1a462f5be71 A[0][3] = b34b4669a5d7c2e2 A[0][4] = 0fc5dfeb3f43fd78 
A[1][0] = ce28e00293fad6f5 A[1][1] = 0a9dc65ada4017ce A[1][2] = 2172c6deb4a52a18 A[1][3] = 6a6626dd4827358d A[1][4] = 946e7b9c701c5247 
A[2][0] = 0713d6e42e4b1eef A[2][1] = b1df0a29b88b0911 A[2][2] = dd9407dcf9f1e408 A[2][3] = 0feb3e686e3298ab A[2][4] = 90d2ef09b904636c 
A[3][0] = e3f3ed9f523ca3c5 A[3][1] = 95f15224831e887e A[3][2] = ba24a55de2adbe13 A[3][3] = 4a276fd9b837ec82 A[3][4] = 0164b50f2a2d827e 
A[4][0] = 05c66b184447f8b3 A[4][1] = cb4d17ca2be79303 A[4][2] = 1564d5c9f09d5fd7 A[4][3] = 9e8b8aa612cf9140 A[4][4] = b1d050051f47a836 

[DEBUG] Round 1 - After last step (RC):
A[0][0] = a0508dbb8dab6e44 A[0][1] = 3beec528bb59eed0 A[0][2] = 37e4b1a462f5be71 A[0][3] = b34b4669a5d7c2e2 A[0][4] = 0fc5dfeb3f43fd78 
A[1][0] = ce28e00293fad6f5 A[1][1] = 0a9dc65ada4017ce A[1][2] = 2172c6deb4a52a18 A[1][3] = 6a6626dd4827358d A[1][4] = 946e7b9c701c5247 
A[2][0] = 0713d6e42e4b1eef A[2][1] = b1df0a29b88b0911 A[2][2] = dd9407dcf9f1e408 A[2][3] = 0feb3e686e3298ab A[2][4] = 90d2ef09b904636c 
A[3][0] = e3f3ed9f523ca3c5 A[3][1] = 95f15224831e887e A[3][2] = ba24a55de2adbe13 A[3][3] = 4a276fd9b837ec82 A[3][4] = 0164b50f2a2d827e 
A[4][0] = 05c66b184447f8b3 A[4][1] = cb4d17ca2be79303 A[4][2] = 1564d5c9f09d5fd7 A[4][3] = 9e8b8aa612cf9140 A[4][4] = b1d050051f47a836 

[DEBUG] Round 2 - After Theta step:
A[0][0] = 637b858c95577a87 A[0][1] = f8c5cd1fa3a5fa13 A[0][2] = f4cfb9937a09aab2 A[0][3] = 70604e5ebd2bd621 A[0][4] = cceed7dc27bfe9bb 
A[1][0] = 363e94562d67c7e9 A[1][1] = f28bb20e64dd06d2 A[1][2] = d964b28a0a383b04 A[1][3] = 92705289f6ba2491 A[1][4] = 6c780fc8ce81435b 
A[2][0] = 1217eb42a84464af A[2][1] = a4db378f3e847351 A[2][2] = c8903a7a7ffe9e48 A[2][3] = 1aef03cee83de2eb A[2][4] = 85d6d2af3f0b192c 
A[3][0] = fefa009ecf51b1d7 A[3][1] = 88f8bf251e739a6c A[3][2] = a72d485c7fc0ac01 A[3][3] = 572e82d8255afe90 A[3][4] = 1c6d580eb740906c 
A[4][0] = a30b6a4378f40119 A[4][1] = 6d80169117546aa9 A[4][2] = b3a9d492cc2ea67d A[4][3] = 38468bfd2e7c68ea A[4][4] = 171d515e23f4519c 

[DEBUG] Round 2 - After Rho step:
B[0][0] = 637b858c95577a87 B[0][1] = 3a5fa13f8c5cd1fa B[0][2] = a67dcc9bd04d5597 B[0][3] = 57ac42e0c09cbd7a B[0][4] = 5f709effa6ef33bb 
B[1][0] = 6c7d28ac5acf8fd2 B[1][1] = d06d2f28bb20e64d B[1][2] = 92ca2828e0ec1365 B[1][3] = 4492324e0a513ed7 B[1][4] = b1e03f233a050d6d 
B[2][0] = c485fad0aa11192b B[2][1] = 36cde3cfa11cd469 B[2][2] = f4f2464481d3d3ff B[2][3] = 81e7741ef1758d77 B[2][4] = 90bada55e7e16325 
B[3][0] = ecf51b1d7fefa009 B[3][1] = 36447c5f928f39cd B[3][2] = b8ff8158034e5a90 B[3][3] = 5b04ab5fd20ae5d0 B[3][4] = 6c1c6d580eb74090 
B[4][0] = 1bc7a008cd185b52 B[4][1] = 69117546aa96d801 B[4][2] = 17533ed9d4ea4966 B[4][3] = 468bfd2e7c68ea38 B[4][4] = 545788fd146705c7 

[DEBUG] Round 2 - After Pi step:
B[0][0] = 637b858c95577a87 B[0][1] = ecf51b1d7fefa009 B[0][2] = 6c7d28ac5acf8fd2 B[0][3] = 1bc7a008cd185b52 B[0][4] = c485fad0aa11192b 
B[1][0] = d06d2f28bb20e64d B[1][1] = 69117546aa96d801 B[1][2] = 36cde3cfa11cd469 B[1][3] = 3a5fa13f8c5cd1fa B[1][4] = 36447c5f928f39cd 
B[2][0] = f4f2464481d3d3ff B[2][1] = a67dcc9bd04d5597 B[2][2] = b8ff8158034e5a90 B[2][3] = 92ca2828e0ec1365 B[2][4] = 17533ed9d4ea4966 
B[3][0] = 5b04ab5fd20ae5d0 B[3][1] = 4492324e0a513ed7 B[3][2] = 468bfd2e7c68ea38 B[3][3] = 81e7741ef1758d77 B[3][4] = 57ac42e0c09cbd7a 
B[4][0] = 545788fd146705c7 B[4][1] = 90bada55e7e16325 B[4][2] = 5f709effa6ef33bb B[4][3] = 6c1c6d580eb74090 B[4][4] = b1e03f233a050d6d 

[DEBUG] Round 2 - After Xi step:
A[0][0] = 47e9c5c895846b35 A[0][1] = 6a9993842fa6a59f A[0][2] = e44f28bc588d8542 A[0][3] = 9b47a808adb85957 A[0][4] = c596f850ee715909 
A[1][0] = db698633e928c24d A[1][1] = 29934702a086f241 A[1][2] = 70cd9fe9dd3c7441 A[1][3] = 3b7af5299d4d5de8 A[1][4] = 76e83c7f929b8dd5 
A[2][0] = f0a146e485b6d3f8 A[2][1] = 3655048a35ed14b7 A[2][2] = a18f838981c94b13 A[2][3] = fed22168ee6e53e5 A[2][4] = b71303daeeeb4963 
A[3][0] = 782cae5f531a9fd0 A[3][1] = 28d73346125fbedf A[3][2] = 6686dd2e24686678 A[3][3] = 9224f41e307d9635 A[3][4] = 13a98230408cad78 
A[4][0] = c453a2dd3e47818f A[4][1] = 91babe1767f13b25 A[4][2] = 4df05dbc07ff6392 A[4][3] = 4c046c6f0ef3c038 A[4][4] = 83a03b2c2a8b2da9 

[DEBUG] Round 2 - After last step (RC):
A[0][0] = c7e9c5c89584ebbf A[0][1] = 6a9993842fa6a59f A[0][2] = e44f28bc588d8542 A[0][3] = 9b47a808adb85957 A[0][4] = c596f850ee715909 
A[1][0] = db698633e928c24d A[1][1] = 29934702a086f241 A[1][2] = 70cd9fe9dd3c7441 A[1][3] = 3b7af5299d4d5de8 A[1][4] = 76e83c7f929b8dd5 
A[2][0] = f0a146e485b6d3f8 A[2][1] = 3655048a35ed14b7 A[2][2] = a18f838981c94b13 A[2][3] = fed22168ee6e53e5 A[2][4] = b71303daeeeb4963 
A[3][0] = 782cae5f531a9fd0 A[3][1] = 28d73346125fbedf A[3][2] = 6686dd2e24686678 A[3][3] = 9224f41e307d9635 A[3][4] = 13a98230408cad78 
A[4][0] = c453a2dd3e47818f A[4][1] = 91babe1767f13b25 A[4][2] = 4df05dbc07ff6392 A[4][3] = 4c046c6f0ef3c038 A[4][4] = 83a03b2c2a8b2da9 

[DEBUG] Round 3 - After Theta step:
A[0][0] = 8f1ffce0d93cf7f7 A[0][1] = 226faaac631eb9d7 A[0][2] = acb911941435990a A[0][3] = d3b19120e100451f A[0][4] = 8d60c178a2c94541 
A[1][0] = 91f26e312a6124c5 A[1][1] = 6308af0063cf14c9 A[1][2] = 3a5677eb1e7592c9 A[1][3] = 71e11d2b5e04bb60 A[1][4] = 3c73d47d51d26b5d 
A[2][0] = 50e4bd58354abffd A[2][1] = 9610ff36851178b2 A[2][2] = 01ca783531352716 A[2][3] = 5e97dad45e923fe0 A[2][4] = 1756f8665e172566 
A[3][0] = f9ec6160966f6059 A[3][1] = a917fc79d72a4156 A[3][2] = e7461211e11d99f1 A[3][3] = 13e43b21f50869bc A[3][4] = 92694d0f85f952f1 
A[4][0] = 5c7fc99569566bcd A[4][1] = 0996d55f30e0d167 A[4][2] = d5dc36f450ee89d0 A[4][3] = d428072759e22a7a A[4][4] = 1b8c50647d9ac7eb 

[DEBUG] Round 3 - After Rho step:
B[0][0] = 8f1ffce0d93cf7f7 B[0][1] = 31eb9d7226faaac6 B[0][2] = 65c88ca0a1acc855 B[0][3] = 008a3fa7632241c2 B[0][4] = 05e28b2515063583 
B[1][0] = 23e4dc6254c2498b B[1][1] = f14c96308af0063c B[1][2] = 59dfac79d64b24e9 B[1][3] = 976c0e3c23a56bc0 B[1][4] = f1cf51f54749ad74 
B[2][0] = 54392f560d52afff B[2][1] = 843fcda1445e2ca5 B[2][2] = a938b00e53c1a989 B[2][3] = ed6a2f491ff02f4b B[2][4] = c2eadf0ccbc2e4ac 
B[3][0] = 0966f6059f9ec616 B[3][1] = ab548bfe3ceb9520 B[3][2] = 23c23b33e3ce8c24 B[3][3] = 643ea10d37827c87 B[3][4] = f192694d0f85f952 
B[4][0] = ab4ab35e6ae3fe4c B[4][1] = 55f30e0d1670996d B[4][2] = 7744e86aee1b7a28 B[4][3] = 28072759e22a7ad4 B[4][4] = 14191f66b1fac6e3 

[DEBUG] Round 3 - After Pi step:
B[0][0] = 8f1ffce0d93cf7f7 B[0][1] = 0966f6059f9ec616 B[0][2] = 23e4dc6254c2498b B[0][3] = ab4ab35e6ae3fe4c B[0][4] = 54392f560d52afff 
B[1][0] = f14c96308af0063c B[1][1] = 55f30e0d1670996d B[1][2] = 843fcda1445e2ca5 B[1][3] = 31eb9d7226faaac6 B[1][4] = ab548bfe3ceb9520 
B[2][0] = a938b00e53c1a989 B[2][1] = 65c88ca0a1acc855 B[2][2] = 23c23b33e3ce8c24 B[2][3] = 59dfac79d64b24e9 B[2][4] = 7744e86aee1b7a28 
B[3][0] = 643ea10d37827c87 B[3][1] = 976c0e3c23a56bc0 B[3][2] = 28072759e22a7ad4 B[3][3] = ed6a2f491ff02f4b B[3][4] = 008a3fa7632241c2 
B[4][0] = 14191f66b1fac6e3 B[4][1] = c2eadf0ccbc2e4ac B[4][2] = 05e28b2515063583 B[4][3] = f192694d0f85f952 B[4][4] = f1cf51f54749ad74 

[DEBUG] Round 3 - After Xi step:
A[0][0] = 872fdcee883d5e76 A[0][1] = 296e76a53e128606 A[0][2] = 0024ee70f742c98b A[0][3] = e35e9357bae2fa65 A[0][4] = 00394f56cf42c5f7 
A[1][0] = b54a9731aef2523a A[1][1] = c7d70c111471baed A[1][2] = 8c3ac9e9447e5e75 A[1][3] = 95cb9e722f4aa1c4 A[1][4] = abde9c7b3dcb94e2 
A[2][0] = b939ae6cd3b92be9 A[2][1] = 254a5da069ee4c79 A[2][2] = 2622b317f6ca8927 A[2][3] = 494fec7dd64ef4f9 A[2][4] = 8601a83aea52d61c 
A[3][0] = ef38418d7f864d93 A[3][1] = 9e682e3d37b969d2 A[3][2] = 0a03731ba2ea32dc A[3][3] = e722bd5b7f922947 A[3][4] = 04ba11a56b304349 
A[4][0] = 64591d76b33ac6eb A[4][1] = 967bd704cba2fdc5 A[4][2] = 81f98aa4151a11a7 A[4][3] = e133656d0b9df9d0 A[4][4] = 5a8bd15d77e0bd74 

[DEBUG] Round 3 - After last step (RC):
A[0][0] = 072fdcee083dde76 A[0][1] = 296e76a53e128606 A[0][2] = 0024ee70f742c98b A[0][3] = e35e9357bae2fa65 A[0][4] = 00394f56cf42c5f7 
A[1][0] = b54a9731aef2523a A[1][1] = c7d70c111471baed A[1][2] = 8c3ac9e9447e5e75 A[1][3] = 95cb9e722f4aa1c4 A[1][4] = abde9c7b3dcb94e2 
A[2][0] = b939ae6cd3b92be9 A[2][1] = 254a5da069ee4c79 A[2][2] = 2622b317f6ca8927 A[2][3] = 494fec7dd64ef4f9 A[2][4] = 8601a83aea52d61c 
A[3][0] = ef38418d7f864d93 A[3][1] = 9e682e3d37b969d2 A[3][2] = 0a03731ba2ea32dc A[3][3] = e722bd5b7f922947 A[3][4] = 04ba11a56b304349 
A[4][0] = 64591d76b33ac6eb A[4][1] = 967bd704cba2fdc5 A[4][2] = 81f98aa4151a11a7 A[4][3] = e133656d0b9df9d0 A[4][4] = 5a8bd15d77e0bd74 

[DEBUG] Round 4 - After Theta step:
A[0][0] = 4e288989c13bb752 A[0][1] = 606923c2f714ef22 A[0][2] = 4923bb173e44a0af A[0][3] = aa59c63073e49341 A[0][4] = 493e1a310644acd3 
A[1][0] = 92760633fb3c64f7 A[1][1] = e0eb9d1341bf8c20 A[1][2] = ab0658eb11b068b8 A[1][3] = b2f70f707a849709 A[1][4] = 8ce20d796805a22f 
A[2][0] = 481c9e07c32b514a A[2][1] = d46f6dcb797c36da A[2][2] = d707837ce658f384 A[2][3] = b86adc16c6dc8e5a A[2][4] = 77249851fac0acbf 
A[3][0] = 0ae0acdd2cf95d9a A[3][1] = 7bb0c36d64c679db A[3][2] = efdb9e4bf19522d5 A[3][3] = 02fa500b2ced394e A[3][4] = e162fcf5384f5340 
A[4][0] = 66979d5624d6e6ab A[4][1] = 94b557245c4edd85 A[4][2] = 83370a8482f631e7 A[4][3] = e3fde54d9c71d990 A[4][4] = 5845517de00c9d34 

[DEBUG] Round 4 - After Rho step:
B[0][0] = 4e288989c13bb752 B[0][1] = 714ef22606923c2f B[0][2] = 491dd8b9f225057a B[0][3] = c9268354b38c60e7 B[0][4] = 68c41912b34d24f8 
B[1][0] = 24ec0c67f678c9ef B[1][1] = f8c20e0eb9d1341b B[1][2] = 1963ac46c1a2e2ac B[1][3] = 92e1365ee1ee0f50 B[1][4] = 338835e5a01688be 
B[2][0] = 92072781f0cad452 B[2][1] = 1bdb72de5f0db6b5 B[2][2] = c79c26b83c1be732 B[2][3] = 6e0b636e472d5c35 B[2][4] = eee4930a3f581597 
B[3][0] = d2cf95d9a0ae0acd B[3][1] = edbdd861b6b2633c B[3][2] = 97e32a45abdfb73c B[3][3] = 01659da729c05f4a B[3][4] = 40e162fcf5384f53 
B[4][0] = b126b7355b34bcea B[4][1] = 7245c4edd8594b55 B[4][2] = 7b18f3c19b854241 B[4][3] = fde54d9c71d990e3 B[4][4] = 545f7803274d1611 

[DEBUG] Round 4 - After Pi step:
B[0][0] = 4e288989c13bb752 B[0][1] = d2cf95d9a0ae0acd B[0][2] = 24ec0c67f678c9ef B[0][3] = b126b7355b34bcea B[0][4] = 92072781f0cad452 
B[1][0] = f8c20e0eb9d1341b B[1][1] = 7245c4edd8594b55 B[1][2] = 1bdb72de5f0db6b5 B[1][3] = 714ef22606923c2f B[1][4] = edbdd861b6b2633c 
B[2][0] = c79c26b83c1be732 B[2][1] = 491dd8b9f225057a B[2][2] = 97e32a45abdfb73c B[2][3] = 1963ac46c1a2e2ac B[2][4] = 7b18f3c19b854241 
B[3][0] = 01659da729c05f4a B[3][1] = 92e1365ee1ee0f50 B[3][2] = fde54d9c71d990e3 B[3][3] = 6e0b636e472d5c35 B[3][4] = c9268354b38c60e7 
B[4][0] = 545f7803274d1611 B[4][1] = eee4930a3f581597 B[4][2] = 68c41912b34d24f8 B[4][3] = 40e162fcf5384f53 B[4][4] = 338835e5a01688be 

[DEBUG] Round 4 - After Xi step:
A[0][0] = 4934a939c5317472 A[0][1] = dbd78dc9828a0ee7 A[0][2] = a0cc046656aac8e7 A[0][3] = b907bb759a147e6a A[0][4] = 80070401f9cfd413 
A[1][0] = f8a39709b8112c53 A[1][1] = e0a5e2abd9934155 A[1][2] = 73df37460f0db676 A[1][3] = 1746b10e009f203e A[1][4] = 6d9bd87596ba439a 
A[2][0] = 938646b83a16e723 A[2][1] = 251959b9ec3515fd A[2][2] = 97e33a4729db9324 A[2][3] = 1983acd671b2e1ee A[2][4] = 4990c7609b97ca59 
A[3][0] = 0b451c2fe9f2fe08 A[3][1] = 82ea328f61480518 A[3][2] = f9cd49f935e959e4 A[3][3] = df0df66f4d29ec9d A[3][4] = 49218154e34434a7 
A[4][0] = e49d7e051f8d1618 A[4][1] = cee4d32e67095487 A[4][2] = 73d76b8aba4812e8 A[4][3] = 00a922fef1ba4f56 A[4][4] = 5e30ed85a626ab92 

[DEBUG] Round 4 - After last step (RC):
A[0][0] = 4934a939c531f4f9 A[0][1] = dbd78dc9828a0ee7 A[0][2] = a0cc046656aac8e7 A[0][3] = b907bb759a147e6a A[0][4] = 80070401f9cfd413 
A[1][0] = f8a39709b8112c53 A[1][1] = e0a5e2abd9934155 A[1][2] = 73df37460f0db676 A[1][3] = 1746b10e009f203e A[1][4] = 6d9bd87596ba439a 
A[2][0] = 938646b83a16e723 A[2][1] = 251959b9ec3515fd A[2][2] = 97e33a4729db9324 A[2][3] = 1983acd671b2e1ee A[2][4] = 4990c7609b97ca59 
A[3][0] = 0b451c2fe9f2fe08 A[3][1] = 82ea328f61480518 A[3][2] = f9cd49f935e959e4 A[3][3] = df0df66f4d29ec9d A[3][4] = 49218154e34434a7 
A[4][0] = e49d7e051f8d1618 A[4][1] = cee4d32e67095487 A[4][2] = 73d76b8aba4812e8 A[4][3] = 00a922fef1ba4f56 A[4][4] = 5e30ed85a626ab92 

[DEBUG] Round 5 - After Theta step:
A[0][0] = 6c0bf7dca13431e2 A[0][1] = fee8d32ce68fcbfc A[0][2] = 85f35a8332af0dfc A[0][3] = 9c38e590fe11bb71 A[0][4] = a5385ae49dca1108 
A[1][0] = 1152950be1612049 A[1][1] = 0954e0a980e34d4f A[1][2] = 9a2e3544567dba6c A[1][3] = feb7b30c59ef2c24 A[1][4] = 846ada77cfca4f80 
A[2][0] = 4e1e4de3e4c0aa6a A[2][1] = f88152e232e358b4 A[2][2] = 4a7b311cf70dde6d A[2][3] = c41ba78daf64aca7 A[2][4] = 9408cc3b45418710 
A[3][0] = 7444416ad68edd23 A[3][1] = fdeb6fca5e342633 A[3][2] = 86cc14bc0a957acf A[3][3] = a00cab2a7255cfb6 A[3][4] = 3620dc11dc38178c 
A[4][0] = 148c51a3e9265dd6 A[4][1] = 3ef5fc8891a21f49 A[4][2] = 83c6442c4ce35926 A[4][3] = f0b80d5807110498 A[4][4] = ae21c223508de05c 

[DEBUG] Round 5 - After Rho step:
B[0][0] = 6c0bf7dca13431e2 B[0][1] = 68fcbfcfee8d32ce B[0][2] = 2f9ad41995786fe4 B[0][3] = 2376e33871cb21fc B[0][4] = 6b927728442294e1 
B[1][0] = 22a52a17c2c24092 B[1][1] = 34d4f0954e0a980e B[1][2] = b8d51159f6e9b268 B[1][3] = e5849fd6f6618b3d B[1][4] = 11ab69df3f293e02 
B[2][0] = 93879378f9302a9a B[2][1] = 2054b88cb8d62d3e B[2][2] = 6ef36a53d988e7b8 B[2][3] = d3c6d7b25653e20d B[2][4] = 1281198768a830e2 
B[3][0] = ad68edd237444416 B[3][1] = 19fef5b7e52f1a13 B[3][2] = 78152af59f0d9829 B[3][3] = 654e4ab9f6d40195 B[3][4] = 8c3620dc11dc3817 
B[4][0] = 1f4932eeb0a4628d B[4][1] = c8891a21f493ef5f B[4][2] = 71ac9341e3221626 B[4][3] = b80d5807110498f0 B[4][4] = 7088d42378172b88 

[DEBUG] Round 5 - After Pi step:
B[0][0] = 6c0bf7dca13431e2 B[0][1] = ad68edd237444416 B[0][2] = 22a52a17c2c24092 B[0][3] = 1f4932eeb0a4628d B[0][4] = 93879378f9302a9a 
B[1][0] = 34d4f0954e0a980e B[1][1] = c8891a21f493ef5f B[1][2] = 2054b88cb8d62d3e B[1][3] = 68fcbfcfee8d32ce B[1][4] = 19fef5b7e52f1a13 
B[2][0] = 6ef36a53d988e7b8 B[2][1] = 2f9ad41995786fe4 B[2][2] = 78152af59f0d9829 B[2][3] = b8d51159f6e9b268 B[2][4] = 71ac9341e3221626 
B[3][0] = 654e4ab9f6d40195 B[3][1] = e5849fd6f6618b3d B[3][2] = b80d5807110498f0 B[3][3] = d3c6d7b25653e20d B[3][4] = 2376e33871cb21fc 
B[4][0] = 7088d42378172b88 B[4][1] = 1281198768a830e2 B[4][2] = 6b927728442294e1 B[4][3] = 8c3620dc11dc3817 B[4][4] = 11ab69df3f293e02 

[DEBUG] Round 5 - After Xi step:
A[0][0] = 2628fd9e30b45652 A[0][1] = 8a7a29ca362c44b6 A[0][2] = 7aa42866c5cbd093 A[0][3] = 8f4832fea0c4e2ad A[0][4] = f3879138fb302ebe 
A[1][0] = 35d8f03d685e980b A[1][1] = 088d11e796926f46 A[1][2] = a05ce88eb8d62dee A[1][3] = 2bfe796dee9f72cb A[1][4] = 1bac958ff5e63bcb 
A[2][0] = 7e73fe51d18bcdb0 A[2][1] = 3d9bd4189df05f26 A[2][2] = 3b870ddddb2f9c28 A[2][3] = b4e53115f765aa7a A[2][4] = 61259b86ed020824 
A[3][0] = 694d696577f411f7 A[3][1] = 48ec7b86e125cf29 A[3][2] = b828501093c4d8e2 A[3][3] = c08fc590f673a085 A[3][4] = a1727118b1db2164 
A[4][0] = 605cd422361da384 A[4][1] = 52000ba6a83b9bab A[4][2] = 6bc2e7a07c36b9cd A[4][3] = ec82addd5fd52855 A[4][4] = 19d30d583b262e03 

[DEBUG] Round 5 - After last step (RC):
A[0][0] = 2628fd9eb0b45653 A[0][1] = 8a7a29ca362c44b6 A[0][2] = 7aa42866c5cbd093 A[0][3] = 8f4832fea0c4e2ad A[0][4] = f3879138fb302ebe 
A[1][0] = 35d8f03d685e980b A[1][1] = 088d11e796926f46 A[1][2] = a05ce88eb8d62dee A[1][3] = 2bfe796dee9f72cb A[1][4] = 1bac958ff5e63bcb 
A[2][0] = 7e73fe51d18bcdb0 A[2][1] = 3d9bd4189df05f26 A[2][2] = 3b870ddddb2f9c28 A[2][3] = b4e53115f765aa7a A[2][4] = 61259b86ed020824 
A[3][0] = 694d696577f411f7 A[3][1] = 48ec7b86e125cf29 A[3][2] = b828501093c4d8e2 A[3][3] = c08fc590f673a085 A[3][4] = a1727118b1db2164 
A[4][0] = 605cd422361da384 A[4][1] = 52000ba6a83b9bab A[4][2] = 6bc2e7a07c36b9cd A[4][3] = ec82addd5fd52855 A[4][4] = 19d30d583b262e03 

[DEBUG] Round 6 - After Theta step:
A[0][0] = d050ae538c90f6a0 A[0][1] = 7c027a070a08e445 A[0][2] = 8cdc7babf9ef7060 A[0][3] = 793061339ce0425e A[0][4] = 05ffc2f5c7148e4d 
A[1][0] = c4beb5c66a9ecfaf A[1][1] = f9eb541c945238e2 A[1][2] = 513aad75ba167a4a A[1][3] = da983c96ec5f256f A[1][4] = eacad074f7266c6f 
A[2][0] = 23c1f711099351a8 A[2][1] = 6029dd5845e8c33e A[2][2] = 6635049d03370030 A[2][3] = e95738552f7d3662 A[2][4] = 3c9792c6351a943c 
A[3][0] = 9d7dd521f700b27e A[3][1] = bcdcc7c261d16ca0 A[3][2] = 4c18ec5413307b6b A[3][3] = 34bf79d47687030c A[3][4] = 5542cd5c312f82ed 
A[4][0] = cc5a9db145ee3892 A[4][1] = fe064235dbc800bd A[4][2] = c7c4ae330fc522db A[4][3] = 4084e44e2c26b343 A[4][4] = b5d544cb48d5b515 

[DEBUG] Round 6 - After Rho step:
B[0][0] = d050ae538c90f6a0 B[0][1] = a08e4457c027a070 B[0][2] = 66e3dd5fcf7b8304 B[0][3] = c084bcf260c26739 B[0][4] = 0bd71c52393417ff 
B[1][0] = 897d6b8cd53d9f5f B[1][1] = 238e2f9eb541c945 B[1][2] = eab5d6e859e92944 B[1][3] = e4adfb530792dd8b B[1][4] = ab2b41d3dc99b1bf 
B[2][0] = 08f07dc44264d46a B[2][1] = 0a7756117a30cf98 B[2][2] = b8018331a824e819 B[2][3] = 9c2a97be9b3174ab B[2][4] = 8792f258c6a35287 
B[3][0] = 1f700b27e9d7dd52 B[3][1] = 505e6e63e130e8b6 B[3][2] = a82660f6d69831d8 B[3][3] = 3a8ed0e0618697ef B[3][4] = ed5542cd5c312f82 
B[4][0] = 8a2f71c49662d4ed B[4][1] = 235dbc800bdfe064 B[4][2] = e2916de3e2571987 B[4][3] = 84e44e2c26b34340 B[4][4] = 5132d2356d456d75 

[DEBUG] Round 6 - After Pi step:
B[0][0] = d050ae538c90f6a0 B[0][1] = 1f700b27e9d7dd52 B[0][2] = 897d6b8cd53d9f5f B[0][3] = 8a2f71c49662d4ed B[0][4] = 08f07dc44264d46a 
B[1][0] = 238e2f9eb541c945 B[1][1] = 235dbc800bdfe064 B[1][2] = 0a7756117a30cf98 B[1][3] = a08e4457c027a070 B[1][4] = 505e6e63e130e8b6 
B[2][0] = b8018331a824e819 B[2][1] = 66e3dd5fcf7b8304 B[2][2] = a82660f6d69831d8 B[2][3] = eab5d6e859e92944 B[2][4] = e2916de3e2571987 
B[3][0] = 3a8ed0e0618697ef B[3][1] = e4adfb530792dd8b B[3][2] = 84e44e2c26b34340 B[3][3] = 9c2a97be9b3174ab B[3][4] = c084bcf260c26739 
B[4][0] = 5132d2356d456d75 B[4][1] = 8792f258c6a35287 B[4][2] = 0bd71c52393417ff B[4][3] = ed5542cd5c312f82 B[4][4] = ab2b41d3dc99b1bf 

[DEBUG] Round 6 - After Xi step:
A[0][0] = 48512e7284b4d6b8 A[0][1] = 5bd24a782df7de52 A[0][2] = 297d4b6a51b5af1f A[0][3] = c01ee36c8faadde9 A[0][4] = aa717c444023c56b 
A[1][0] = 21007f5ef4c3dea3 A[1][1] = a3519e800b5fbcef A[1][2] = 0eb758195a138d98 A[1][3] = b48445414237f4db A[1][4] = 505afe73e1b08e8e 
A[2][0] = f9318124a4658009 A[2][1] = 65f1dd570f5a8100 A[2][2] = a33570a4cf9c2567 A[2][3] = 8be096a91de92244 A[2][4] = c9ba2ce27e4e8901 
A[3][0] = bacefca2e116056f A[3][1] = fccdf2742ec650db A[3][2] = 04cc2da0e2bacb40 A[3][3] = 9e00a6be1973a4c6 A[3][4] = c05480f662a62379 
A[4][0] = 72bcd3b95c046430 A[4][1] = a79f46d8c4ab72a3 A[4][2] = 09d508431334577f A[4][3] = cdd546de1c340f92 A[4][4] = fb2543f07d89992b 

[DEBUG] Round 6 - After last step (RC):
A[0][0] = c8512e7204b45639 A[0][1] = 5bd24a782df7de52 A[0][2] = 297d4b6a51b5af1f A[0][3] = c01ee36c8faadde9 A[0][4] = aa717c444023c56b 
A[1][0] = 21007f5ef4c3dea3 A[1][1] = a3519e800b5fbcef A[1][2] = 0eb758195a138d98 A[1][3] = b48445414237f4db A[1][4] = 505afe73e1b08e8e 
A[2][0] = f9318124a4658009 A[2][1] = 65f1dd570f5a8100 A[2][2] = a33570a4cf9c2567 A[2][3] = 8be096a91de92244 A[2][4] = c9ba2ce27e4e8901 
A[3][0] = bacefca2e116056f A[3][1] = fccdf2742ec650db A[3][2] = 04cc2da0e2bacb40 A[3][3] = 9e00a6be1973a4c6 A[3][4] = c05480f662a62379 
A[4][0] = 72bcd3b95c046430 A[4][1] = a79f46d8c4ab72a3 A[4][2] = 09d508431334577f A[4][3] = cdd546de1c340f92 A[4][4] = fb2543f07d89992b 

[DEBUG] Round 7 - After Theta step:
A[0][0] = f227b394e283aa6e A[0][1] = 61a4d79ecbc02205 A[0][2] = 130bd68cb7825348 A[0][3] = fa687e8a699d21be A[0][4] = 9007e1a2a614393c 
A[1][0] = 0acee22e4db5ff03 A[1][1] = 889f03f0b2299d4f A[1][2] = 2579c569e365ac38 A[1][3] = 9f4ad831fb41d57b A[1][4] = 7b94630358c6af2e 
A[2][0] = a83f89ad0f13271e A[2][1] = 34ffd5dea42c2617 A[2][2] = f23b782d64ea8270 A[2][3] = daee9e20b69f8553 A[2][4] = 98b4246bd5382e16 
A[3][0] = 136c5a27325f24ef A[3][1] = 556f54f1fd8f715b A[3][2] = ad6e8b2531f3eac0 A[3][3] = 37a2003bca3a8546 A[3][4] = 69f62673b1ef02f9 
A[4][0] = cf04b61664450296 A[4][1] = 1a272377fcea1405 A[4][2] = b46d6dec2b7531d9 A[4][3] = 706d237124756934 A[4][4] = 469d265f45c8ff8d 

[DEBUG] Round 7 - After Rho step:
B[0][0] = f227b394e283aa6e B[0][1] = bc0220561a4d79ec B[0][2] = 985eb465bc129a40 B[0][3] = 3a437df4d0fd14d3 B[0][4] = 868a9850e4f2401f 
B[1][0] = 159dc45c9b6bfe06 B[1][1] = 99d4f889f03f0b22 B[1][2] = e715a78d96b0e095 B[1][3] = 3aaf73e95b063f68 B[1][4] = ee518c0d631abcb9 
B[2][0] = aa0fe26b43c4c9c7 B[2][1] = 3ff577a90b0985cd B[2][2] = 54138791dbc16b27 B[2][3] = 4f105b4fc2a9ed77 B[2][4] = d316848d7aa705c2 
B[3][0] = 7325f24ef136c5a2 B[3][1] = adaab7aa78fec7b8 B[3][2] = 4a63e7d5815add16 B[3][3] = 07794750a8c6f440 B[3][4] = f969f62673b1ef02 
B[4][0] = b3222814b67825b0 B[4][1] = 377fcea14051a272 B[4][2] = ba98ecda36b6f615 B[4][3] = 6d23712475693470 B[4][4] = 4997d1723fe351a7 

[DEBUG] Round 7 - After Pi step:
B[0][0] = f227b394e283aa6e B[0][1] = 7325f24ef136c5a2 B[0][2] = 159dc45c9b6bfe06 B[0][3] = b3222814b67825b0 B[0][4] = aa0fe26b43c4c9c7 
B[1][0] = 99d4f889f03f0b22 B[1][1] = 377fcea14051a272 B[1][2] = 3ff577a90b0985cd B[1][3] = bc0220561a4d79ec B[1][4] = adaab7aa78fec7b8 
B[2][0] = 54138791dbc16b27 B[2][1] = 985eb465bc129a40 B[2][2] = 4a63e7d5815add16 B[2][3] = e715a78d96b0e095 B[2][4] = ba98ecda36b6f615 
B[3][0] = 07794750a8c6f440 B[3][1] = 3aaf73e95b063f68 B[3][2] = 6d23712475693470 B[3][3] = 4f105b4fc2a9ed77 B[3][4] = 3a437df4d0fd14d3 
B[4][0] = 4997d1723fe351a7 B[4][1] = d316848d7aa705c2 B[4][2] = 868a9850e4f2401f B[4][3] = f969f62673b1ef02 B[4][4] = ee518c0d631abcb9 

[DEBUG] Round 7 - After Xi step:
A[0][0] = b624b484e943ca6b A[0][1] = fb25c20a4d34dda2 A[0][2] = 559f44081b39a614 A[0][3] = f037af9d32c8a5a1 A[0][4] = b81faa3b45c4f9c2 
A[1][0] = 9abcb8c9d0399f62 A[1][1] = 15de8d290355875a A[1][2] = 1af567897f28a5ad A[1][3] = b40278145a44748e A[1][4] = ade9a68eb8b7c77a 
A[2][0] = 1c9517b3cce06a80 A[2][1] = 594e30619cb39ac2 A[2][2] = c8eb6f8501c89d19 A[2][3] = 577c03ada7a0e295 A[2][4] = 7e886cd315b45e3d 
A[3][0] = b55965d468c65e08 A[3][1] = 1a8e01abda16ff48 A[3][2] = 7c3635286e608a70 A[3][3] = 4d12535f46e1edc7 A[3][4] = 3a4d1f96d0395595 
A[4][0] = 4047997b2fdf50a7 A[4][1] = d74c882c7ae62792 A[4][2] = aceaabf1e4f241d6 A[4][3] = f569f6647bb4b74e A[4][4] = ebf1998d5b20ba81 

[DEBUG] Round 7 - After last step (RC):
A[0][0] = 3624b484e9434a62 A[0][1] = fb25c20a4d34dda2 A[0][2] = 559f44081b39a614 A[0][3] = f037af9d32c8a5a1 A[0][4] = b81faa3b45c4f9c2 
A[1][0] = 9abcb8c9d0399f62 A[1][1] = 15de8d290355875a A[1][2] = 1af567897f28a5ad A[1][3] = b40278145a44748e A[1][4] = ade9a68eb8b7c77a 
A[2][0] = 1c9517b3cce06a80 A[2][1] = 594e30619cb39ac2 A[2][2] = c8eb6f8501c89d19 A[2][3] = 577c03ada7a0e295 A[2][4] = 7e886cd315b45e3d 
A[3][0] = b55965d468c65e08 A[3][1] = 1a8e01abda16ff48 A[3][2] = 7c3635286e608a70 A[3][3] = 4d12535f46e1edc7 A[3][4] = 3a4d1f96d0395595 
A[4][0] = 4047997b2fdf50a7 A[4][1] = d74c882c7ae62792 A[4][2] = aceaabf1e4f241d6 A[4][3] = f569f6647bb4b74e A[4][4] = ebf1998d5b20ba81 

[DEBUG] Round 8 - After Theta step:
A[0][0] = 0ba4782de5726d8d A[0][1] = c6a50ea34105fa4d A[0][2] = 681f88a1170881fb A[0][3] = cdb763343ef9824e A[0][4] = 859f669249f5de2d 
A[1][0] = 0382c1badf645132 A[1][1] = 8ce0f45a0c08490a A[1][2] = 83cb1efa70756bfd A[1][3] = 2d3c01675519bade A[1][4] = 34d7dffdb7ea092a 
A[2][0] = d995a07c16864224 A[2][1] = 9c4e87ae46d5b266 A[2][2] = 0debd84adbaeb5bd A[2][3] = 927cb4627dc6ca31 A[2][4] = bb88db1ccfd27699 
A[3][0] = 5b6ee862a9f7f9a3 A[3][1] = f4b98c1d1b2758e3 A[3][2] = 9201b89eaf512ddb A[3][3] = a325dee987d04a6c A[3][4] = d47a92201108f23e 
A[4][0] = 4595eaa4f53318aa A[4][1] = d29efbf3a00a6f9f A[4][2] = a938d82e3e1e09db A[4][3] = f0bb85bba158ff43 A[4][4] = ee23ea5281ccf28c 

[DEBUG] Round 8 - After Rho step:
B[0][0] = 0ba4782de5726d8d B[0][1] = 105fa4dc6a50ea34 B[0][2] = 40fc4508b8440fdb B[0][3] = f3049d9b6ec6687d B[0][4] = 9a4927d778b6167d 
B[1][0] = 07058375bec8a264 B[1][1] = 8490a8ce0f45a0c0 B[1][2] = 2c7be9c1d5aff60f B[1][3] = 375bc5a7802ceaa3 B[1][4] = d35f7ff6dfa824a8 
B[2][0] = 3665681f05a19089 B[2][1] = 13a1eb91b56c99a7 B[2][2] = 75ade86f5ec256dd B[2][3] = 5a313ee36518c93e B[2][4] = 37711b6399fa4ed3 
B[3][0] = 2a9f7f9a35b6ee86 B[3][1] = 71fa5cc60e8d93ac B[3][2] = 3d5ea25bb7240371 B[3][3] = dd30fa094d9464bb B[3][4] = 3ed47a92201108f2 
B[4][0] = 27a998c5522caf55 B[4][1] = bf3a00a6f9fd29ef B[4][2] = 0f04edd49c6c171f B[4][3] = bb85bba158ff43f0 B[4][4] = fa94a0733ca33b88 

[DEBUG] Round 8 - After Pi step:
B[0][0] = 0ba4782de5726d8d B[0][1] = 2a9f7f9a35b6ee86 B[0][2] = 07058375bec8a264 B[0][3] = 27a998c5522caf55 B[0][4] = 3665681f05a19089 
B[1][0] = 8490a8ce0f45a0c0 B[1][1] = bf3a00a6f9fd29ef B[1][2] = 13a1eb91b56c99a7 B[1][3] = 105fa4dc6a50ea34 B[1][4] = 71fa5cc60e8d93ac 
B[2][0] = 75ade86f5ec256dd B[2][1] = 40fc4508b8440fdb B[2][2] = 3d5ea25bb7240371 B[2][3] = 2c7be9c1d5aff60f B[2][4] = 0f04edd49c6c171f 
B[3][0] = dd30fa094d9464bb B[3][1] = 375bc5a7802ceaa3 B[3][2] = bb85bba158ff43f0 B[3][3] = 5a313ee36518c93e B[3][4] = f3049d9b6ec6687d 
B[4][0] = fa94a0733ca33b88 B[4][1] = 37711b6399fa4ed3 B[4][2] = 9a4927d778b6167d B[4][3] = 3ed47a92201108f2 B[4][4] = d35f7ff6dfa824a8 

[DEBUG] Round 8 - After Xi step:
A[0][0] = 7a89380cb5f03b90 A[0][1] = 6a5b3a9235b6e896 A[0][2] = 2b5b833fbcc8a034 A[0][3] = 0b89d1c4c783bb5e A[0][4] = 3861c90f95c1949a 
A[1][0] = 0c80bace0e5180e2 A[1][1] = 88398001f9d5c9cf A[1][2] = 9120f231fdb7d927 A[1][3] = 425fb2fe4a40e304 A[1][4] = 81fa4ccd6c0ffbcc 
A[2][0] = 5729e81d6ee14ddd A[2][1] = 40dc5f48a1960b8b A[2][2] = 3d16a60d9724177c A[2][3] = 08bfa9d1d5aef6cf A[2][4] = 0f5f8fb00d44139f 
A[3][0] = dc10a2058cc420be A[3][1] = 3fd5a13fa4284aa7 A[3][2] = be813b81deb7e3f0 A[3][3] = 5b18bea637346e3b A[3][4] = d7249d926ec7f87c 
A[4][0] = 7e8420b136a6bbc8 A[4][1] = a2511b4751b34fba A[4][2] = 8ae94f5779920ffe A[4][3] = 2e825e8a084148d2 A[4][4] = 92c56b36d5a4278c 

[DEBUG] Round 8 - After last step (RC):
A[0][0] = 7a89380cb5f03b1a A[0][1] = 6a5b3a9235b6e896 A[0][2] = 2b5b833fbcc8a034 A[0][3] = 0b89d1c4c783bb5e A[0][4] = 3861c90f95c1949a 
A[1][0] = 0c80bace0e5180e2 A[1][1] = 88398001f9d5c9cf A[1][2] = 9120f231fdb7d927 A[1][3] = 425fb2fe4a40e304 A[1][4] = 81fa4ccd6c0ffbcc 
A[2][0] = 5729e81d6ee14ddd A[2][1] = 40dc5f48a1960b8b A[2][2] = 3d16a60d9724177c A[2][3] = 08bfa9d1d5aef6cf A[2][4] = 0f5f8fb00d44139f 
A[3][0] = dc10a2058cc420be A[3][1] = 3fd5a13fa4284aa7 A[3][2] = be813b81deb7e3f0 A[3][3] = 5b18bea637346e3b A[3][4] = d7249d926ec7f87c 
A[4][0] = 7e8420b136a6bbc8 A[4][1] = a2511b4751b34fba A[4][2] = 8ae94f5779920ffe A[4][3] = 2e825e8a084148d2 A[4][4] = 92c56b36d5a4278c 

[DEBUG] Round 9 - After Theta step:
A[0][0] = 3c8a148b2e6bbe4d A[0][1] = 2c581615ae2d6dc1 A[0][2] = 6d58afb827532563 A[0][3] = 4d8afd435c183e09 A[0][4] = 7e62e5880e5a11cd 
A[1][0] = 5ee74dd761eeb46a A[1][1] = da5e7718966afd47 A[1][2] = c34705289208edaf A[1][3] = 103845e725ffd78c A[1][4] = d39dbbd403b0cf44 
A[2][0] = 23e5e9cf1dcdfa42 A[2][1] = 34105e9ad2babc14 A[2][2] = 49daa7dfe408a0e3 A[2][3] = 7c73a803a6824150 A[2][4] = 7b938e627e68a400 
A[3][0] = 25e517078ab8bd61 A[3][1] = c620143da254d778 A[3][2] = 47748e83d8cb7e2f A[3][3] = a2ed0ba43148f3e4 A[3][4] = 2ed1289068bb65a3 
A[4][0] = bf3f09ea44961c9e A[4][1] = 63ea321c2383e8ec A[4][2] = 4b52660c0ba2a8a8 A[4][3] = ef3977d17a71ef84 A[4][4] = 537e426da79480da 

[DEBUG] Round 9 - After Rho step:
B[0][0] = 3c8a148b2e6bbe4d B[0][1] = e2d6dc12c581615a B[0][2] = 6ac57dc13a992b1b B[0][3] = 307c129b15fa86b8 B[0][4] = 962039684735f98b 
B[1][0] = bdce9baec3dd68d4 B[1][1] = afd47da5e7718966 B[1][2] = 1c14a24823b6bf0d B[1][3] = faf1820708bce4bf B[1][4] = 4e76ef500ec33d13 
B[2][0] = 88f97a73c7737e90 B[2][1] = 0417a6b4aeaf050d B[2][2] = 45071a4ed53eff20 B[2][3] = d401d34120a83e39 B[2][4] = 0f7271cc4fcd1480 
B[3][0] = 78ab8bd6125e5170 B[3][1] = bc63100a1ed12a6b B[3][2] = 07b196fc5e8ee91d B[3][3] = 7486291e7c945da1 B[3][4] = a32ed1289068bb65 
B[4][0] = 5224b0e4f5f9f84f B[4][1] = 21c2383e8ec63ea3 B[4][2] = d1545425a9330605 B[4][3] = 3977d17a71ef84ef B[4][4] = 909b69e5203694df 

[DEBUG] Round 9 - After Pi step:
B[0][0] = 3c8a148b2e6bbe4d B[0][1] = 78ab8bd6125e5170 B[0][2] = bdce9baec3dd68d4 B[0][3] = 5224b0e4f5f9f84f B[0][4] = 88f97a73c7737e90 
B[1][0] = afd47da5e7718966 B[1][1] = 21c2383e8ec63ea3 B[1][2] = 0417a6b4aeaf050d B[1][3] = e2d6dc12c581615a B[1][4] = bc63100a1ed12a6b 
B[2][0] = 45071a4ed53eff20 B[2][1] = 6ac57dc13a992b1b B[2][2] = 07b196fc5e8ee91d B[2][3] = 1c14a24823b6bf0d B[2][4] = d1545425a9330605 
B[3][0] = 7486291e7c945da1 B[3][1] = faf1820708bce4bf B[3][2] = 3977d17a71ef84ef B[3][3] = d401d34120a83e39 B[3][4] = 307c129b15fa86b8 
B[4][0] = 909b69e5203694df B[4][1] = 0f7271cc4fcd1480 B[4][2] = 962039684735f98b B[4][3] = a32ed1289068bb65 B[4][4] = 4e76ef500ec33d13 

[DEBUG] Round 9 - After Xi step:
A[0][0] = 7c8916c13e65c84d A[0][1] = 32aece1722475068 A[0][2] = be6e8be693dd80c4 A[0][3] = 4e2492acd7cf664a A[0][4] = c9ed3e5666517a94 
A[1][0] = 9f545cb5cff189e7 A[1][1] = b1f2ba388ee2fa07 A[1][2] = 3c51e7b68fce01ef A[1][3] = 22d78d13c589616a A[1][4] = 9c4b12900a19aad3 
A[2][0] = c51e5aafd51c7f7e A[2][1] = 6fc70c097dd83b1b A[2][2] = 81b1befc589e901d A[2][3] = 3f3aa260b3f63e49 A[2][4] = 9f56b965a3323f06 
A[3][0] = 58863d1472dd77a1 A[3][1] = 8a78081518aea5cf A[3][2] = 10b953fcf12784bb A[3][3] = 8401f38545397e33 A[3][4] = b0f502b8d4cac438 
A[4][0] = 13cf00c1e12695fd A[4][1] = 0e3241e4c34d3a03 A[4][2] = 96311d786b17fc82 A[4][3] = 03fc9d3a9068ba75 A[4][4] = 7a74ef5816433d78 

[DEBUG] Round 9 - After last step (RC):
A[0][0] = 7c8916c13e65c8c5 A[0][1] = 32aece1722475068 A[0][2] = be6e8be693dd80c4 A[0][3] = 4e2492acd7cf664a A[0][4] = c9ed3e5666517a94 
A[1][0] = 9f545cb5cff189e7 A[1][1] = b1f2ba388ee2fa07 A[1][2] = 3c51e7b68fce01ef A[1][3] = 22d78d13c589616a A[1][4] = 9c4b12900a19aad3 
A[2][0] = c51e5aafd51c7f7e A[2][1] = 6fc70c097dd83b1b A[2][2] = 81b1befc589e901d A[2][3] = 3f3aa260b3f63e49 A[2][4] = 9f56b965a3323f06 
A[3][0] = 58863d1472dd77a1 A[3][1] = 8a78081518aea5cf A[3][2] = 10b953fcf12784bb A[3][3] = 8401f38545397e33 A[3][4] = b0f502b8d4cac438 
A[4][0] = 13cf00c1e12695fd A[4][1] = 0e3241e4c34d3a03 A[4][2] = 96311d786b17fc82 A[4][3] = 03fc9d3a9068ba75 A[4][4] = 7a74ef5816433d78 

[DEBUG] Round 10 - After Theta step:
A[0][0] = d61a058ef3a96fd9 A[0][1] = 983ddd58ef8bf774 A[0][2] = 14fd98a95e1127d8 A[0][3] = e4b781e31a03c156 A[0][4] = 637e2d19ab9ddd88 
A[1][0] = fedd45c030ad273f A[1][1] = d07ba34d71be54df A[1][2] = 5dd8fec37092af37 A[1][3] = 435e94663ad5cfb2 A[1][4] = fdc20be5f545040b 
A[2][0] = 8412eb97c11e1f75 A[2][1] = 2ecbbd3169da5b10 A[2][2] = c0bd0fc44c9cf016 A[2][3] = 7e361358a7f45e42 A[2][4] = de5a085db7305f0d 
A[3][0] = 370a92340cec0a75 A[3][1] = e5f4a735669fd81b A[3][2] = 7f35fcdc8f16f96f A[3][3] = eb8d5ca53b0803e7 A[3][4] = df79ad98aafbb9ec 
A[4][0] = 0a7d68959743704d A[4][1] = 178029b0b528dfb3 A[4][2] = 8f83752c1d721932 A[4][3] = 1a4ef56ee60d5fc5 A[4][4] = 63c6870c6026d8c8 

[DEBUG] Round 10 - After Rho step:
B[0][0] = d61a058ef3a96fd9 B[0][1] = f8bf774983ddd58e B[0][2] = a7ecc54af0893ec0 B[0][3] = 0782adc96f03c634 B[0][4] = b466ae7776218df8 
B[1][0] = fdba8b80615a4e7f B[1][1] = e54dfd07ba34d71b B[1][2] = 63fb0dc24abcdd77 B[1][3] = b9f6486bd28cc75a B[1][4] = f7082f97d514102f 
B[2][0] = 6104bae5f04787dd B[2][1] = b2ef4c5a7696c40b B[2][2] = e780b605e87e2264 B[2][3] = 09ac53fa2f213f1b B[2][4] = bbcb410bb6e60be1 
B[3][0] = 40cec0a75370a923 B[3][1] = 0df2fa539ab34fec B[3][2] = b91e2df2defe6bf9 B[3][3] = 94a761007cfd71ab B[3][4] = ecdf79ad98aafbb9 
B[4][0] = acba1b826853eb44 B[4][1] = 9b0b528dfb317802 B[4][2] = b90c9947c1ba960e B[4][3] = 4ef56ee60d5fc51a B[4][4] = a1c31809b63218f1 

[DEBUG] Round 10 - After Pi step:
B[0][0] = d61a058ef3a96fd9 B[0][1] = 40cec0a75370a923 B[0][2] = fdba8b80615a4e7f B[0][3] = acba1b826853eb44 B[0][4] = 6104bae5f04787dd 
B[1][0] = e54dfd07ba34d71b B[1][1] = 9b0b528dfb317802 B[1][2] = b2ef4c5a7696c40b B[1][3] = f8bf774983ddd58e B[1][4] = 0df2fa539ab34fec 
B[2][0] = e780b605e87e2264 B[2][1] = a7ecc54af0893ec0 B[2][2] = b91e2df2defe6bf9 B[2][3] = 63fb0dc24abcdd77 B[2][4] = b90c9947c1ba960e 
B[3][0] = 94a761007cfd71ab B[3][1] = b9f6486bd28cc75a B[3][2] = 4ef56ee60d5fc51a B[3][3] = 09ac53fa2f213f1b B[3][4] = 0782adc96f03c634 
B[4][0] = a1c31809b63218f1 B[4][1] = bbcb410bb6e60be1 B[4][2] = b466ae7776218df8 B[4][3] = ecdf79ad98aafbb9 B[4][4] = f7082f97d514102f 

[DEBUG] Round 10 - After Xi step:
A[0][0] = d49a078eb3e34fbd A[0][1] = 642a45e553f8afe3 A[0][2] = f4aaaa20e932658f A[0][3] = affa13002073e335 A[0][4] = d108bbe1b14f17df 
A[1][0] = f56abc07aeb58690 A[1][1] = 83195aacf935b918 A[1][2] = f40e0e5e77974009 A[1][3] = f0bb2571a6dcf786 A[1][4] = 0b70dedbb4b20fdc 
A[2][0] = c6c0ae0c6a7c2a34 A[2][1] = a5e5c44ad4eb3661 A[2][2] = 091cade3acde6319 A[2][3] = 87a825c7da361dd7 A[2][4] = 49049b5151ae8605 
A[3][0] = c2bf64863d7416a3 A[3][1] = f9f2c8cf939c6758 A[3][2] = 076d6f660c05871d A[3][3] = 098c51f84f703f5f A[3][4] = 07863da94f4041e4 
A[4][0] = 8086e008be2688f3 A[4][1] = 20ca53031ee75be1 A[4][2] = b623ea2d60a50df8 A[4][3] = bcda1de41b26ef33 A[4][4] = fbfa6f85dfa4580f 

[DEBUG] Round 10 - After last step (RC):
A[0][0] = d49a078e33e3cfb4 A[0][1] = 642a45e553f8afe3 A[0][2] = f4aaaa20e932658f A[0][3] = affa13002073e335 A[0][4] = d108bbe1b14f17df 
A[1][0] = f56abc07aeb58690 A[1][1] = 83195aacf935b918 A[1][2] = f40e0e5e77974009 A[1][3] = f0bb2571a6dcf786 A[1][4] = 0b70dedbb4b20fdc 
A[2][0] = c6c0ae0c6a7c2a34 A[2][1] = a5e5c44ad4eb3661 A[2][2] = 091cade3acde6319 A[2][3] = 87a825c7da361dd7 A[2][4] = 49049b5151ae8605 
A[3][0] = c2bf64863d7416a3 A[3][1] = f9f2c8cf939c6758 A[3][2] = 076d6f660c05871d A[3][3] = 098c51f84f703f5f A[3][4] = 07863da94f4041e4 
A[4][0] = 8086e008be2688f3 A[4][1] = 20ca53031ee75be1 A[4][2] = b623ea2d60a50df8 A[4][3] = bcda1de41b26ef33 A[4][4] = fbfa6f85dfa4580f 

[DEBUG] Round 11 - After Theta step:
A[0][0] = 76b90a7753f6a9d4 A[0][1] = c609481c33edc983 A[0][2] = 5689a7d9892703ef A[0][3] = 0dd91ef940668555 A[0][4] = 732bb618d15a71bf 
A[1][0] = 86a80eca8503be9f A[1][1] = f0dbe861d2838117 A[1][2] = 87ccbc935c217806 A[1][3] = 837997bc8d6acf89 A[1][4] = 78b26c169f0437d3 
A[2][0] = db23e3ae1dbebd55 A[2][1] = b80689e8a329a100 A[2][2] = 14ffe041db1cf478 A[2][3] = 9a4b6865adf48ab6 A[2][4] = 54e7d6f3266c1164 
A[3][0] = c4b44b3bad692191 A[3][1] = fff9e7720381506a A[3][2] = 016640db9c18b02f A[3][3] = 0f877e45df6d086d A[3][4] = 018d1214df5d76d6 
A[4][0] = c77cce222cd0e2ca A[4][1] = 67307d298c1131d8 A[4][2] = f1d9c407f25367c1 A[4][3] = fb2033ce89d0850a A[4][4] = bc0041af4d523236 

[DEBUG] Round 11 - After Rho step:
B[0][0] = 76b90a7753f6a9d4 B[0][1] = 3edc983c609481c3 B[0][2] = b44d3ecc49381f7a B[0][3] = cd0aaa1bb23df280 B[0][4] = d8634569c6fdccae 
B[1][0] = 0d501d950a077d3f B[1][1] = 38117f0dbe861d28 B[1][2] = 32f24d7085e01a1f B[1][3] = 59f1306f32f791ad B[1][4] = e2c9b05a7c10df4d 
B[2][0] = 76c8f8eb876faf55 B[2][1] = 01a27a28ca68402e B[2][2] = e7a3c0a7ff020ed8 B[2][3] = b432d6fa455b4d25 B[2][4] = 8a9cfade64cd822c 
B[3][0] = bad692191c4b44b3 B[3][1] = 357ffcf3b901c0a8 B[3][2] = b73831605e02cc81 B[3][3] = c8bbeda10da1f0ef B[3][4] = d6018d1214df5d76 
B[4][0] = 11668716563be671 B[4][1] = d298c1131d867307 B[4][2] = 29b3e0f8ece203f9 B[4][3] = 2033ce89d0850afb B[4][4] = 106bd3548c8daf00 

[DEBUG] Round 11 - After Pi step:
B[0][0] = 76b90a7753f6a9d4 B[0][1] = bad692191c4b44b3 B[0][2] = 0d501d950a077d3f B[0][3] = 11668716563be671 B[0][4] = 76c8f8eb876faf55 
B[1][0] = 38117f0dbe861d28 B[1][1] = d298c1131d867307 B[1][2] = 01a27a28ca68402e B[1][3] = 3edc983c609481c3 B[1][4] = 357ffcf3b901c0a8 
B[2][0] = e7a3c0a7ff020ed8 B[2][1] = b44d3ecc49381f7a B[2][2] = b73831605e02cc81 B[2][3] = 32f24d7085e01a1f B[2][4] = 29b3e0f8ece203f9 
B[3][0] = c8bbeda10da1f0ef B[3][1] = 59f1306f32f791ad B[3][2] = 2033ce89d0850afb B[3][3] = b432d6fa455b4d25 B[3][4] = cd0aaa1bb23df280 
B[4][0] = 106bd3548c8daf00 B[4][1] = 8a9cfade64cd822c B[4][2] = d8634569c6fdccae B[4][3] = d6018d1214df5d76 B[4][4] = e2c9b05a7c10df4d 

[DEBUG] Round 11 - After Xi step:
A[0][0] = b11b8ad512f6ab04 A[0][1] = 9e93acd55c7348cb A[0][2] = bb481cd51e05f1be A[0][3] = 1144c256d35bfc6d A[0][4] = 7e48f8e3c38dac04 
A[1][0] = 3009520dbe27ed0f A[1][1] = 9b28c1302f41f382 A[1][2] = 01a1b4a14aed4254 A[1][3] = badc0ab6208fc4e3 A[1][4] = f177f6f0ab1c30a8 
A[2][0] = f7e3d2f37f0e01d8 A[2][1] = 3641f45c0d301d7a A[2][2] = 6f783000587a0885 A[2][3] = 70f3447095640a4d A[2][4] = 0b72f0b8a0e20eb4 
A[3][0] = ae2be5825ed3f03b A[3][1] = 69b3306e2af5d53e A[3][2] = 2523d61dd8873bea A[3][3] = b554d4fe077bef24 A[3][4] = d90ae2ba3152d290 
A[4][0] = 186ba65c208dbb28 A[4][1] = ca94bbdc6549b128 A[4][2] = d8c127410695ccae A[4][3] = f899953a345b5cf4 A[4][4] = e3feb44a44109fe5 

[DEBUG] Round 11 - After last step (RC):
A[0][0] = b11b8ad592f6ab0e A[0][1] = 9e93acd55c7348cb A[0][2] = bb481cd51e05f1be A[0][3] = 1144c256d35bfc6d A[0][4] = 7e48f8e3c38dac04 
A[1][0] = 3009520dbe27ed0f A[1][1] = 9b28c1302f41f382 A[1][2] = 01a1b4a14aed4254 A[1][3] = badc0ab6208fc4e3 A[1][4] = f177f6f0ab1c30a8 
A[2][0] = f7e3d2f37f0e01d8 A[2][1] = 3641f45c0d301d7a A[2][2] = 6f783000587a0885 A[2][3] = 70f3447095640a4d A[2][4] = 0b72f0b8a0e20eb4 
A[3][0] = ae2be5825ed3f03b A[3][1] = 69b3306e2af5d53e A[3][2] = 2523d61dd8873bea A[3][3] = b554d4fe077bef24 A[3][4] = d90ae2ba3152d290 
A[4][0] = 186ba65c208dbb28 A[4][1] = ca94bbdc6549b128 A[4][2] = d8c127410695ccae A[4][3] = f899953a345b5cf4 A[4][4] = e3feb44a44109fe5 

[DEBUG] Round 12 - After Theta step:
A[0][0] = 621526d001ddff94 A[0][1] = 4d9d00d0cf581c51 A[0][2] = 6846b0d08d2ea524 A[0][3] = c24a6e534070a8f7 A[0][4] = ad4654e650a6f89e 
A[1][0] = 617216a341f58ea0 A[1][1] = ca53859ed093902d A[1][2] = 50daf00fb53f21fb A[1][3] = eba74e18df5da74c A[1][4] = a00cb25e54ce5307 
A[2][0] = 0b0262421a06effd A[2][1] = caa044ed6838f35f A[2][2] = 939980b13d72e6a0 A[2][3] = 8c12f4c1f06ce468 A[2][4] = f7934009c5eae091 
A[3][0] = 59c270872725eb9b A[3][1] = 9e5aa56b5303ce9e A[3][2] = d2ca4318a171204a A[3][3] = 42bd41fb7e8df484 A[3][4] = 2ee377bf48a4c930 
A[4][0] = 611693283aa91c56 A[4][1] = b3e98ea87f6d1656 A[4][2] = a1bc12351cb16bd0 A[4][3] = 81e4a04e2e7ffb8a A[4][4] = 9a83813e5e34389b 

[DEBUG] Round 12 - After Rho step:
B[0][0] = 621526d001ddff94 B[0][1] = f581c514d9d00d0c B[0][2] = 4235868469752923 B[0][3] = e151ef8494dca680 B[0][4] = 5399429be27ab519 
B[1][0] = c2e42d4683eb1d40 B[1][1] = 3902dca53859ed09 B[1][2] = 6bc03ed4fc87ed43 B[1][3] = b4e99d74e9c31beb B[1][4] = 8032c97953394c1e 
B[2][0] = 42c098908681bbff B[2][1] = a8113b5a0e3cd7f2 B[2][2] = 9735049ccc0589eb B[2][3] = 7a60f83672344609 B[2][4] = 3ef2680138bd5c12 
B[3][0] = 72725eb9b59c2708 B[3][1] = 4f4f2d52b5a981e7 B[3][2] = 3142e24095a59486 B[3][3] = 3f6fd1be908857a8 B[3][4] = 302ee377bf48a4c9 
B[4][0] = 41d548e2b308b499 B[4][1] = ea87f6d1656b3e98 B[4][2] = 58b5e850de091a8e B[4][3] = e4a04e2e7ffb8a81 B[4][4] = e04f978d0e26e6a0 

[DEBUG] Round 12 - After Pi step:
B[0][0] = 621526d001ddff94 B[0][1] = 72725eb9b59c2708 B[0][2] = c2e42d4683eb1d40 B[0][3] = 41d548e2b308b499 B[0][4] = 42c098908681bbff 
B[1][0] = 3902dca53859ed09 B[1][1] = ea87f6d1656b3e98 B[1][2] = a8113b5a0e3cd7f2 B[1][3] = f581c514d9d00d0c B[1][4] = 4f4f2d52b5a981e7 
B[2][0] = 9735049ccc0589eb B[2][1] = 4235868469752923 B[2][2] = 3142e24095a59486 B[2][3] = 6bc03ed4fc87ed43 B[2][4] = 58b5e850de091a8e 
B[3][0] = 3f6fd1be908857a8 B[3][1] = b4e99d74e9c31beb B[3][2] = e4a04e2e7ffb8a81 B[3][3] = 7a60f83672344609 B[3][4] = e151ef8494dca680 
B[4][0] = e04f978d0e26e6a0 B[4][1] = 3ef2680138bd5c12 B[4][2] = 5399429be27ab519 B[4][3] = 302ee377bf48a4c9 B[4][4] = 8032c97953394c1e 

[DEBUG] Round 12 - After Xi step:
A[0][0] = e42026c8c5d9ff76 A[0][1] = 72425ebdbd88262b A[0][2] = d3a6ed46126a1d44 A[0][3] = 4b957222970f54da A[0][4] = 52705890cc81a1f7 
A[1][0] = 11480d8728d1bb09 A[1][1] = 5e4fefa1e5e92c50 A[1][2] = 6cb137746466ddf3 A[1][3] = e5a10536dbe00f04 A[1][4] = ee0f2ad6b57d25e7 
A[2][0] = 5735029dc22329eb A[2][1] = 4827e68579496d33 A[2][2] = 225be2d115a5a19e A[2][3] = 6bce3d9571cf4d83 A[2][4] = 5897e8299d285290 
A[3][0] = 3d7ff1ee91514ebc A[3][1] = f4e98bcc6cc338e3 A[3][2] = 64c4636a7e7a82c1 A[3][3] = 3bb1f0b672345619 A[3][4] = a391ff04105c1561 
A[4][0] = f94d4fa83626e6a9 A[4][1] = b677c84178de4482 A[4][2] = 7b885083ee6e77ab A[4][3] = 842e6663f798adcd A[4][4] = 8d3dec3b62114c1e 

[DEBUG] Round 12 - After last step (RC):
A[0][0] = e42026c845d97ffd A[0][1] = 72425ebdbd88262b A[0][2] = d3a6ed46126a1d44 A[0][3] = 4b957222970f54da A[0][4] = 52705890cc81a1f7 
A[1][0] = 11480d8728d1bb09 A[1][1] = 5e4fefa1e5e92c50 A[1][2] = 6cb137746466ddf3 A[1][3] = e5a10536dbe00f04 A[1][4] = ee0f2ad6b57d25e7 
A[2][0] = 5735029dc22329eb A[2][1] = 4827e68579496d33 A[2][2] = 225be2d115a5a19e A[2][3] = 6bce3d9571cf4d83 A[2][4] = 5897e8299d285290 
A[3][0] = 3d7ff1ee91514ebc A[3][1] = f4e98bcc6cc338e3 A[3][2] = 64c4636a7e7a82c1 A[3][3] = 3bb1f0b672345619 A[3][4] = a391ff04105c1561 
A[4][0] = f94d4fa83626e6a9 A[4][1] = b677c84178de4482 A[4][2] = 7b885083ee6e77ab A[4][3] = 842e6663f798adcd A[4][4] = 8d3dec3b62114c1e 

[DEBUG] Round 13 - After Theta step:
A[0][0] = 89b08e9fff408b3c A[0][1] = 1fd2f6ea0711d2ea A[0][2] = be364511a8f3e985 A[0][3] = 2605da752d96a01b A[0][4] = 3fe0f0c776185536 
A[1][0] = 514814ec1d35fe1c A[1][1] = 1e4ff6cad00d6945 A[1][2] = 2cb12e1f518298e6 A[1][3] = a5a11c5dee044a11 A[1][4] = ae0f33bd809960f2 
A[2][0] = 15c9d5dac6e1266e A[2][1] = 0adb31c27d8b62b6 A[2][2] = 60a735961167ae1b A[2][3] = 2932ead2750d4206 A[2][4] = 1a6b3f6e99ea5d15 
A[3][0] = 482d98ffb947dc4f A[3][1] = 81bbe2dd44d5aa10 A[3][2] = 11960a7b566c1032 A[3][3] = 4ee399a75a22c4ea A[3][4] = d6c39615384a8792 
A[4][0] = 747c2651b4cd3231 A[4][1] = 3b46a1b8fa35901a A[4][2] = f6b9397a6c85a333 A[4][3] = 091f0f9a75737955 A[4][4] = 000c85c2e0fa9886 

[DEBUG] Round 13 - After Rho step:
B[0][0] = 89b08e9fff408b3c B[0][1] = 711d2ea1fd2f6ea0 B[0][2] = f1b2288d479f4c2d B[0][3] = 2d40364c0bb4ea5b B[0][4] = c31dd86154d8ff83 
B[1][0] = a29029d83a6bfc38 B[1][1] = d69451e4ff6cad00 B[1][2] = c4b87d460a6398b2 B[1][3] = 894234b4238bbdc0 B[1][4] = b83ccef6026583ca 
B[2][0] = 85727576b1b8499b B[2][1] = b6cc709f62d8ad82 B[2][2] = 3d70db0539acb08b B[2][3] = 75693a86a1031499 B[2][4] = a34d67edd33d4ba2 
B[3][0] = fb947dc4f482d98f B[3][1] = 0840ddf16ea26ad5 B[3][2] = f6acd82064232c14 B[3][3] = 34eb44589d49dc73 B[3][4] = 92d6c39615384a87 
B[4][0] = 8da669918ba3e132 B[4][1] = 1b8fa35901a3b46a B[4][2] = 42d199fb5c9cbd36 B[4][3] = 1f0f9a7573795509 B[4][4] = 2170b83ea6218003 

[DEBUG] Round 13 - After Pi step:
B[0][0] = 89b08e9fff408b3c B[0][1] = fb947dc4f482d98f B[0][2] = a29029d83a6bfc38 B[0][3] = 8da669918ba3e132 B[0][4] = 85727576b1b8499b 
B[1][0] = d69451e4ff6cad00 B[1][1] = 1b8fa35901a3b46a B[1][2] = b6cc709f62d8ad82 B[1][3] = 711d2ea1fd2f6ea0 B[1][4] = 0840ddf16ea26ad5 
B[2][0] = 3d70db0539acb08b B[2][1] = f1b2288d479f4c2d B[2][2] = f6acd82064232c14 B[2][3] = c4b87d460a6398b2 B[2][4] = 42d199fb5c9cbd36 
B[3][0] = 34eb44589d49dc73 B[3][1] = 894234b4238bbdc0 B[3][2] = 1f0f9a7573795509 B[3][3] = 75693a86a1031499 B[3][4] = 2d40364c0bb4ea5b 
B[4][0] = 2170b83ea6218003 B[4][1] = a34d67edd33d4ba2 B[4][2] = c31dd86154d8ff83 B[4][3] = 92d6c39615384a87 B[4][4] = b83ccef6026583ca 

[DEBUG] Round 13 - After Xi step:
A[0][0] = a0d0049effc09bb7 A[0][1] = 1ba47540b29e918a A[0][2] = e2b0a1f83e48fc2c A[0][3] = 090638d789e37120 A[0][4] = c7e3757ca1a4dcb9 
A[1][0] = d61f55bc7b2de170 A[1][1] = 13cfb76921a305aa A[1][2] = bfcf72ca7180fc8b A[1][3] = 405c2c215c2f6aa9 A[1][4] = 2540fbf56d82289c 
A[2][0] = 3c6063231b8cb08b A[2][1] = d3bf6bc497ab0e0f A[2][2] = 36bc982060a38696 A[2][3] = 462ebc561e5bd2b4 A[2][4] = d2ed51495cddbcb6 
A[3][0] = bc6b42d9c409d74f A[3][1] = d1d22cb407092dcd A[3][2] = 3f8fbbed595a5531 A[3][3] = 784912872b80b5a9 A[3][4] = 2802074cba2ca24a 
A[4][0] = 7774e95ea60da403 A[4][1] = a346e5f4d21c6fc2 A[4][2] = d75188661448fe01 A[4][3] = e2cfc5b661344407 A[4][4] = b03c46774c67a18e 

[DEBUG] Round 13 - After last step (RC):
A[0][0] = 20d0049effc09b3c A[0][1] = 1ba47540b29e918a A[0][2] = e2b0a1f83e48fc2c A[0][3] = 090638d789e37120 A[0][4] = c7e3757ca1a4dcb9 
A[1][0] = d61f55bc7b2de170 A[1][1] = 13cfb76921a305aa A[1][2] = bfcf72ca7180fc8b A[1][3] = 405c2c215c2f6aa9 A[1][4] = 2540fbf56d82289c 
A[2][0] = 3c6063231b8cb08b A[2][1] = d3bf6bc497ab0e0f A[2][2] = 36bc982060a38696 A[2][3] = 462ebc561e5bd2b4 A[2][4] = d2ed51495cddbcb6 
A[3][0] = bc6b42d9c409d74f A[3][1] = d1d22cb407092dcd A[3][2] = 3f8fbbed595a5531 A[3][3] = 784912872b80b5a9 A[3][4] = 2802074cba2ca24a 
A[4][0] = 7774e95ea60da403 A[4][1] = a346e5f4d21c6fc2 A[4][2] = d75188661448fe01 A[4][3] = e2cfc5b661344407 A[4][4] = b03c46774c67a18e 

[DEBUG] Round 14 - After Theta step:
A[0][0] = 4f468c05878cffbd A[0][1] = 7432fddbcad2f50b A[0][2] = 8d262963460498ad A[0][3] = 6690b04cf1af15a1 A[0][4] = a875fde7d9e8b838 
A[1][0] = 5a7e33807c781653 A[1][1] = 9faed15526f6f289 A[1][2] = 33ae14f676d50ba8 A[1][3] = cc3d4a1d5b7a9d8a A[1][4] = a9219dc96ad7dfbf 
A[2][0] = 2798a47e16c29a4f A[2][1] = c847ac999ae524cb A[2][2] = 2d445f7d6dedac52 A[2][3] = 5dd67b0b1315f870 A[2][4] = c915961451939672 
A[3][0] = 52eb311bf01e21cd A[3][1] = 3f525f76331edb4f A[3][2] = d10fc82f6d4da3b3 A[3][3] = 96c961451f97432b A[3][4] = c682748e8e3b54c8 
A[4][0] = 5b4a120f1b59aa55 A[4][1] = 8f781ea56f486194 A[4][2] = fb6f7337a91cf057 A[4][3] = cef13ee7dc604a51 A[4][4] = 9c02bd26f133afd8 

[DEBUG] Round 14 - After Rho step:
B[0][0] = 4f468c05878cffbd B[0][1] = ad2f50b7432fddbc B[0][2] = 69314b1a3024c56c B[0][3] = 5e2b42cd216099e3 B[0][4] = f79f67a2e0e2a1d7 
B[1][0] = b4fc6700f8f02ca6 B[1][1] = 6f2899faed15526f B[1][2] = b853d9db542ea0ce B[1][3] = 53b15987a943ab6f B[1][4] = a4867725ab5f7efe 
B[2][0] = c9e6291f85b0a693 B[2][1] = 11eb2666b94932f2 B[2][2] = 6d62916a22fbeb6f B[2][3] = 3d85898afc382eeb B[2][4] = 5922b2c28a3272ce 
B[3][0] = bf01e21cd52eb311 B[3][1] = a79fa92fbb198f6d B[3][2] = 5eda9b4767a21f90 B[3][3] = 28a3f2e86572d92c B[3][4] = c8c682748e8e3b54 
B[4][0] = 78dacd52aada5090 B[4][1] = ea56f4861948f781 B[4][2] = 8e782bfdb7b99bd4 B[4][3] = f13ee7dc604a51ce B[4][4] = af49bc4cebf62700 

[DEBUG] Round 14 - After Pi step:
B[0][0] = 4f468c05878cffbd B[0][1] = bf01e21cd52eb311 B[0][2] = b4fc6700f8f02ca6 B[0][3] = 78dacd52aada5090 B[0][4] = c9e6291f85b0a693 
B[1][0] = 6f2899faed15526f B[1][1] = ea56f4861948f781 B[1][2] = 11eb2666b94932f2 B[1][3] = ad2f50b7432fddbc B[1][4] = a79fa92fbb198f6d 
B[2][0] = 6d62916a22fbeb6f B[2][1] = 69314b1a3024c56c B[2][2] = 5eda9b4767a21f90 B[2][3] = b853d9db542ea0ce B[2][4] = 8e782bfdb7b99bd4 
B[3][0] = 28a3f2e86572d92c B[3][1] = 53b15987a943ab6f B[3][2] = f13ee7dc604a51ce B[3][3] = 3d85898afc382eeb B[3][4] = 5e2b42cd216099e3 
B[4][0] = af49bc4cebf62700 B[4][1] = 5922b2c28a3272ce B[4][2] = f79f67a2e0e2a1d7 B[4][3] = c8c682748e8e3b54 B[4][4] = a4867725ab5f7efe 

[DEBUG] Round 14 - After Xi step:
A[0][0] = 4f048c05856656bd A[0][1] = be20e904f50ab37d A[0][2] = faecfe01be5221a6 A[0][3] = 688a441abeda70d2 A[0][4] = c1862bcf8110b603 
A[1][0] = 6fa9fb7aa815426f A[1][1] = f8d6e403900bdd82 A[1][2] = b0cf42feb90172bc A[1][3] = a8ab50b7eb3fd39d A[1][4] = f79ce92fbb598f4e 
A[2][0] = ea2a9d6ea87fcd6f A[2][1] = 6133e95a321495ec A[2][2] = 585b9b65e702bf81 A[2][3] = 7811dbaf56a8b1da A[2][4] = 2efc1edd3da6fdc8 
A[3][0] = 68a5f2e9617a0191 A[3][1] = f5b0199bfc4f2a7e A[3][2] = f15ee7dc785a5dee A[3][3] = 0d9dc488dc686e6b A[3][4] = 174b4ad725c019e2 
A[4][0] = 8f61adb683e72742 A[4][1] = 1974a6408272364e A[4][2] = f69c67c4e1ebb387 A[4][3] = 4de392d1cfabb678 A[4][4] = 829ff70591567792 

[DEBUG] Round 14 - After last step (RC):
A[0][0] = cf048c058566d634 A[0][1] = be20e904f50ab37d A[0][2] = faecfe01be5221a6 A[0][3] = 688a441abeda70d2 A[0][4] = c1862bcf8110b603 
A[1][0] = 6fa9fb7aa815426f A[1][1] = f8d6e403900bdd82 A[1][2] = b0cf42feb90172bc A[1][3] = a8ab50b7eb3fd39d A[1][4] = f79ce92fbb598f4e 
A[2][0] = ea2a9d6ea87fcd6f A[2][1] = 6133e95a321495ec A[2][2] = 585b9b65e702bf81 A[2][3] = 7811dbaf56a8b1da A[2][4] = 2efc1edd3da6fdc8 
A[3][0] = 68a5f2e9617a0191 A[3][1] = f5b0199bfc4f2a7e A[3][2] = f15ee7dc785a5dee A[3][3] = 0d9dc488dc686e6b A[3][4] = 174b4ad725c019e2 
A[4][0] = 8f61adb683e72742 A[4][1] = 1974a6408272364e A[4][2] = f69c67c4e1ebb387 A[4][3] = 4de392d1cfabb678 A[4][4] = 829ff70591567792 

[DEBUG] Round 15 - After Theta step:
A[0][0] = 91fe4ddc9916d651 A[0][1] = e0da28dde97ab318 A[0][2] = a4163fd8a22221c3 A[0][3] = 367085c3a2aa70b7 A[0][4] = 9f7cea169d60b666 
A[1][0] = 46335be9752e9670 A[1][1] = d14c44904d30099d A[1][2] = 9955e26d643aa6a3 A[1][3] = 8131f02436040782 A[1][4] = de0649bc66625b51 
A[2][0] = 7f967c9340887ffd A[2][1] = f48f08a7dae3277e A[2][2] = cde77a980ff50d13 A[2][3] = edad3a52be5f0348 A[2][4] = bb40ff20d5514f5a 
A[3][0] = b2e0cb070a1b6c42 A[3][1] = 2ff52075972e47ad A[3][2] = 2b1bde32133b303d A[3][3] = d7d8fd66b70903b8 A[3][4] = cd0e73394ea17431 
A[4][0] = bc75c6ec7cc922b6 A[4][1] = 2a60cd1a7d5c33ba A[4][2] = c5880c9e1ec5b673 A[4][3] = 7ef7f98b3085b38c A[4][4] = b18b9c5f6e787266 

[DEBUG] Round 15 - After Rho step:
B[0][0] = 91fe4ddc9916d651 B[0][1] = 97ab318e0da28dde B[0][2] = 20b1fec511110e1d B[0][3] = 54e16e6ce10b8745 B[0][4] = a85a7582d99a7df3 
B[1][0] = 8c66b7d2ea5d2ce0 B[1][1] = 0099dd14c44904d3 B[1][2] = 5789b590ea9a8e65 B[1][3] = 80f050263e0486c0 B[1][4] = 781926f199896d47 
B[2][0] = 5fe59f24d0221fff B[2][1] = 23c229f6b8c9dfbd B[2][2] = a8689e6f3bd4c07f B[2][3] = 9d295f2f81a476d6 B[2][4] = 57681fe41aaa29eb 
B[3][0] = 70a1b6c42b2e0cb0 B[3][1] = d697fa903acb9723 B[3][2] = 642676607a5637bc B[3][3] = acd6e120771afb1f B[3][4] = 31cd0e73394ea174 
B[4][0] = 63e64915b5e3ae37 B[4][1] = d1a7d5c33ba2a60c B[4][2] = 62db39e2c4064f0f B[4][3] = f7f98b3085b38c7e B[4][4] = e717db9e1c99ac62 

[DEBUG] Round 15 - After Pi step:
B[0][0] = 91fe4ddc9916d651 B[0][1] = 70a1b6c42b2e0cb0 B[0][2] = 8c66b7d2ea5d2ce0 B[0][3] = 63e64915b5e3ae37 B[0][4] = 5fe59f24d0221fff 
B[1][0] = 0099dd14c44904d3 B[1][1] = d1a7d5c33ba2a60c B[1][2] = 23c229f6b8c9dfbd B[1][3] = 97ab318e0da28dde B[1][4] = d697fa903acb9723 
B[2][0] = a8689e6f3bd4c07f B[2][1] = 20b1fec511110e1d B[2][2] = 642676607a5637bc B[2][3] = 5789b590ea9a8e65 B[2][4] = 62db39e2c4064f0f 
B[3][0] = acd6e120771afb1f B[3][1] = 80f050263e0486c0 B[3][2] = f7f98b3085b38c7e B[3][3] = 9d295f2f81a476d6 B[3][4] = 54e16e6ce10b8745 
B[4][0] = e717db9e1c99ac62 B[4][1] = 57681fe41aaa29eb B[4][2] = a85a7582d99a7df3 B[4][3] = 31cd0e73394ea174 B[4][4] = 781926f199896d47 

[DEBUG] Round 15 - After Xi step:
A[0][0] = 399e4fb7a282167d A[0][1] = 50b19cc02b3f04a1 A[0][2] = c842e1d2a84b0ce0 A[0][3] = 23e6cd0557fbac16 A[0][4] = 7fad9e46142657f3 
A[1][0] = 040fbc1480433fd3 A[1][1] = 51e7d5e115a626cc A[1][2] = b01ba0e63d6857ff A[1][3] = 1f8b7ba10c86fd4c A[1][4] = c2b7bc9c1bc21763 
A[2][0] = eb6984f13355c41f A[2][1] = 77b9f10511bb2736 A[2][2] = 6c2402e2225e463d A[2][3] = 774db5c0d2d00f45 A[2][4] = 4ac33973dc86270d 
A[3][0] = bc3ee560f61ca90e A[3][1] = a071f0261f0082d0 A[3][2] = f3dd0960a7f68c7e A[3][3] = df0b1e2b050578d5 A[3][4] = 5305f768a12995fd 
A[4][0] = e7164b9e58d0ace0 A[4][1] = d66e5ee70a2a8be7 A[4][2] = 8bda7da6c91aaeee A[4][3] = a5c43ef9314ea0bc A[4][4] = f80b4661b340ed47 

[DEBUG] Round 15 - After last step (RC):
A[0][0] = b99e4fb7a282967e A[0][1] = 50b19cc02b3f04a1 A[0][2] = c842e1d2a84b0ce0 A[0][3] = 23e6cd0557fbac16 A[0][4] = 7fad9e46142657f3 
A[1][0] = 040fbc1480433fd3 A[1][1] = 51e7d5e115a626cc A[1][2] = b01ba0e63d6857ff A[1][3] = 1f8b7ba10c86fd4c A[1][4] = c2b7bc9c1bc21763 
A[2][0] = eb6984f13355c41f A[2][1] = 77b9f10511bb2736 A[2][2] = 6c2402e2225e463d A[2][3] = 774db5c0d2d00f45 A[2][4] = 4ac33973dc86270d 
A[3][0] = bc3ee560f61ca90e A[3][1] = a071f0261f0082d0 A[3][2] = f3dd0960a7f68c7e A[3][3] = df0b1e2b050578d5 A[3][4] = 5305f768a12995fd 
A[4][0] = e7164b9e58d0ace0 A[4][1] = d66e5ee70a2a8be7 A[4][2] = 8bda7da6c91aaeee A[4][3] = a5c43ef9314ea0bc A[4][4] = f80b4661b340ed47 

[DEBUG] Round 16 - After Theta step:
A[0][0] = 2f6d43adc4ff1bf2 A[0][1] = c64290da4d42892d A[0][2] = 5eb1edc8ce36816c A[0][3] = b515c11f3186219a A[0][4] = e95e925c725bda7f 
A[1][0] = e3dc2ab8ffa540b0 A[1][1] = b634434d6a4059af A[1][2] = 57c8364a428e289c A[1][3] = f858ed0d7360822f A[1][4] = 25642a3064246800 
A[2][0] = 149f60145910f5c0 A[2][1] = 884f15e07bfe16e9 A[2][2] = 93d2e607481b77e2 A[2][3] = 88bb5125b8953e9a A[2][4] = b535dd96b6c316d2 
A[3][0] = bf9e3e4bcb27ac77 A[3][1] = a3d12b0d223b87a9 A[3][2] = f07dd24b9acd8907 A[3][3] = dcabc500383e7dac A[3][4] = 50a52c439c129084 
A[4][0] = 7ec67d3776402ddc A[4][1] = 4fbe684e24ba0adb A[4][2] = 120a4b0fe78a2fd2 A[4][3] = 3c1408501fde2180 A[4][4] = 61db70c89dd06c7b 

[DEBUG] Round 16 - After Rho step:
B[0][0] = 2f6d43adc4ff1bf2 B[0][1] = d42892dc64290da4 B[0][2] = f58f6e4671b40b62 B[0][3] = 0c43356a2b823e63 B[0][4] = 4971c96f69ffa57a 
B[1][0] = c7b85571ff4a8161 B[1][1] = 059afb634434d6a4 B[1][2] = 20d9290a38a2715f B[1][3] = 1045ff0b1da1ae6c B[1][4] = 9590a8c19091a000 
B[2][0] = 0527d80516443d70 B[2][1] = 13c5781eff85ba62 B[2][2] = dbbf149e97303a40 B[2][3] = a892dc4a9f4d445d B[2][4] = 56a6bbb2d6d862da 
B[3][0] = bcb27ac77bf9e3e4 B[3][1] = d4d1e89586911dc3 B[3][2] = 97359b120fe0fba4 B[3][3] = a00707cfb59b9578 B[3][4] = 8450a52c439c1290 
B[4][0] = bbb2016ee3f633e9 B[4][1] = 84e24ba0adb4fbe6 B[4][2] = c517e909052587f3 B[4][3] = 1408501fde21803c B[4][4] = dc3227741b1ed876 

[DEBUG] Round 16 - After Pi step:
B[0][0] = 2f6d43adc4ff1bf2 B[0][1] = bcb27ac77bf9e3e4 B[0][2] = c7b85571ff4a8161 B[0][3] = bbb2016ee3f633e9 B[0][4] = 0527d80516443d70 
B[1][0] = 059afb634434d6a4 B[1][1] = 84e24ba0adb4fbe6 B[1][2] = 13c5781eff85ba62 B[1][3] = d42892dc64290da4 B[1][4] = d4d1e89586911dc3 
B[2][0] = dbbf149e97303a40 B[2][1] = f58f6e4671b40b62 B[2][2] = 97359b120fe0fba4 B[2][3] = 20d9290a38a2715f B[2][4] = c517e909052587f3 
B[3][0] = a00707cfb59b9578 B[3][1] = 1045ff0b1da1ae6c B[3][2] = 1408501fde21803c B[3][3] = a892dc4a9f4d445d B[3][4] = 0c43356a2b823e63 
B[4][0] = dc3227741b1ed876 B[4][1] = 56a6bbb2d6d862da B[4][2] = 4971c96f69ffa57a B[4][3] = 8450a52c439c1290 B[4][4] = 9590a8c19091a000 

[DEBUG] Round 16 - After Xi step:
A[0][0] = f548473157ff33b2 A[0][1] = cdbf5e812bf9e3e4 A[0][2] = 4388d671ff2ac0e5 A[0][3] = 9b63286cfb7443b2 A[0][4] = 0421d90d1760bf40 
A[1][0] = 259af82264bf539c A[1][1] = 84a2daa9a1b55fea A[1][2] = 13cd38132f84ba7a A[1][3] = 5c2a469ce36409a4 A[1][4] = dc91fcf7ac1325c3 
A[2][0] = 878f34ae9d347246 A[2][1] = b32d6ef6b3ec4bf0 A[2][2] = de4412722e3edee6 A[2][3] = 2499082e783263df A[2][4] = 54876188953407f3 
A[3][0] = 834a4746717a96f8 A[3][1] = b855bf4e34802f48 A[3][2] = 9280440f4821803d A[3][3] = 9330dc083f2f6534 A[3][4] = 0c64656e2dc62313 
A[4][0] = dca09f361b1e1c72 A[4][1] = 56e6ba9252dc7ad8 A[4][2] = 5934e161697a9f78 A[4][3] = c05837bc47951e94 A[4][4] = 454088511000a083 

[DEBUG] Round 16 - After last step (RC):
A[0][0] = 7548473157ffb3b0 A[0][1] = cdbf5e812bf9e3e4 A[0][2] = 4388d671ff2ac0e5 A[0][3] = 9b63286cfb7443b2 A[0][4] = 0421d90d1760bf40 
A[1][0] = 259af82264bf539c A[1][1] = 84a2daa9a1b55fea A[1][2] = 13cd38132f84ba7a A[1][3] = 5c2a469ce36409a4 A[1][4] = dc91fcf7ac1325c3 
A[2][0] = 878f34ae9d347246 A[2][1] = b32d6ef6b3ec4bf0 A[2][2] = de4412722e3edee6 A[2][3] = 2499082e783263df A[2][4] = 54876188953407f3 
A[3][0] = 834a4746717a96f8 A[3][1] = b855bf4e34802f48 A[3][2] = 9280440f4821803d A[3][3] = 9330dc083f2f6534 A[3][4] = 0c64656e2dc62313 
A[4][0] = dca09f361b1e1c72 A[4][1] = 56e6ba9252dc7ad8 A[4][2] = 5934e161697a9f78 A[4][3] = c05837bc47951e94 A[4][4] = 454088511000a083 

[DEBUG] Round 17 - After Theta step:
A[0][0] = 47bf7dfe6b21c0a3 A[0][1] = ff48644e172790f7 A[0][2] = 717fecbec3f4b3f6 A[0][3] = a99412a3c7aa30a1 A[0][4] = 36d6e3c22bbecc53 
A[1][0] = 7457859bd0463926 A[1][1] = d56fa710154c3550 A[1][2] = 420045aa9b7dd0c0 A[1][3] = 0de73b25579d631e A[1][4] = 8d5c814e18ea4f79 
A[2][0] = d8579e9f06a91779 A[2][1] = ecf5c4c728712ecf A[2][2] = 819cb843b5a3bbd9 A[2][3] = 7b41a21fe3af06e0 A[2][4] = 0b5fcbb90ea962cc 
A[3][0] = b566909a72c09a0e A[3][1] = 8e796892373a23be A[3][2] = a4ac93d34b9b8ccb A[3][3] = a51c0bd43c9569c2 A[3][4] = 3a48b2b22e7c2fe5 
A[4][0] = 2211e717da5cbb5e A[4][1] = a857c2b3939eddf4 A[4][2] = a7859940a8383854 A[4][3] = 3ee94f9d86d7b9b8 A[4][4] = bbf1f070d14207af 

[DEBUG] Round 17 - After Rho step:
B[0][0] = 47bf7dfe6b21c0a3 B[0][1] = 72790f7ff48644e1 B[0][2] = 8bff65f61fa59fb3 B[0][3] = 546143532825478f B[0][4] = 8f08aefb314cdb5b 
B[1][0] = e8af0b37a08c724c B[1][1] = c3550d56fa710154 B[1][2] = 0116aa6df7430108 B[1][3] = ac63c1bce764aaf3 B[1][4] = 3572053863a93de6 
B[2][0] = 7615e7a7c1aa45de B[2][1] = 3d7131ca1c4bb3fb B[2][2] = 1ddecc0ce5c21dad B[2][3] = d10ff1d783703da0 B[2][4] = 816bf97721d52c59 
B[3][0] = a72c09a0eb566909 B[3][1] = df473cb4491b9d11 B[3][2] = a697371997495927 B[3][3] = 7a8792ad3854a381 B[3][4] = e53a48b2b22e7c2f 
B[4][0] = bed2e5daf1108f38 B[4][1] = 2b3939eddf4a857c B[4][2] = 1c1c2a53c2cca054 B[4][3] = e94f9d86d7b9b83e B[4][4] = 7c1c345081ebeefc 

[DEBUG] Round 17 - After Pi step:
B[0][0] = 47bf7dfe6b21c0a3 B[0][1] = a72c09a0eb566909 B[0][2] = e8af0b37a08c724c B[0][3] = bed2e5daf1108f38 B[0][4] = 7615e7a7c1aa45de 
B[1][0] = c3550d56fa710154 B[1][1] = 2b3939eddf4a857c B[1][2] = 3d7131ca1c4bb3fb B[1][3] = 72790f7ff48644e1 B[1][4] = df473cb4491b9d11 
B[2][0] = 1ddecc0ce5c21dad B[2][1] = 8bff65f61fa59fb3 B[2][2] = a697371997495927 B[2][3] = 0116aa6df7430108 B[2][4] = 1c1c2a53c2cca054 
B[3][0] = 7a8792ad3854a381 B[3][1] = ac63c1bce764aaf3 B[3][2] = e94f9d86d7b9b83e B[3][3] = d10ff1d783703da0 B[3][4] = 546143532825478f 
B[4][0] = 7c1c345081ebeefc B[4][1] = 816bf97721d52c59 B[4][2] = 8f08aefb314cdb5b B[4][3] = e53a48b2b22e7c2f B[4][4] = 3572053863a93de6 

[DEBUG] Round 17 - After Xi step:
A[0][0] = 5b35bdf66ea3dc0a A[0][1] = 27ea4db2ebf3738a A[0][2] = 6a290d26238c3a48 A[0][3] = bfd445daf2518e30 A[0][4] = 760de5e4436e659a 
A[1][0] = a1541ff7e265a354 A[1][1] = 0f39b9e53f0aa53c A[1][2] = 7439b94c5cfb13e3 A[1][3] = a2705eedf4b67841 A[1][4] = 9f267db4613ada9a 
A[2][0] = 19c6e85c646951d1 A[2][1] = 8af75db51f349bbb A[2][2] = a0971560b70d1a66 A[2][3] = 2526a24dc74d4107 A[2][4] = 3d0e2e7b81449834 
A[3][0] = 7924db035254a382 A[3][1] = 8a67c13c2d66ebf3 A[3][2] = 89e89c825739983a A[3][3] = cbcf549fc260beb0 A[3][4] = 1664a1d4a8270797 
A[4][0] = fc5c345011bbefa8 A[4][1] = 897ac93a35dda82d A[4][2] = 9a589e332d0f5ae8 A[4][3] = a5134297b6a83cee A[4][4] = bc301d286bb8a5e7 

[DEBUG] Round 17 - After last step (RC):
A[0][0] = db35bdf66ea3dc8a A[0][1] = 27ea4db2ebf3738a A[0][2] = 6a290d26238c3a48 A[0][3] = bfd445daf2518e30 A[0][4] = 760de5e4436e659a 
A[1][0] = a1541ff7e265a354 A[1][1] = 0f39b9e53f0aa53c A[1][2] = 7439b94c5cfb13e3 A[1][3] = a2705eedf4b67841 A[1][4] = 9f267db4613ada9a 
A[2][0] = 19c6e85c646951d1 A[2][1] = 8af75db51f349bbb A[2][2] = a0971560b70d1a66 A[2][3] = 2526a24dc74d4107 A[2][4] = 3d0e2e7b81449834 
A[3][0] = 7924db035254a382 A[3][1] = 8a67c13c2d66ebf3 A[3][2] = 89e89c825739983a A[3][3] = cbcf549fc260beb0 A[3][4] = 1664a1d4a8270797 
A[4][0] = fc5c345011bbefa8 A[4][1] = 897ac93a35dda82d A[4][2] = 9a589e332d0f5ae8 A[4][3] = a5134297b6a83cee A[4][4] = bc301d286bb8a5e7 

[DEBUG] Round 18 - After Theta step:
A[0][0] = e36cf91e92eb364f A[0][1] = 1fb3095a17bb994f A[0][2] = 527049cedfc4d08d A[0][3] = 878d01320e1964f5 A[0][4] = 4e54a10cbf268f5f 
A[1][0] = a9671bd4e134cfc8 A[1][1] = 070abdc63c5bc9a0 A[1][2] = 7c0abd6f5faa7f7f A[1][3] = aa435acef7e714dd A[1][4] = 97157997626bb606 
A[2][0] = b0c433b7f4e93458 A[2][1] = 23f5865e8fb4fe32 A[2][2] = 0995ce8b278d7fef A[2][3] = 8c2479a657cd248e A[2][4] = 940cf59011c4fdbd 
A[3][0] = be108e7170fea274 A[3][1] = 4d53944e0fccea05 A[3][2] = 4edcc9f0759399cc A[3][3] = 0cfb01ede0cabf46 A[3][4] = d150f4a68a8d0661 
A[4][0] = e502fd1e7c317b00 A[4][1] = 9024007458573c85 A[4][2] = 8306577d4085ce40 A[4][3] = bc4d8bd9db22a846 A[4][4] = a56ed4660632314f 

[DEBUG] Round 18 - After Rho step:
B[0][0] = e36cf91e92eb364f B[0][1] = 7bb994f1fb3095a1 B[0][2] = 93824e76fe26846a B[0][3] = 32c9eb0f1a02641c B[0][4] = 8432fc9a3d7d3952 
B[1][0] = 52ce37a9c2699f91 B[1][1] = bc9a0070abdc63c5 B[1][2] = 2af5bd7ea9fdfdf0 B[1][3] = e29bb5486b59defc B[1][4] = 5c55e65d89aed81a 
B[2][0] = 2c310cedfd3a4d16 B[2][1] = fd6197a3ed3f8c88 B[2][2] = 6bff784cae74593c B[2][3] = 3cd32be692474612 B[2][4] = b2819eb202389fb7 
B[3][0] = 170fea274be108e7 B[3][1] = 02a6a9ca2707e675 B[3][2] = e0eb2733989db993 B[3][3] = 3dbc1957e8c19f60 B[3][4] = 61d150f4a68a8d06 
B[4][0] = f3e18bd8072817e8 B[4][1] = 07458573c8590240 B[4][2] = 42e72041832bbea0 B[4][3] = 4d8bd9db22a846bc B[4][4] = b519818c8c53e95b 

[DEBUG] Round 18 - After Pi step:
B[0][0] = e36cf91e92eb364f B[0][1] = 170fea274be108e7 B[0][2] = 52ce37a9c2699f91 B[0][3] = f3e18bd8072817e8 B[0][4] = 2c310cedfd3a4d16 
B[1][0] = bc9a0070abdc63c5 B[1][1] = 07458573c8590240 B[1][2] = fd6197a3ed3f8c88 B[1][3] = 7bb994f1fb3095a1 B[1][4] = 02a6a9ca2707e675 
B[2][0] = 6bff784cae74593c B[2][1] = 93824e76fe26846a B[2][2] = e0eb2733989db993 B[2][3] = 2af5bd7ea9fdfdf0 B[2][4] = 42e72041832bbea0 
B[3][0] = 3dbc1957e8c19f60 B[3][1] = e29bb5486b59defc B[3][2] = 4d8bd9db22a846bc B[3][3] = 3cd32be692474612 B[3][4] = 32c9eb0f1a02641c 
B[4][0] = b519818c8c53e95b B[4][1] = b2819eb202389fb7 B[4][2] = 8432fc9a3d7d3952 B[4][3] = 61d150f4a68a8d06 B[4][4] = 5c55e65d89aed81a 

[DEBUG] Round 18 - After Xi step:
A[0][0] = a009811296cb2e77 A[0][1] = 878da0237dc78ccd A[0][2] = 524417b9d2e9ae82 A[0][3] = f3a5a2d607e57fb8 A[0][4] = 6c700cec7d125596 
A[1][0] = a89a0163eb5de585 A[1][1] = 675c347bc90058d4 A[1][2] = f0614f6bcf1fcaa4 A[1][3] = 6fbb9671e93297a3 A[1][4] = 32ae62c43f07a669 
A[2][0] = ebfef8c4aa663927 A[2][1] = 838244c4fe068569 A[2][2] = 60db033385c880d1 A[2][3] = 6bf5ed6e8d7574f4 A[2][4] = 0ef32411028726a2 
A[3][0] = 7fd86145fa698964 A[3][1] = e795d54d2298debc A[3][2] = 1f47dafae0a8c03d A[3][3] = aef3a0ee936754fa A[3][4] = 12e9e3af6e126118 
A[4][0] = a98b81eca547a8db A[4][1] = b2c19be282209db7 A[4][2] = 29137c98106b395a A[4][3] = 69c944d55e9a0d07 A[4][4] = 5ed3475f8bab7a7b 

[DEBUG] Round 18 - After last step (RC):
A[0][0] = a009811296cbae7d A[0][1] = 878da0237dc78ccd A[0][2] = 524417b9d2e9ae82 A[0][3] = f3a5a2d607e57fb8 A[0][4] = 6c700cec7d125596 
A[1][0] = a89a0163eb5de585 A[1][1] = 675c347bc90058d4 A[1][2] = f0614f6bcf1fcaa4 A[1][3] = 6fbb9671e93297a3 A[1][4] = 32ae62c43f07a669 
A[2][0] = ebfef8c4aa663927 A[2][1] = 838244c4fe068569 A[2][2] = 60db033385c880d1 A[2][3] = 6bf5ed6e8d7574f4 A[2][4] = 0ef32411028726a2 
A[3][0] = 7fd86145fa698964 A[3][1] = e795d54d2298debc A[3][2] = 1f47dafae0a8c03d A[3][3] = aef3a0ee936754fa A[3][4] = 12e9e3af6e126118 
A[4][0] = a98b81eca547a8db A[4][1] = b2c19be282209db7 A[4][2] = 29137c98106b395a A[4][3] = 69c944d55e9a0d07 A[4][4] = 5ed3475f8bab7a7b 

[DEBUG] Round 19 - After Theta step:
A[0][0] = 602ff98202185949 A[0][1] = 47abd8b3e9147bf9 A[0][2] = 92626f29463a59b6 A[0][3] = 3383da469336888c A[0][4] = ac56747ce9c1a2a2 
A[1][0] = 99cd754914fb9e0b A[1][1] = 560b405136a6235a A[1][2] = c1363b4130b9b12a A[1][3] = 5eece25b1694ec2d A[1][4] = 03f916eec0a1dde7 
A[2][0] = ff6c2d651b483b16 A[2][1] = 971091654f288758 A[2][2] = 7449d69234e682e0 A[2][3] = 7f6738cf3c5b76c5 A[2][4] = 1a61f1b0b3a92493 
A[3][0] = 18ffdd3060491139 A[3][1] = 80b26938b8b846e1 A[3][2] = 7860668f7a885860 A[3][3] = c9d41c9b0947cca7 A[3][4] = 75ce5fdaf432f945 
A[4][0] = 46b09d3be64e46e5 A[4][1] = 5dfa8735c1297389 A[4][2] = c628604f5362d764 A[4][3] = 86f258021d93e339 A[4][4] = b1e85b88c8a29445 

[DEBUG] Round 19 - After Rho step:
B[0][0] = 602ff98202185949 B[0][1] = 9147bf947abd8b3e B[0][2] = 9313794a31d2cdb4 B[0][3] = 6d11186707b48d26 B[0][4] = d1f3a7068a8ab159 
B[1][0] = 339aea9229f73c17 B[1][1] = 6235a560b405136a B[1][2] = d8ed04c2e6c4ab04 B[1][3] = 9d85abdd9c4b62d2 B[1][4] = 0fe45bbb0287779c 
B[2][0] = bfdb0b5946d20ec5 B[2][1] = c4245953ca21d625 B[2][2] = 341703a24eb491a7 B[2][3] = 9c679e2dbb62bfb3 B[2][4] = 634c3e3616752492 
B[3][0] = 06049113918ffdd3 B[3][1] = 70c059349c5c5c23 B[3][2] = 1ef510b0c0f0c0cd B[3][3] = 936128f994f93a83 B[3][4] = 4575ce5fdaf432f9 
B[4][0] = df3272372a3584e9 B[4][1] = 735c12973895dfa8 B[4][2] = b16bb263143027a9 B[4][3] = f258021d93e33986 B[4][4] = 16e23228a5116c7a 

[DEBUG] Round 19 - After Pi step:
B[0][0] = 602ff98202185949 B[0][1] = 06049113918ffdd3 B[0][2] = 339aea9229f73c17 B[0][3] = df3272372a3584e9 B[0][4] = bfdb0b5946d20ec5 
B[1][0] = 6235a560b405136a B[1][1] = 735c12973895dfa8 B[1][2] = c4245953ca21d625 B[1][3] = 9147bf947abd8b3e B[1][4] = 70c059349c5c5c23 
B[2][0] = 341703a24eb491a7 B[2][1] = 9313794a31d2cdb4 B[2][2] = 1ef510b0c0f0c0cd B[2][3] = d8ed04c2e6c4ab04 B[2][4] = b16bb263143027a9 
B[3][0] = 936128f994f93a83 B[3][1] = 9d85abdd9c4b62d2 B[3][2] = f258021d93e33986 B[3][3] = 9c679e2dbb62bfb3 B[3][4] = 6d11186707b48d26 
B[4][0] = 16e23228a5116c7a B[4][1] = 634c3e3616752492 B[4][2] = d1f3a7068a8ab159 B[4][3] = 4575ce5fdaf432f9 B[4][4] = 0fe45bbb0287779c 

[DEBUG] Round 19 - After Xi step:
A[0][0] = 742dfb0048a8d9cc A[0][1] = 8607f85b90cdfdc7 A[0][2] = 294bea3229273cdf A[0][3] = 979a7275ae75a4e9 A[0][4] = 3ef0a91a46f22d4d 
A[1][0] = e1558d39244c396a A[1][1] = 7fd89002b49cfdea A[1][2] = 242c5b5ed922ef27 A[1][3] = 954525b9639f9f8d A[1][4] = 3cd051309fd8d425 
A[2][0] = 309511a26fb4d5df A[2][1] = f15b6d6833e6c9b4 A[2][2] = 1f56b5b2c8f84094 A[2][3] = 99fd4490a650ab4c A[2][4] = b38ff1fb14335531 
A[3][0] = f36ce17b96f12b82 A[3][1] = 99852adc1dc1bb93 A[3][2] = d0504a8db2963580 A[3][3] = 0665ae0d9b633bb3 A[3][4] = dd0a182743e48567 
A[4][0] = 14f2364811146e58 A[4][1] = 12143cb23e6526ba A[4][2] = 15d7b647488a7379 A[4][3] = 453043df8a7c39ef A[4][4] = 4fe40b9f9a8b27be 

[DEBUG] Round 19 - After last step (RC):
A[0][0] = f42dfb00c8a8d9c6 A[0][1] = 8607f85b90cdfdc7 A[0][2] = 294bea3229273cdf A[0][3] = 979a7275ae75a4e9 A[0][4] = 3ef0a91a46f22d4d 
A[1][0] = e1558d39244c396a A[1][1] = 7fd89002b49cfdea A[1][2] = 242c5b5ed922ef27 A[1][3] = 954525b9639f9f8d A[1][4] = 3cd051309fd8d425 
A[2][0] = 309511a26fb4d5df A[2][1] = f15b6d6833e6c9b4 A[2][2] = 1f56b5b2c8f84094 A[2][3] = 99fd4490a650ab4c A[2][4] = b38ff1fb14335531 
A[3][0] = f36ce17b96f12b82 A[3][1] = 99852adc1dc1bb93 A[3][2] = d0504a8db2963580 A[3][3] = 0665ae0d9b633bb3 A[3][4] = dd0a182743e48567 
A[4][0] = 14f2364811146e58 A[4][1] = 12143cb23e6526ba A[4][2] = 15d7b647488a7379 A[4][3] = 453043df8a7c39ef A[4][4] = 4fe40b9f9a8b27be 

[DEBUG] Round 20 - After Theta step:
A[0][0] = cba06a24d4ce3c12 A[0][1] = b98a697f8cab1813 A[0][2] = 16c67b163541d90b A[0][3] = a817e351b213413d A[0][4] = 017d383e5a94c899 
A[1][0] = fa8a4719f01aed15 A[1][1] = 64075a2260ca2995 A[1][2] = 3ff3917e0d743b58 A[1][3] = 8e9aef99b7c94bf2 A[1][4] = 270f9b104b8e005a 
A[2][0] = e00d4d4f1843835a A[2][1] = 21c3318544119f31 A[2][2] = cfcee95fbf0f1611 A[2][3] = 4965187dd1a7fdc9 A[2][4] = 6317ad1663c403b4 
A[3][0] = 344d74925e20c294 A[3][1] = 5ea4bf35d5105285 A[3][2] = 1771df647a47dc96 A[3][3] = c1443be453b2d2a5 A[3][4] = 1a2b8dce8b356c71 
A[4][0] = 91326545c3be57e8 A[4][1] = 97d46fbfeccf1f0a A[4][2] = 9017e54a9a204ac9 A[4][3] = c0f010d258d6005f A[4][4] = ca24589248211e0e 

[DEBUG] Round 20 - After Rho step:
B[0][0] = cba06a24d4ce3c12 B[0][1] = cab1813b98a697f8 B[0][2] = b633d8b1aa0ec858 B[0][3] = 26827b502fc6a364 B[0][4] = e0f96a53226405f4 
B[1][0] = f5148e33e035da2b B[1][1] = a299564075a2260c B[1][2] = ce45f835d0ed60ff B[1][3] = 297e51d35df336f9 B[1][4] = 9c3e6c412e380168 
B[2][0] = b8035353c610e0d6 B[2][1] = 70cc61510467cc48 B[2][2] = 78b08e7e774afdf8 B[2][3] = 8c3ee8d3fee4a4b2 B[2][4] = 8c62f5a2cc788076 
B[3][0] = 25e20c294344d749 B[3][1] = 42af525f9aea8829 B[3][2] = c8f48fb92c2ee3be B[3][3] = 7c8a765a54b82887 B[3][4] = 711a2b8dce8b356c 
B[4][0] = 2e1df2bf4489932a B[4][1] = fbfeccf1f0a97d46 B[4][2] = 102564c80bf2a54d B[4][3] = f010d258d6005fc0 B[4][4] = 162492084783b289 

[DEBUG] Round 20 - After Pi step:
B[0][0] = cba06a24d4ce3c12 B[0][1] = 25e20c294344d749 B[0][2] = f5148e33e035da2b B[0][3] = 2e1df2bf4489932a B[0][4] = b8035353c610e0d6 
B[1][0] = a299564075a2260c B[1][1] = fbfeccf1f0a97d46 B[1][2] = 70cc61510467cc48 B[1][3] = cab1813b98a697f8 B[1][4] = 42af525f9aea8829 
B[2][0] = 78b08e7e774afdf8 B[2][1] = b633d8b1aa0ec858 B[2][2] = c8f48fb92c2ee3be B[2][3] = ce45f835d0ed60ff B[2][4] = 102564c80bf2a54d 
B[3][0] = 7c8a765a54b82887 B[3][1] = 297e51d35df336f9 B[3][2] = f010d258d6005fc0 B[3][3] = 8c3ee8d3fee4a4b2 B[3][4] = 26827b502fc6a364 
B[4][0] = 162492084783b289 B[4][1] = 8c62f5a2cc788076 B[4][2] = e0f96a53226405f4 B[4][3] = 711a2b8dce8b356c B[4][4] = 9c3e6c412e380168 

[DEBUG] Round 20 - After Xi step:
A[0][0] = 9380e21ad686e5e2 A[0][1] = 21e31c2949425751 A[0][2] = 7d24009bc83df99d A[0][3] = 2a598abb04c0f32d A[0][4] = a80377d3c700c592 
A[1][0] = a69326407512260b A[1][1] = f2b2cdb3a5584be7 A[1][2] = 40cc3111d667d008 A[1][3] = ca8b81f9b6a613f8 A[1][4] = 642d494fbeee8a09 
A[2][0] = 7a940e7e74496ff0 A[2][1] = 32337c912a06485e A[2][2] = c81da7ba0c4ae38a A[2][3] = bf45fb39d0e671b3 A[2][4] = 881960c90bcaa545 
A[3][0] = b50a1e7ec4f42495 A[3][1] = 08fe59da5ef761f0 A[3][2] = e5145678161185cb A[3][3] = 823b38e1fee426b0 A[3][4] = 06836842efc643f2 
A[4][0] = 363d864866a3b085 A[4][1] = 567e35727cd1a870 A[4][2] = e0310b13262601b4 A[4][3] = b1ba2a8d56ad31bc A[4][4] = de926c4d36d20941 

[DEBUG] Round 20 - After last step (RC):
A[0][0] = 1380e21a56866563 A[0][1] = 21e31c2949425751 A[0][2] = 7d24009bc83df99d A[0][3] = 2a598abb04c0f32d A[0][4] = a80377d3c700c592 
A[1][0] = a69326407512260b A[1][1] = f2b2cdb3a5584be7 A[1][2] = 40cc3111d667d008 A[1][3] = ca8b81f9b6a613f8 A[1][4] = 642d494fbeee8a09 
A[2][0] = 7a940e7e74496ff0 A[2][1] = 32337c912a06485e A[2][2] = c81da7ba0c4ae38a A[2][3] = bf45fb39d0e671b3 A[2][4] = 881960c90bcaa545 
A[3][0] = b50a1e7ec4f42495 A[3][1] = 08fe59da5ef761f0 A[3][2] = e5145678161185cb A[3][3] = 823b38e1fee426b0 A[3][4] = 06836842efc643f2 
A[4][0] = 363d864866a3b085 A[4][1] = 567e35727cd1a870 A[4][2] = e0310b13262601b4 A[4][3] = b1ba2a8d56ad31bc A[4][4] = de926c4d36d20941 

[DEBUG] Round 21 - After Theta step:
A[0][0] = 884c385b16670cf4 A[0][1] = ba2fc66809a33ec6 A[0][2] = e6e8dada88dc900a A[0][3] = b19550fa44219aba A[0][4] = 33cfad9287e1ac05 
A[1][0] = 0442b8cb7379fabe A[1][1] = 50635338a3339752 A[1][2] = e21daf9ad00c0cbd A[1][3] = 685a1f72b0cdcf4d A[1][4] = c6fcd7c4b88556bc 
A[2][0] = 786f9ed5404d003c A[2][1] = 30c8ec3a1e022792 A[2][2] = cae63711384e8c46 A[2][3] = bdbe6b92e4e21e7f A[2][4] = 8ae2f0623fceca89 
A[3][0] = dc59ad09f58b773e A[3][1] = 61adeaad6f88325b A[3][2] = 8c47e50f276ed660 A[3][3] = eb688b96cf9b751b A[3][4] = 6fd0db35deb91059 
A[4][0] = 705fc0b7d3e0ef48 A[4][1] = 101c738dc992f7bd A[4][2] = a6534dec93655e79 A[4][3] = f7d86c72e3ee6e71 A[4][4] = 98f02ab28391568c 

[DEBUG] Round 21 - After Rho step:
B[0][0] = 884c385b16670cf4 B[0][1] = 9a33ec6ba2fc6680 B[0][2] = 3746d6d446e48057 B[0][3] = 433575632aa1f488 B[0][4] = b64a1f86b014cf3e 
B[1][0] = 08857196e6f3f57c B[1][1] = 3975250635338a33 B[1][2] = 76be6b403032f788 B[1][3] = b9e9ad0b43ee5619 B[1][4] = 1bf35f12e2155af3 
B[2][0] = 1e1be7b55013400f B[2][1] = 323b0e878089e48c B[2][2] = 7462365731b889c2 B[2][3] = 35c972710f3fdedf B[2][4] = 315c5e0c47f9d951 
B[3][0] = 9f58b773edc59ad0 B[3][1] = 2db0d6f556b7c419 B[3][2] = 1e4eddacc1188fca B[3][3] = 72d9f36ea37d6d11 B[3][4] = 596fd0db35deb910 
B[4][0] = be9f077a4382fe05 B[4][1] = 38dc992f7bd101c7 B[4][2] = b2af3cd329a6f649 B[4][3] = d86c72e3ee6e71f7 B[4][4] = 0aaca0e455a3263c 

[DEBUG] Round 21 - After Pi step:
B[0][0] = 884c385b16670cf4 B[0][1] = 9f58b773edc59ad0 B[0][2] = 08857196e6f3f57c B[0][3] = be9f077a4382fe05 B[0][4] = 1e1be7b55013400f 
B[1][0] = 3975250635338a33 B[1][1] = 38dc992f7bd101c7 B[1][2] = 323b0e878089e48c B[1][3] = 9a33ec6ba2fc6680 B[1][4] = 2db0d6f556b7c419 
B[2][0] = 7462365731b889c2 B[2][1] = 3746d6d446e48057 B[2][2] = 1e4eddacc1188fca B[2][3] = 76be6b403032f788 B[2][4] = b2af3cd329a6f649 
B[3][0] = 72d9f36ea37d6d11 B[3][1] = b9e9ad0b43ee5619 B[3][2] = d86c72e3ee6e71f7 B[3][3] = 35c972710f3fdedf B[3][4] = 433575632aa1f488 
B[4][0] = 0aaca0e455a3263c B[4][1] = 315c5e0c47f9d951 B[4][2] = b64a1f86b014cf3e B[4][3] = 596fd0db35deb910 B[4][4] = 1bf35f12e2155af3 

[DEBUG] Round 21 - After Xi step:
A[0][0] = cc4e2a0a16ef0d34 A[0][1] = 985af1a3e9e11ac0 A[0][2] = 04c1a0bea7e3fe3e A[0][3] = da13047a53806f0d A[0][4] = 8c14cfb77913724f 
A[1][0] = 3bece42eb776ee22 A[1][1] = b075b0247adb57cf A[1][2] = f21b2cc4aeef94b9 A[1][3] = 9b72fc5aadf16ed7 A[1][4] = 6ca097d554b6c499 
A[2][0] = 7c4636d7653a8bee A[2][1] = 375284d042f50917 A[2][2] = 384cd0a8d10801c2 A[2][3] = 3e98ebca00f2d688 A[2][4] = aa6d36c3e9b2fc3a 
A[3][0] = f299eb75a13965d1 A[3][1] = 37e90c78ebea5499 A[3][2] = d0e912f3a88d41b7 A[3][3] = 935975514d3f98da A[3][4] = 473dd5c63aa3f484 
A[4][0] = 3b9da5e074b3a43f A[4][1] = 11d8560055e9d856 A[4][2] = 84701187b01ccfbe A[4][3] = 594f38da95a2b990 A[4][4] = 3a534f52e4b1dee3 

[DEBUG] Round 21 - After last step (RC):
A[0][0] = 4c4e2a0a16ef8db4 A[0][1] = 985af1a3e9e11ac0 A[0][2] = 04c1a0bea7e3fe3e A[0][3] = da13047a53806f0d A[0][4] = 8c14cfb77913724f 
A[1][0] = 3bece42eb776ee22 A[1][1] = b075b0247adb57cf A[1][2] = f21b2cc4aeef94b9 A[1][3] = 9b72fc5aadf16ed7 A[1][4] = 6ca097d554b6c499 
A[2][0] = 7c4636d7653a8bee A[2][1] = 375284d042f50917 A[2][2] = 384cd0a8d10801c2 A[2][3] = 3e98ebca00f2d688 A[2][4] = aa6d36c3e9b2fc3a 
A[3][0] = f299eb75a13965d1 A[3][1] = 37e90c78ebea5499 A[3][2] = d0e912f3a88d41b7 A[3][3] = 935975514d3f98da A[3][4] = 473dd5c63aa3f484 
A[4][0] = 3b9da5e074b3a43f A[4][1] = 11d8560055e9d856 A[4][2] = 84701187b01ccfbe A[4][3] = 594f38da95a2b990 A[4][4] = 3a534f52e4b1dee3 

[DEBUG] Round 22 - After Theta step:
A[0][0] = 9dc79966c2b15725 A[0][1] = 49d342cf3dbfc051 A[0][2] = d54813d273bd24af A[0][3] = 0b9ab71687deb59c A[0][4] = 5d9d7cdbad4da8de 
A[1][0] = 72652bb8fa07c939 A[1][1] = f9fc7fb237aa70d4 A[1][2] = bb92e352e39eb3a2 A[1][3] = d2fb33cce08049cc A[1][4] = 2529584319c7e382 
A[2][0] = 71ec8f45d4bb35b7 A[2][1] = 3af83d42f374b74e A[2][2] = 35e6693a6089bf9b A[2][3] = 33325258b17368d1 A[2][4] = a7c78f5158334263 
A[3][0] = 8f677f0c7e156511 A[3][1] = 4a17980134c65459 A[3][2] = ad17868a77a14177 A[3][3] = eea7e1289213981a A[3][4] = 3ac341bfe58ff444 
A[4][0] = f7c5913d058d508f A[4][1] = dd8062dd24d72ce6 A[4][2] = 4828255ac1223b0e A[4][3] = 95170c07e49c4d20 A[4][4] = f60b7b8f958f2a53 

[DEBUG] Round 22 - After Rho step:
B[0][0] = 9dc79966c2b15725 B[0][1] = dbfc05149d342cf3 B[0][2] = aa409e939de9257e B[0][3] = bd6b3817356e2d0f B[0][4] = f36eb536a3797675 
B[1][0] = e4ca5771f40f9272 B[1][1] = a70d4f9fc7fb237a B[1][2] = 4b8d4b8e7ace8aee B[1][3] = 09399a5f66799c10 B[1][4] = 94a5610c671f8e08 
B[2][0] = dc7b23d1752ecd6d B[2][1] = be0f50bcdd2dd38e B[2][2] = 4dfcd9af3349d304 B[2][3] = 292c58b9b4689999 B[2][4] = 74f8f1ea2b06684c 
B[3][0] = c7e1565118f677f0 B[3][1] = 2ca50bcc009a632a B[3][2] = 14ef4282ef5a2f0d B[3][3] = 25124273035dd4fc B[3][4] = 443ac341bfe58ff4 
B[4][0] = e82c6a847fbe2c89 B[4][1] = 2dd24d72ce6dd806 B[4][2] = 911d87241412ad60 B[4][3] = 170c07e49c4d2095 B[4][4] = dee3e563ca94fd82 

[DEBUG] Round 22 - After Pi step:
B[0][0] = 9dc79966c2b15725 B[0][1] = c7e1565118f677f0 B[0][2] = e4ca5771f40f9272 B[0][3] = e82c6a847fbe2c89 B[0][4] = dc7b23d1752ecd6d 
B[1][0] = a70d4f9fc7fb237a B[1][1] = 2dd24d72ce6dd806 B[1][2] = be0f50bcdd2dd38e B[1][3] = dbfc05149d342cf3 B[1][4] = 2ca50bcc009a632a 
B[2][0] = 4dfcd9af3349d304 B[2][1] = aa409e939de9257e B[2][2] = 14ef4282ef5a2f0d B[2][3] = 4b8d4b8e7ace8aee B[2][4] = 911d87241412ad60 
B[3][0] = 25124273035dd4fc B[3][1] = 09399a5f66799c10 B[3][2] = 170c07e49c4d2095 B[3][3] = 292c58b9b4689999 B[3][4] = bd6b3817356e2d0f 
B[4][0] = dee3e563ca94fd82 B[4][1] = 74f8f1ea2b06684c B[4][2] = f36eb536a3797675 B[4][3] = 443ac341bfe58ff4 B[4][4] = 94a5610c671f8e08 

[DEBUG] Round 22 - After Xi step:
A[0][0] = d5370946f2b18721 A[0][1] = 45e1c4d009765288 A[0][2] = e42a5573d65dbe73 A[0][3] = e82d200e1d74ae85 A[0][4] = 4d63a7f1612e412d 
A[1][0] = 870f4dcfc7ef2782 A[1][1] = 2ceb4d3eac7d4006 A[1][2] = bd0f55d8cd28d31e A[1][3] = fbdc152519143de2 A[1][4] = 00c733df21f66325 
A[2][0] = 971d7caffbc9fa06 A[2][1] = de80ff3394ef4532 A[2][2] = f48df290cc6a796d A[2][3] = 0f9fc8ce714b8c8a A[2][4] = 9199c62c56032f60 
A[3][0] = 24165a77037cd6d9 A[3][1] = 8a389c4e76898ba0 A[3][2] = 138c45a5c84ba097 A[3][3] = 8128703df472b990 A[3][4] = f5313ac6254e6c6a 
A[4][0] = fceba3facfdeddd8 A[4][1] = 5ceaf8c8ed0fe04a A[4][2] = e96bb5baaa5937f9 A[4][3] = 57eac6513fe58f86 A[4][4] = b4216900678fac0a 

[DEBUG] Round 22 - After last step (RC):
A[0][0] = d537094672b18720 A[0][1] = 45e1c4d009765288 A[0][2] = e42a5573d65dbe73 A[0][3] = e82d200e1d74ae85 A[0][4] = 4d63a7f1612e412d 
A[1][0] = 870f4dcfc7ef2782 A[1][1] = 2ceb4d3eac7d4006 A[1][2] = bd0f55d8cd28d31e A[1][3] = fbdc152519143de2 A[1][4] = 00c733df21f66325 
A[2][0] = 971d7caffbc9fa06 A[2][1] = de80ff3394ef4532 A[2][2] = f48df290cc6a796d A[2][3] = 0f9fc8ce714b8c8a A[2][4] = 9199c62c56032f60 
A[3][0] = 24165a77037cd6d9 A[3][1] = 8a389c4e76898ba0 A[3][2] = 138c45a5c84ba097 A[3][3] = 8128703df472b990 A[3][4] = f5313ac6254e6c6a 
A[4][0] = fceba3facfdeddd8 A[4][1] = 5ceaf8c8ed0fe04a A[4][2] = e96bb5baaa5937f9 A[4][3] = 57eac6513fe58f86 A[4][4] = b4216900678fac0a 

[DEBUG] Round 23 - After Theta step:
A[0][0] = a476af389ee27a7c A[0][1] = 34a062aee525afd4 A[0][2] = 956bf30d3a0e432f A[0][3] = 996c8670f12753d9 A[0][4] = 3c22018f8d7dbc71 
A[1][0] = 1091ad081e276897 A[1][1] = bb75adf975b50f13 A[1][2] = 2a91b51f14e09c0b A[1][3] = 6c42f5e2c0dc72f7 A[1][4] = 9759d318f83e2c30 
A[2][0] = e99a9db2bc954072 A[2][1] = a0071e2ed3b3ff46 A[2][2] = 8a0a138d8b36c319 A[2][3] = 711829d3361736fe A[2][4] = ef1e2731115f9514 
A[3][0] = 5242a62a26bce0a5 A[3][1] = fc6c60135349bddc A[3][2] = 65d8b9f8ed8b96eb A[3][3] = f77c8c60d1b28fec A[3][4] = 8365c69b008e5a16 
A[4][0] = 963454a800ddfd2b A[4][1] = 36350f9a220cc0b9 A[4][2] = 83b442e8655a170a A[4][3] = 3d353103f0e6af75 A[4][4] = defe9e52a88c8cf9 

[DEBUG] Round 23 - After Rho step:
B[0][0] = a476af389ee27a7c B[0][1] = 525afd434a062aee B[0][2] = ab5f9869d072197c B[0][3] = 4ea7b332d90ce1e2 B[0][4] = 063e35f6f1c4f088 
B[1][0] = 21235a103c4ed12e B[1][1] = 50f13bb75adf975b B[1][2] = 46d47c5382702caa B[1][3] = 8e5eed885ebc581b B[1][4] = 5d674c63e0f8b0c2 
B[2][0] = ba66a76caf25501c B[2][1] = 01c78bb4ecffd1a8 B[2][2] = b618cc50509c6c59 B[2][3] = 14e99b0b9b7f388c B[2][4] = 9de3c4e6222bf2a2 
B[3][0] = a26bce0a55242a62 B[3][1] = ee7e363009a9a4de B[3][2] = f1db172dd6cbb173 B[3][3] = 8c1a3651fd9eef91 B[3][4] = 168365c69b008e5a 
B[4][0] = 4006efe95cb1a2a5 B[4][1] = f9a220cc0b936350 B[4][2] = ad0b8541da217432 B[4][3] = 353103f0e6af753d B[4][4] = a794aa23233e77bf 

[DEBUG] Round 23 - After Pi step:
B[0][0] = a476af389ee27a7c B[0][1] = a26bce0a55242a62 B[0][2] = 21235a103c4ed12e B[0][3] = 4006efe95cb1a2a5 B[0][4] = ba66a76caf25501c 
B[1][0] = 50f13bb75adf975b B[1][1] = f9a220cc0b936350 B[1][2] = 01c78bb4ecffd1a8 B[1][3] = 525afd434a062aee B[1][4] = ee7e363009a9a4de 
B[2][0] = b618cc50509c6c59 B[2][1] = ab5f9869d072197c B[2][2] = f1db172dd6cbb173 B[2][3] = 46d47c5382702caa B[2][4] = ad0b8541da217432 
B[3][0] = 8c1a3651fd9eef91 B[3][1] = 8e5eed885ebc581b B[3][2] = 353103f0e6af753d B[3][3] = 14e99b0b9b7f388c B[3][4] = 4ea7b332d90ce1e2 
B[4][0] = a794aa23233e77bf B[4][1] = 9de3c4e6222bf2a2 B[4][2] = 063e35f6f1c4f088 B[4][3] = 168365c69b008e5a B[4][4] = 5d674c63e0f8b0c2 

[DEBUG] Round 23 - After Xi step:
A[0][0] = 027e6b789ee2127c A[0][1] = a036562b8544324e A[0][2] = d13b4e192e4ef17d A[0][3] = 4482eff9dcc1a6a5 A[0][4] = bb67262d7d25003c 
A[1][0] = 58f309b6f7dd14db A[1][1] = fda2454c051f2353 A[1][2] = 05e78b64ccdb95a4 A[1][3] = 42737e4b53093aea A[1][4] = acda040208a5251e 
A[2][0] = 959c447252bc7c77 A[2][1] = bafe980ff071bbdc A[2][2] = f3d5232bc78b31f3 A[2][3] = 44d618978270aaf8 A[2][4] = bc4bc900fad16432 
A[3][0] = 8c783349615ee7d1 A[3][1] = ac56e7800bb8505b A[3][2] = 143049f0eaa5741b A[3][3] = 54ed1122dfce1829 A[3][4] = eca7103ed609a1fe 
A[4][0] = f715baa46323f2bc A[4][1] = c463e42228b8b3b2 A[4][2] = 06fab4523175f008 A[4][3] = 04db75c499068610 A[4][4] = 197f5c73e0701400 

[DEBUG] Round 23 - After last step (RC):
A[0][0] = 827e6b781ee29274 A[0][1] = a036562b8544324e A[0][2] = d13b4e192e4ef17d A[0][3] = 4482eff9dcc1a6a5 A[0][4] = bb67262d7d25003c 
A[1][0] = 58f309b6f7dd14db A[1][1] = fda2454c051f2353 A[1][2] = 05e78b64ccdb95a4 A[1][3] = 42737e4b53093aea A[1][4] = acda040208a5251e 
A[2][0] = 959c447252bc7c77 A[2][1] = bafe980ff071bbdc A[2][2] = f3d5232bc78b31f3 A[2][3] = 44d618978270aaf8 A[2][4] = bc4bc900fad16432 
A[3][0] = 8c783349615ee7d1 A[3][1] = ac56e7800bb8505b A[3][2] = 143049f0eaa5741b A[3][3] = 54ed1122dfce1829 A[3][4] = eca7103ed609a1fe 
A[4][0] = f715baa46323f2bc A[4][1] = c463e42228b8b3b2 A[4][2] = 06fab4523175f008 A[4][3] = 04db75c499068610 A[4][4] = 197f5c73e0701400 

Final hash (DEBUG): 7492E21E786B7E82DB14DDF7B609F358777CBC5272449C95D1E75E614933788C
Hash match for message=debug test.
```