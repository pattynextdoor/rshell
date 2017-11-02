#ifndef __CONNECTOR_H__
#define __CONNECTOR_H__

#include "base.h"

class Connector : public Base {
  protected:
    Base* left;
    Base* right;

  public:
    Connector() {left = 0, right = 0} ;
    Connector(Base* left, Base* right);

    bool execute();
};
#endif
