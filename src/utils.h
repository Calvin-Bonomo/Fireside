#ifndef UTILS
#define UTILS

typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned short ushort;

inline void *copy(void *src, void *dst, ulong n) {
  if (!src || !dst) return (void *)0;

  char *srcCpy = src, *dstCpy = dst;
  for (ulong i = 0; i < n; i++) {
    dstCpy[i] = srcCpy[i];
  }
  return dst;
}

#endif