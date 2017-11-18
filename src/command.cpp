#include "../header/command.h"

Command::Command(string input) {
  value = input;
}

bool Command::execute() {
  return true; //Dummy return
}


