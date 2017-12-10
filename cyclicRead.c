#include "gen.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "cyclicBuf.h"
int main() {
  int shared_file_descr = shm_open("shared_place", O_RDONLY, 0);
  if (shared_file_descr == -1) {
    perror("Can't open file");
    return shared_file_descr;
  }

  struct cyclic_buf* mem =
      mmap(NULL, sizeof(struct cyclic_buf), PROT_READ, MAP_SHARED, shared_file_descr, 0);
  if (mem == NULL) {
    perror("mmap? what's that?");
    return -1;
  }

  uint64_t current_pl = 0;
  printf("starting position: %ld\n", current_pl);

  while (1) {
    if (mem->pl == current_pl) {
    	continue;
    }
    int64_t current_seed = verify((void*)mem->BUFFER[current_pl].arr);
    if (current_seed == -1) {
      printf("Error verify! curr_seed = -1?");
      break;
    }
    printf("Verified at %ld with seed %ld\n", current_pl, current_seed);
    current_pl++;
    current_pl %= 1000;
  }
  return 0;
}
