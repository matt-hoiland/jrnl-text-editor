#ifndef IKEYBOARDLISTENER_H_
#define IKEYBOARDLISTENER_H_

class IKeyboardListener {
public:
  virtual ~IKeyboardListener() {}
  virtual void keyEmitted(int key) = 0;
};

#endif /* IKEYBOARDLISTENER_H_ */
