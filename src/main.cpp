#include <iostream>
#include <cstring>
#include <stack>
#include <queue>
#include <vector>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <fstream>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "../header/cmd.h"
#include "../header/exit.h"

// Prompt user and return input string
std::string prompt() {

  char hostname[HOST_NAME_MAX];
  char username[LOGIN_NAME_MAX];
  gethostname(hostname, HOST_NAME_MAX);
  getlogin_r(username, LOGIN_NAME_MAX);

  std::string host = std::string(hostname);
  std::string user = std::string(username);

  std::string input;

  char buf[500];
  getcwd(buf, 500);
  std::string cwd = buf;
  
  cout << user + "@" + host + " " + cwd + " $ ";
  std::getline(cin, input);

  return input;
}

// Using Boost's split() to parse string 
void parse(std::vector<std::string> &commands) {
  std::string input = prompt();
  boost::split(commands, input, boost::is_any_of(" "));
}


bool isExit(std::vector<std::string> commands) {
  if (commands.at(0) == "exit") {
    return true;
  }
  return false;
}

void removeComments(std::vector<std::string> &commands) {
  int commentIndex = commands.size();

  for (unsigned i = 0; i < commands.size(); i++) {
    if (commands.at(i) == "#" || commands.at(i).front() == '#') {
      commentIndex = i;
      break;
    }
  }

  std::vector<std::string>::const_iterator first = commands.begin();
  std::vector<std::string>::const_iterator last = commands.begin() + commentIndex;

  commands.assign(first, last);
}

int main() {
  while(1) {
    CMD* currCommand = new CMD(); 
    parse(currCommand->commands);
    // Check if user inputs exit
    if (isExit(currCommand->commands)) { 
      Exit* userExit = new Exit(); 
      // Call execute to exit terminal
      userExit->execute(); 
    }
    removeComments(currCommand->commands);
    currCommand->execute();
  }
  return 0;
}

