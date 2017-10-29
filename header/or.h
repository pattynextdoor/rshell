#ifndef __OR_H__
#define __OR_H__

#include "connector.h"

class Or : public Connector {
  public:
    Or();
    Or(Base* left, Base* right);
    
    bool execute();
};
#endif
