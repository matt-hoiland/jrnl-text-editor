#ifndef KEYBOARDREADER_H_
#define KEYBOARDREADER_H_

#define CTRL_KEY(k) ((k) & 0x1f)

enum KeyCode {

};

class KeyboardReader {
public:
    void run();

private:
    int getKeyPress();
};

#endif /* KEYBOARDREADER_H_ */
