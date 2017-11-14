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
#include "../header/cmd.h"
#include "../header/command.h"
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
void parse(vector<Base*> &commands) {
  string input = prompt();
  vector<string> argVector;
  split(argVector, input, is_any_of(" "));

  for(unsigned i = 0; i < argVector.size(); i++) {
    if(argVector.at(i) == "&&") {
      And* newAnd = new And();
      commands.push_back(newAnd);
    }
    else if (argVector.at(i) == "||") {
      Or* newOr = new Or();
      commands.push_back(newOr);
    }
    else if (argVector.at(i) == ";") {
      Semicolon* newSemi = new Semicolon();
      commands.push_back(newSemi);
    }
    else {
      Command* newCommand = new Command(argVector.at(i));
      commands.push_back(newCommand);
    }
  }
}

void executeCommand(char* args[], unsigned size) {
  for (unsigned i = 0; i < size; i++) {
    cout << "Reached for loop. i value is: ";
    cout << i << endl;
    if (strcmp(args[i], ";") == 0) {
      char* leftArgs[250];
      char* rightArgs[250];
      //execute args[] before i
      for (unsigned j = 0; j < i; j++) {
        cout << "Populating left. j value is: ";
        cout << j << endl;
        leftArgs[j] = args[j];
      }
      //execute args[] after i
      for (unsigned j =  i + 1; j < size; j++) {
        cout << "Populating right. j value is: ";
        cout << j << endl;
        rightArgs[j] = args[j];
      }
      executeCommand(leftArgs, i); 
      executeCommand(rightArgs, size - (i + 1));
    }
  }

  cout << "uh lmoa" << endl;
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

bool isExit(vector<Base*> commands) {
  if (commands.at(0)->value == "exit") {
    return true;
  }
  return false;
}

int main() {
  while(1) {
    CMD* currCommand = new CMD(); 
    parse(currCommand->commands);
    // Check if user inputs exit
    if (isExit(currCommand->commands)) { 
      Exit* userExit = new Exit(); 
      //call execute to exit terminal
      userExit->execute(); 
    }

    char* args[500];

    // Typecast string tokens into syscall-compatible char* array
    for (unsigned i = 0; i < currCommand->commands.size(); i++) {
      args[i] = (char*)currCommand->commands.at(i)->value.c_str();
    }

    args[currCommand->commands.size()] = NULL;
    // Parse through commands to find comment character #
    for (unsigned int i = 0; i < currCommand->commands.size(); i++) { 
      if (strcmp(args[i], "#") == 0) { 
        int commentIndex = i; 
          for (unsigned j = commentIndex; j <= currCommand->commands.size(); j++) {
            // Starting at commentIndex, set # and elements after to null
            args[j] = NULL; 
          }
        break; 
      }
    }
    // Function for syscalls
    executeCommand(args, currCommand->commands.size());    
  }
  return 0;
}
