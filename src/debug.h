#ifndef DEBUG_H_
#define DEBUG_H_

#define DIE(s) die(s, __LINE__)

void die(const char *s, int line);

#endif /* DEBUG_H_ */
