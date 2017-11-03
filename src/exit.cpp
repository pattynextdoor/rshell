#include "../header/exit.h"
#include <iostream>
#include <stdlib.h>

Exit::Exit() {}

bool Exit::execute() {
  exit(0);
  return true;
}
