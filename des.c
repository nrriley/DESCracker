// build using gcc des.c -lssl -lcrypto
// requires package openssl-dev

#include <openssl/des.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void)
{
    const char plain[8] = "(Hello)\0";

    DES_cblock *key = malloc(sizeof(DES_cblock));
    DES_cblock *output = malloc(sizeof(DES_cblock));
    DES_key_schedule *key_schedule = malloc(sizeof(DES_key_schedule));

    DES_random_key(key); // Use random key for now
    // will work on using given keys later, just a matter of converting
    // type int to type DES_cblock


    // Print key as hex
    for(int i = 0; i < 8; i++)
        printf("%02X ", (*key)[i]);
    printf("\n");

    // Generate Key Schedule
    DES_set_key(key, key_schedule);

    // Perform DES
    DES_ecb_encrypt((DES_cblock*)&plain, output, key_schedule, DES_DECRYPT);

    // Print ciphertext as hex
    for(int i = 0; i < 8; i++)
        printf("%02X ", (*output)[i]);
    printf("\n");


    return 0;
}
