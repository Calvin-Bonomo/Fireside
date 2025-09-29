#ifndef UTILS
#define UTILS

typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned short ushort;
typedef unsigned char uchar;

static inline void *copy(void *src, void *dst, ulong n) {
  if (!src || !dst) return (void *)0;

  char *srcCpy = src, *dstCpy = dst;
  for (ulong i = 0; i < n; i++) {
    dstCpy[i] = srcCpy[i];
  }
  return dst;
}

static inline int swap(void *p1, void *p2, ulong n) {
  if (!p1 || !p2) return -1;

  char *pByte1 = p1, *pByte2 = p2;
  for (ulong i = 0; i < n; i++) {
    pByte1[i] ^= pByte2[i];
    pByte2[i] ^= pByte1[i];
    pByte1[i] ^= pByte2[i];
  }
  return 0;
}

static inline void *clear(void *p, ulong n) {
  if (!p) return NULL;

  for (ulong i = 0; i < n; i++) {
    *((char *)p + i) = (char)0;
  }
  return p;
}

#endif