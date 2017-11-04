#include <iostream>
#include <string>
#include <cstring>
#include <stack>
#include <vector>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "../header/or.h"
#include "../header/exit.h"
#include "../header/and.h"
#include "../header/semicolon.h"

using namespace std;
using namespace boost;

// Prompt user and return input string
string prompt() {
  string input;

  cout << "$ ";
  getline(cin, input);
  return input;
}

// Using Boost's split() to parse string 
void parse(vector<string> &argVector) {
  string input = prompt();
  split(argVector, input, is_any_of(" "));
}

void executeCommand(char* args[]) {
  pid_t pid = fork();

  if (pid == 0) {
    if (execvp(args[0], args) == -1) {
      perror("exec");
    }
  }
  if (pid > 0) {
    if (wait(0) == -1) {
      perror("wait");
    }
  }
}

bool isExit(vector<string> argVector) {
  if (argVector.at(0) == "exit") { 
    return true;
  }
  return false;
}

int main() {
  while(1) {
    vector<string> argVector;
    parse(argVector);
    
    // Check if user inputs exit
    if (isExit(argVector)) { 
      Exit* userExit = new Exit(); 
      
      //call execute to exit terminal
      userExit->execute(); 
    }

    char* args[500];

    // Typecast string tokens into syscall-compatible char* array
    for (unsigned i = 0; i < argVector.size(); i++) {
      args[i] = (char*)argVector.at(i).c_str();
    }
    args[argVector.size()] = NULL;
    // Parse through commands to find comment character #
    for (unsigned int i = 0; i < argVector.size(); i++) { 
      if (strcmp(args[i], "#") == 0) { 
        int commentIndex = i; 
          for (unsigned j = commentIndex; j <= argVector.size(); j++) {
            // Starting at commentIndex, set # and elements after to null
            args[j] = NULL; 
          }
        break; 
      }
    }
    // Function for syscalls
    executeCommand(args);    
  }
  return 0;
}

