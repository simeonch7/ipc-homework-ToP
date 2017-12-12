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
  int shared_file_descr = shm_open("shared_buffer", O_CREAT | O_RDWR, S_IRWXU);
  if (shared_file_descr == -1) {
    perror("Can't open the file?");
    return -1;
  }

  int res;
  res = ftruncate(shared_file_descr, sizeof(struct cyclic_buf));
  if (res != 0) {
    perror("Can't truncate the file?");
    return res;
  }

  struct cyclic_buf* mem = mmap(NULL, sizeof(struct cyclic_buf),
                                PROT_READ | PROT_WRITE, MAP_SHARED, shared_file_descr, 0);
  if (mem == NULL) {
    perror("mmap??? whats that?");
    return -1;
  }

  mem->pl = 0;
  uint32_t seed = 0;
  while (1) {
    generate((void*)mem->BUFFER[mem->pl].arr, seed);
    seed++;
    mem->pl++;
   // mem->pl %= 1000;
  }
  return 0;
}
