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
    
    int exitIndex = 0; 
    int commentIndex = 0;  
  while(1) {
    vector<string> argVector;
    string input = prompt();
    
    split(argVector, input, is_any_of(" "));

    char* args[500];

    for(unsigned i = 0; i < argVector.size(); i++) {
      args[i] = (char*)argVector.at(i).c_str();
    }

    for (unsigned int i = 0; i < argVector.size(); i++) {
      if(strcmp(args[i], "exit") == 0) {
        exitIndex = i;
      }
    }
    //CHECK IF USER INPUTS EXIT ONLY and no other commands
    if((strcmp(args[0], "exit") == 0)) { //if exit is found
      Exit* userExit = new Exit(); //make new object to call execute
      userExit->execute(); //call execute to exit terminal
    }
    else { //if exit is not the first command line
      args[argVector.size()] = NULL;

      for(unsigned int i = 0; i < argVector.size(); i++) { //Parse through commands to find #
        if(strcmp(args[i], "#") == 0) { //Check
          commentIndex = i; //find the index where # is located
            for( unsigned j = commentIndex; j <= argVector.size(); j++) {
            //starting at commentIndex, set # and elements after to null
              args[j] = NULL; //set all elements after # to null
            }
          break; //break out of the loop to continue
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

