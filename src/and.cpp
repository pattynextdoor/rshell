#include "../header/and.h"

And::And(Base* left, Base* right) : Connector(left, right) {}

bool And::execute() {
  if(left->execute() && right->execute()) {
    return true;
  }
  return false;
} 
