#ifndef FIRSTVIEW_H_
#define FIRSTVIEW_H_

#include "IKeyboardListener.h"

class FirstView : public IKeyboardListener {
public:
  virtual ~FirstView() {}

  virtual void keyEmitted(int key);
};

#endif /* FIRSTVIEW_H_ */
