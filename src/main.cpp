#include <cstdlib>
#include <termios.h>
#include <unistd.h>

#include "debug.h"
#include "KeyboardReader.h"
#include "FirstView.h"
#include "ClearScreen.h"

struct termios orig_termios;

void disableRawMode() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1) {
    DIE("tcsetattr");
  }
}

void enableRawMode() {
  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) {
    DIE("tcgetattr");
  }
  atexit(disableRawMode);

  struct termios raw = orig_termios;
  // BRKINT:  disable break interrupts
  // ICRNL :  fix ctrl-M
  // INPCK :  disable parity checking
  // ISTRIP:  disable 8th bit stripping
  // IXON  :  disable ctrl-S and ctrl-Q
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  // OPOST :  disable output processing (\n -/-> \r\n)
  raw.c_oflag &= ~(OPOST);
  // CS8   :  set character size to 8 bits/byte
  raw.c_cflag |= (CS8);
  // ECHO  :  disable echoing
  // ICANON:  disable canonical mode (read byte by byte)
  // IEXTEN:  disable ctrl-V
  // ISIG  :  disable interrupts (ctrl-C and ctrl-Z)
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;

  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
    DIE("tcsetattr");
  }
}

int main() {
  enableRawMode();

  FirstView fv;
  ClearScreen cs;
  KeyboardReader kr;
  kr.registerListener(&cs);
  kr.run();
  return 0;
}
