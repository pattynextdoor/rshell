#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "base.h"
#include <iostream>
#include <string>
#include <vector>

class Command : public Base {
  public:
    Command() : Base() {};
    Command(string input);
    bool execute();
};
#endif
