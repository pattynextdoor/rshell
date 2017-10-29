#ifndef __BASE_H__
#define __BASE_H__

#include <unistd.h>
#include <iostream>
#include <string>

class Base {
  public: 
    virtual bool execute() = 0;
};
#endif
