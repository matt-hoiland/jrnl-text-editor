#ifndef KEYBOARDREADER_H_
#define KEYBOARDREADER_H_

#define CTRL_KEY(k) ((k) & 0x1f)

enum KeyCode {
  ARROW_UP = 0x100,
  ARROW_DOWN,
  ARROW_RIGHT,
  ARROW_LEFT,
};

class KeyboardReader {
public:
  void run();

private:
  int getByte();
  int getKeyPress();
};

#endif /* KEYBOARDREADER_H_ */
