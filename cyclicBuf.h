#ifndef _SIMEONCH7
#define _SIMEONCH7
#define _BLOCK_SIZE 4096

#include <stdint.h>
struct chunk_t {
  volatile int arr[_BLOCK_SIZE];
};

struct cyclic_buf {
  volatile uint64_t pl;

  volatile struct chunk_t BUFFER[1000];
};

#endif

