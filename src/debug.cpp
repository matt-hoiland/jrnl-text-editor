#include "debug.h"

#include <cstdlib>
#include <cstdio>

void die(const char *s, int line) {
  printf("%3d: ", line);
  perror(s);
  exit(1);
}
