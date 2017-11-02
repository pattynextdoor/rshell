#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

using namespace std;
using namespace boost;

string prompt() {

  string input;

  cout << "$ ";
  getline(cin, input);
  return input;
}

int main() {
  string input;
  while(input != "exit") {
    if(input == "exit") {
      Exit* userExit = new Exit();
      userExit.execute();
    }
  
    vector<string> argVector;
    CMD* userCMD = new CMD();
    input = prompt();

    split(argVector, input, is_any_of(" "));

    char* args[argVector.size()];

    for(unsigned i = 0; i < argVector.size(); i++) {
      args[i] = (char*)argVector.at(i).c_str();
    }

    args[argVector.size()] = NULL;

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
  
    for(unsigned int j = 0; j < argVector.size(); j++) {
      if (argVector.at(j) == ||) {
        Or* newOr = new Or()
        userCMD.commands.push_back(newOr);
      }
      if (argVector.at(j) == &&) {
        And newAnd = new And();
        userCMD.commands.push_back(newAnd);
      }
      else
        //INCOMPLETE
     }
    
        
 }
}

