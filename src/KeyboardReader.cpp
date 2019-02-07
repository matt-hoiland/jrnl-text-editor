#include "KeyboardReader.h"

#include <cerrno>
#include <cctype>
#include <cstdio>
#include <unistd.h>

#include "debug.h"

void KeyboardReader::run() {
  while (true) {
    int c = getKeyPress();
    if (c == '\0') {
      continue;
    } else if (iscntrl(c)) {
      printf("0x%02X | %03d\r\n", c, c);
    } else {
      printf("0x%02X | %03d ('%c')\r\n", c, c, c);
    }
    if (c == CTRL_KEY('q')) { break; }
  }
}

int KeyboardReader::getKeyPress() {
  int c = '\0';
  if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) {
    DIE("KeyboardReader::getKeyPress() -> read()");
  }
  switch (c) {
    case 0x27: { // Escape sequence
      break;
    }
  }
  return c;
}
