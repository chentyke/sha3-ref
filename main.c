#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>  // for gettimeofday

#include "sponge.h"

long long get_current_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)tv.tv_sec * 1000000 + tv.tv_usec;
}

void verify_hashes(const char *filename);
char* read_line_from_file(const char *filename, int line_number);

int main(int argc, char *argv[])
{

    #ifdef DEBUG
    char message[20] = "debug test";
    int32_t size = strlen(message);

    // Gen hash
    uint8_t *hash = sponge((uint8_t *)message, size);

    // Converting a hash to a hexadecimal string
    char computed_hash[65]; // Each hash value is 64 characters + 1 '\0'
    for (int j = 0; j < 32; j++) {
        sprintf(&computed_hash[j * 2], "%02X", hash[j]);
    }
    computed_hash[64] = '\0';
    printf("Final hash (DEBUG): %s\n", computed_hash);
    // Compare with known correct hash of 1
    const char *correct_hash = "7492E21E786B7E82DB14DDF7B609F358777CBC5272449C95D1E75E614933788C";
    if (strcmp(computed_hash, correct_hash) == 0) {
        printf("Hash match for message=debug test.\n");
    } else {
        printf("Hash mismatch for message=1!\n");
        printf("Expected: %s\n", correct_hash);
        printf("Got:      %s\n", computed_hash);
    }
    free(hash);

    #else
    // Non-DEBUG mode: retain test times, time measurement, and throughput statistics
    const int iterations = 120000;    // Number of test iterations

    const int msg_size = 32;
    uint8_t *msg = malloc(msg_size);
    memset(msg, 0xAB, msg_size);

    long long start = get_current_time();
    for (int i = 0; i < iterations; i++) {
        uint8_t *hash = sponge(msg, msg_size);
        free(hash);
    }
    long long end = get_current_time();
    free(msg);

    double elapsed_sec = (end - start) / 1000000.0; // total times
    double ns_per_iter = (elapsed_sec * 1e9) / iterations; // Nanoseconds per iteration
    printf("Total time: %.4f seconds\n", elapsed_sec);
    printf("Time per iteration: %.2f ns\n", ns_per_iter);

    double total_bytes = (double)msg_size * iterations;
    double throughput_MB_s = (total_bytes / elapsed_sec) / (1024.0 * 1024.0);

    printf("Throughput: %.2f MB/s\n", throughput_MB_s);

    const char *filename = "hashes";
    verify_hashes(filename);
    #endif
    return 0;
}



char* read_line_from_file(const char *filename, int line_number)
{
    if (line_number <= 0) {
        fprintf(stderr, "Line numbers must be positive\n");
        return NULL;
    }

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Failed to open file");
        return NULL;
    }

    char buffer[1024];
    int current_line = 0;
    char *result = NULL;

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        current_line++;

        if (current_line == line_number) {
            // Remove line breaks at the end of the line (if any)
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';
            }

            // Allocate memory and copy the contents of the line
            result = (char *)malloc(len + 1);
            if (result == NULL) {
                fprintf(stderr, "Memory allocation failure\n");
                fclose(fp);
                return NULL;
            }
            strcpy(result, buffer);
            break;
        }
    }
    fclose(fp);
    return result;
}

void verify_hashes(const char *filename)
{
    for (int i = 1; i <= 1000; i++) {
        char message[12]; // Enough storage for '50000' and '\0'.
        snprintf(message, sizeof(message), "%d", i);

        int32_t size = strlen(message);
        // Gen hash
        uint8_t *hash = sponge((uint8_t *)message, size);

        // Converting a hash to a hexadecimal string
        char computed_hash[65]; // Each hash value is 64 characters + 1 '\0'
        for (int j = 0; j < 32; j++) {
            sprintf(&computed_hash[j * 2], "%02X", hash[j]);
        }
        computed_hash[64] = '\0';

        char *file_hash = read_line_from_file(filename, i);

        file_hash[strcspn(file_hash, "\r\n")] = '\0';

        // Check if the hash is empty
        if (strlen(file_hash) == 0) {
            fprintf(stderr, "Empty hash at line %d\n", i);
            exit(EXIT_FAILURE);
        }

        // Compare hashes
        if (strcmp(computed_hash, file_hash) != 0) {
            fprintf(stderr, "Hash mismatch at line %d\n", i);
            fprintf(stderr, "Computed: %s\n", computed_hash);
            fprintf(stderr, "File: %s\n", file_hash);
            exit(EXIT_FAILURE);
        }
        free(hash);
    }
    printf("All hashes match.\n");
}