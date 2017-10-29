#ifndef __AND_H__
#define __AND_H__

#include "connector.h"

class And : public Connector {
  public:
    And();
    And(Base* left, Base* right);

    bool execute();
};
#endif
