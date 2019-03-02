#ifndef CLEARSCREEN_H_
#define CLEARSCREEN_H_

#include "IKeyboardListener.h"

class ClearScreen : public IKeyboardListener {
public:
  virtual ~ClearScreen() {}

  virtual void keyEmitted(int c);
};

#endif /* CLEARSCREEN_H_ */
