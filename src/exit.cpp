#include "../header/exit.h"
#include <iostream>

Exit::Exit() {}

bool Exit::execute() {
  exit(0);
}
