#ifndef _EXIT_H__
#define _EXIT_H__

#include "cmd.h"
#include <iostream>
#include <string>

class Exit : public CMD {
  public:
    bool execute();

};
#endif
