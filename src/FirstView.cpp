#include "FirstView.h"

#include <cctype>
#include <cstdio>

#include "KeyboardReader.h"

void FirstView::keyEmitted(int c) {
  if (c == '\0') {
    // continue;
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
}
