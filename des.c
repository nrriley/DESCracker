// build using gcc des.c -lssl -lcrypto -fopenmp
// requires packages:
// libssl-dev

#include <omp.h>
#include <openssl/des.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void uint64_to_cblock(uint64_t, char cblock[8]);

int main(void)
{
    const char ciphertext[43][8] = {"\x08\x92\xe7\xe6\xf4\xaf\x00\xca",
                                    "\x9c\xe6\x93\xb6\xf9\xfc\x57\xc3",
                                    "\x87\xa5\x3b\xdd\x7c\xcd\x9d\x50",
                                    "\x4d\xa9\x29\xd9\x23\x92\x8d\x17",
                                    "\x21\x4c\x28\x14\x79\x50\x80\x76",
                                    "\xbf\xc7\x81\x0a\xf9\x42\x2d\xf3",
                                    "\xfb\xab\xb0\xd7\x8a\xbc\xa8\x57",
                                    "\xba\x79\x03\xfc\x6a\xe6\x89\x67",
                                    "\xf6\xaf\xe4\xa3\x28\xa2\x4f\xe5",
                                    "\x7b\xa2\x2b\x15\x93\x13\x30\x2f",
                                    "\x7f\xe0\xfd\x72\xa4\x92\xc3\xf9",
                                    "\x0c\xa8\x59\xf4\x27\x54\x1a\xe4",
                                    "\x3b\x58\x63\x5f\x11\x31\x03\x39",
                                    "\x83\x50\x24\x52\x0d\x99\xc1\x02",
                                    "\x3e\xe2\x6b\xa3\xdc\x65\xac\xba",
                                    "\xf0\xeb\x17\x9b\x8d\x5d\x3b\x13",
                                    "\xe3\x6c\xf6\x8d\x52\x73\xfb\x3a",
                                    "\x91\xc8\xfd\x2f\xd5\x67\xe9\x3a",
                                    "\x72\xb2\x60\xf4\x63\x1f\x45\xd6",
                                    "\xda\xf0\x14\x37\x77\x45\x9b\x34",
                                    "\xe2\x1a\x32\x82\xb9\x2e\x88\x9b",
                                    "\x8f\x34\x60\x60\x43\x2b\x07\xb3",
                                    "\x50\x8b\x8f\xb7\xbc\x5f\x71\xb9",
                                    "\x6d\x4d\x11\xfc\x89\xfd\x59\x33",
                                    "\x2b\xa7\xc8\x11\x83\x48\x44\x90",
                                    "\x4e\x6a\xc9\x50\xef\xb6\x0d\x22",
                                    "\x1c\x0c\x43\x50\x39\xf6\x02\x73",
                                    "\xaf\xa8\xd3\x81\x92\x9d\xbb\x9b",
                                    "\xe4\x55\xf0\xb3\x20\x3e\x48\x2c",
                                    "\xba\xce\x3d\x6b\xe3\x3d\x1e\xce",
                                    "\x95\x2e\x51\xc9\x6f\xd8\x77\xba",
                                    "\xd8\x52\xca\x0e\xcf\xea\x4e\x45",
                                    "\x8a\x44\x65\x38\x3d\x6e\xdf\x37",
                                    "\x7c\x03\x2f\x11\xaf\x94\x32\xab",
                                    "\x1e\x14\x60\xbb\xce\x70\x5b\x78",
                                    "\x87\x7f\xed\x87\xcb\xd6\x6b\xfd",
                                    "\x11\x45\xcb\xe4\x7d\x2b\x6c\x70",
                                    "\x66\x53\x10\x64\x44\xf5\x4d\x3d",
                                    "\xb0\xf5\x64\x5e\x30\xa4\xfb\x01",
                                    "\x45\xca\x80\xac\x91\x00\xc6\x9f",
                                    "\xf7\x30\xa1\x1c\x66\x43\x77\x26",
                                    "\x1d\x0c\x28\x4c\x5b\x2f\xa3\xfb",
                                    "\x35\xac\xa6\xc3\x8a\xfb\x24\x2e"};

    #pragma omp parallel
    #pragma omp for
    for(uint64_t k = 0; k < 0x10000000000; k++) {
        uint8_t text_index = 0;
        char key[8];
        DES_cblock output;
        DES_key_schedule key_schedule;
        // Generate key
        uint64_to_cblock(k, key);

        // Generate Key Schedule
        DES_set_key_unchecked((DES_cblock *)&key, &key_schedule);

        do {
            if(text_index == 43){
                printf("KEY:\t");
                for(int i = 0; i < 8; i++)
                    printf("%02hhX ", key[i]);
                putchar('\n');
                printf("PLAIN:\t");
                for(int i = 0; i < 8; i++)
                    printf("%02hhX ", output[i]);
                putchar('\n');
                break;
            }
            DES_ecb_encrypt((DES_cblock*)&ciphertext[text_index], &output, &key_schedule, DES_DECRYPT);
            text_index++;
        } while(!(char)(output[7] << 4));


    return 0;
}

void uint64_to_cblock(uint64_t n, char retval[8])
{
    uint8_t i, j;
    for(i = 0; i < 8; i++)
        retval[i] = '\0';

    for(i = 0; i < 4; i++)
        for(j = 0; j < 7; j++)
            retval[i] |= (n & (1LL << (j + i*7))) ? (char)(0x80U >> j) : 0;

    for(i = 4; i < 8; i++)
        for(j = 0; j < 4; j++)
            retval[i] |= (n & (1LL << (j + (i-4)*7))) ? (char)(0x80U >> j) : 0;

    for(i = 4; i < 8; i++)
        for(j = 4; j < 7; j++)
            retval[i] |= (n & (1LL << (28 + (j-4) + (i-4)*3))) ? (char)(0x80U >> j) : 0;
}
