#include "ClearScreen.h"

#include <unistd.h>

void ClearScreen::keyEmitted(int c) {
  write(STDOUT_FILENO, "\x1b[2J", 4); // Clears the screen
}
