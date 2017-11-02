#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "base.h"
#include <iostream>
#include <string>
#include <vector>

class CMD : public Base {
  protected:
    vector<Base*> commands;
	
  public:
    CMD();
    bool execute();
};
#endif
