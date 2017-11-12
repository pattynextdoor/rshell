#ifndef __CMD_H__
#define __CMD_H__

#include "base.h"
#include <iostream>
#include <string>
#include <vector>

class CMD : public Base {
  public:
    vector<Base*> commands;
    CMD();
    bool execute();
};
#endif
