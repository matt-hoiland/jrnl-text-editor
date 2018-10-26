#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios orig_termios;

void die(const char *s) {
    perror(s);
    exit(1);
}

void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1) {
        die("tcsetattr");
    }
}

void enableRawMode() {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) {
        die("tcgetattr");
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
        die("tcsetattr");
    }
}

int main() {
    enableRawMode();

    while (true) {
        char c = '\0';
        if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) {
            die("read");
        }
        if (iscntrl(c)) {
            printf("0x%02X | %03d\r\n", c, c);
        } else {
            printf("0x%02X | %03d ('%c')\r\n", c, c, c);
        }
        if (c == 'q') { break; }
    }
    return 0;
}
