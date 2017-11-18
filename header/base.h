#ifndef __BASE_H__
#define __BASE_H__

#include <unistd.h>
#include <iostream>
#include <string>

using namespace std;

class Base {
  public:
    string value;
    virtual bool execute() = 0;
};
#endif
