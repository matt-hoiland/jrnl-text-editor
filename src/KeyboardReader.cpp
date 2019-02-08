#include "KeyboardReader.h"

#include <cerrno>
#include <cctype>
#include <cstdio>
#include <unistd.h>

#include "debug.h"

void KeyboardReader::run() {
  while (true) {
    int c = getKeyPress();
    for (const auto& listener : listeners) {
      listener->keyEmitted(c);
    }
    if (c == CTRL_KEY('q')) { break; }
  }
}

void KeyboardReader::registerListener(IKeyboardListener* listener) {
  listeners.push_back(listener);
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
