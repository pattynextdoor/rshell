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

string prompt() {

  string input;

  cout << "$ ";
  getline(cin, input);
  return input;
}

int main() {
  /*string input = prompt();
  //stack<Base*> cmdStack;
  vector<string> argVector;

  split(argVector, input, is_any_of(" "));

  char* args[argVector.size()];

  for(unsigned i = 0; i < argVector.size(); i++) {
    args[i] = (char*)argVector.at(i).c_str();
  }
  
  unsigned int exitIndex = 0; 
  for(unsigned int j = 0; j <argVector.size(); j++) {
    if(strcmp(args[j], "exit") == 0) {
      exitIndex = j;
      cout << exitIndex << endl;
    }
  }
  for( unsigned int j = 0; j < argVector.size(); j++) {
    if (cmdStack.size() != 3) {
      CMD* userCMD = new CMD();
      userCMD = 
      cout << args[j];
      cmdStack.push(args[j]);
    }
  }*/
  int exitIndex = 1;
  int commentIndex = 0;  
  while(exitIndex != 0) {
    vector<string> argVector;
    string input = prompt();
    
    split(argVector, input, is_any_of(" "));

    char* args[argVector.size()];

    for(unsigned i = 0; i < argVector.size(); i++) {
      args[i] = (char*)argVector.at(i).c_str();
    }

    args[argVector.size()] = NULL;
    for(unsigned int i = 0; i < argVector.size(); i++) {
      if(strcmp(args[i], "#") == 0) {
        commentIndex = i;
          for( unsigned j = commentIndex; j < argVector.size(); j++) {
            args[j] = NULL;
          }
      }
    }

    pid_t pid = fork();

    if(pid == 0) {
      if(execvp(args[0], args) == -1) {
        perror("exec");
      }
    }
    if(pid > 0) {
      if(wait(0) == -1) {
        perror("wait");
      }
    }
    
    /*for(unsigned int j = 0; j < argVector.size(); j++) {
      if(strcmp(args[j], "exit") == 0) {
        exitIndex = j;
      }
    }*/

    /*for(unsigned int j = 0; j < argVector.size(); j++) {
      if (argVector.at(j) == "||") {
        Or* newOr = new Or();
        userCMD->commands.push_back(newOr);
      }
      if (argVector.at(j) == "&&") {
        And* newAnd = new And();
        userCMD->commands.push_back(newAnd);
      }
        //INCOMPLETE
    }*/
        
 }
  return 0;
}

