#include "or.h"

Or::Or(Base* left, Base* right) : Connector(left, right) {}

bool Or::execute() {
  if(left->execute() || right->execute()) {
    return true;
  }
  return false;
}
