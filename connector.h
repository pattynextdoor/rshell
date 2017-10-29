#ifndef __CONNECTOR_H__
#define __CONNECTOR_H__

#include "base.h"

class Connector : public Base {
  protected:
    Base* left;
    Base* right;

  public:
    bool execute();
}
