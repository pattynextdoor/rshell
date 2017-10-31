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
#include "../header/cmd.h"

using namespace std;
using namespace boost;

string prompt() {

  string input;

  cout << "$ ";
  getline(cin, input);
  return input;
}

int main() {
  while(1) {
    vector<string> argVector;
    char* args[50];
    string input = prompt();
    split(argVector, input, is_any_of(" "));

    for(unsigned i = 0; i < argVector.size(); i++) {
      string buffer = argVector.at(i);
      args[i] = (char*)buffer.c_str();

      if(i == argVector.size() - 1) {
        args[i + 1] = NULL;
        
        for(unsigned j = 0; j < argVector.size(); j++) {
          cout << args[i] << endl;
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
    }
  

        
/*
    unsigned argsPos = 0;
    string input = prompt();
    char_separator<char> sep(" ");
    tokenizer<char_separator<char> > tok(input, sep);
    
    for(tokenizer< char_separator<char> > ::iterator iter= tok.begin(); iter != tok.end(); ++iter){
      string buffer  = *iter;
      args[argsPos] = (char*)buffer.c_str();
      cout << args[argsPos] << endl;
      argsPos++;
    }
    cout << args[0] << endl;
    //Last element must be NULL for execvp
    if(execvp(args[0], args) == -1) {
      perror("exec");
    }
*/
  }
}

