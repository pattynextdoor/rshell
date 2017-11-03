#include "../header/exit.h"
#include <iostream>
#include <stdlib.h>

Exit::Exit() {}

bool Exit::execute() {
  cout << "Exiting Rshell" << endl;
  exit(0);
  return true;
}
