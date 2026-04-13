#include "utils.h"

#include "assert.h"

void copy(void *src, void *dst, ulong n) {
    assert(src && "src must not be NULL");
    assert(dst && "dst must not be NULL");
    assert(n && "n must be greater than 0");

    char *srcCpy = src, *dstCpy = dst;
    for (ulong i = 0; i < n; i++) {
        dstCpy[i] = srcCpy[i];
    }
}

int swap(void *p1, void *p2, ulong n) {
    assert(p1 && "p1 must not be NULL");
    assert(p2 && "p2 must not be NULL");
    assert(n && "n must be greater than 0");

    char *pByte1 = p1, *pByte2 = p2;
    for (int i = 0; i < n; i++) {
        pByte1[i] ^= pByte2[i];
        pByte2[i] ^= pByte1[i];
        pByte1[i] ^= pByte2[i];
    }
    return 0;
}

void clear(void *p, ulong n) {
    assert(p && "p must not be NULL");
    assert(n && "n must be greater than 0");

    char *pBytes = p;
    for (ulong i = 0; i < n; i++)
        pBytes[i] = 0;
}
