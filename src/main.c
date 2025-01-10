#include <stdio.h>

#include "embedder.h"

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s [directory]\n", argv[0]);
    return 1;
  }

  char *dir = argv[1];
  fprintf(stderr, "FIXME run %s\n", dir);

  return 0;
}
