#include "syscall.h"

#define GRND_NONBLOCK 0x01
#define GRND_RANDOM 0x02

unsigned char secure_random[256];
unsigned char secure_random_index = 0;
unsigned char unsecure_random[256];
unsigned char unsecure_random_index = 0;

// /dev/random
int get_secure_random(unsigned char buf[], unsigned int n) {
    for (int i = 0; i < n; i++) {
        if (secure_random_index == 0) {
            getrandom(secure_random, 256, GRND_RANDOM);
        }
        buf[i] = secure_random[secure_random_index];
        secure_random_index++;
    }
    return 0;
}

// /dev/urandom
int get_unsecure_random(unsigned char buf[], unsigned int n) {
    for (int i = 0; i < n; i++) {
        if (unsecure_random_index == 0) {
            getrandom(unsecure_random, 256, 0);
        }
        buf[i] = unsecure_random[unsecure_random_index];
        unsecure_random_index++;
    }
    return 0;
}
