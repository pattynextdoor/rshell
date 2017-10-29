#include "semicolon.h"

Semicolon::Semicolon(Base* left, Base* right) : Connector(left, right) {}

bool Semicolon::execute() {
  left->execute();
  if(right->execute()){
    return true;
  }
  return false;
}
