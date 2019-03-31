#include "../header/exit.h"
#include <iostream>
#include <stdlib.h>

bool Exit::execute() {
  cout << "Exiting Rshell" << endl;
  exit(0);
  return true;
}
