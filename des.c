// build using gcc des.c -lssl -lcrypto -fopenmp
// requires packages:
// libssl-dev

#include <omp.h>
#include <openssl/des.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(void)
{
    const char plain[8] = "(Hello)\0";

    uint64_t key = 0;
    DES_cblock *output = malloc(sizeof(DES_cblock));
    DES_key_schedule *key_schedule = malloc(sizeof(DES_key_schedule));


    #pragma omp parallel
    #pragma omp for
    for(key = 0; key < 1000000000; key++) { // 1 billion times
        // Generate Key Schedule
        DES_set_key((DES_cblock *)&key, key_schedule);

        // Perform DES
        DES_ecb_encrypt((DES_cblock*)&plain, output, key_schedule, DES_DECRYPT);
    }


    return 0;
}
