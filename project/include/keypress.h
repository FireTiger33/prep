#ifndef PROJECT_INCLUDE_KEYPRESS_H_
#define PROJECT_INCLUDE_KEYPRESS_H_

#include <termios.h>
#include <sys/types.h>
#include <unistd.h>


void shadow_keypress();
void reset_keypress();

#endif  // PROJECT_INCLUDE_KEYPRESS_H_
