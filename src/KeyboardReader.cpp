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
    } else if (c >= 0x80) {
      printf("0x%02X | ", c);
      switch (c) {
        case ARROW_UP:    printf("%s\r\n", "ARROW_UP"); break;
        case ARROW_DOWN:  printf("%s\r\n", "ARROW_DOWN"); break;
        case ARROW_RIGHT: printf("%s\r\n", "ARROW_RIGHT"); break;
        case ARROW_LEFT:  printf("%s\r\n", "ARROW_LEFT"); break;
      }
    } else {
      printf("0x%02X | %03d ('%c')\r\n", c, c, c);
    }
    if (c == CTRL_KEY('q')) { break; }
  }
}

int KeyboardReader::getByte() {
  int c = '\0';
  if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) {
    DIE("KeyboardReader::getKeyPress() -> read()");
  }
  return c;
}

int KeyboardReader::getKeyPress() {
  int c = getByte();
  switch (c) {
    case 0x1B: { // Escape sequence
      switch (getByte()) {
        case '[': {
          switch (getByte()) {
            case 'A': return ARROW_UP;
            case 'B': return ARROW_DOWN;
            case 'C': return ARROW_RIGHT;
            case 'D': return ARROW_LEFT;
          }
          break;
        }
      }
      break;
    }
  }
  return c;
}
