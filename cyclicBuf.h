#ifndef _DUMB_SHM_STRUCT
#define _DUMB_SHM_STRUCT
#define _BLOCK_SIZE 4096

#include <stdint.h>
struct chunk_t {
  volatile int arr[_BLOCK_SIZE];
};

struct cyclic_buf {
  volatile uint64_t pos;

  volatile struct chunk_t BUFFER[1000];
};

#endif

