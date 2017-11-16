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
#include <sys/stat.h>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "../header/cmd.h"
#include "../header/exit.h"
//#include "../header/or.h"
//#include "../header/and.h"
//#include "../header/semicolon.h"

using namespace std;
using namespace boost;

//Function instantiations for checking existence of a path
bool fileExists(string& fileName);
bool isDirectory(string& fileName);
bool isFile(string& fileName);

// Prompt user and return input string
string prompt() {
  string input;

  cout << "$ ";
  getline(cin, input);
  return input;
}

// Using Boost's split() to parse string 
void parse(vector<string> &commands) {
  string input = prompt();
  split(commands, input, is_any_of(" "));

  for(unsigned i = 0; i < commands.size(); i++) {
    if(commands.at(i) == "&&") {
      //TODO: Implement And
    }
    else if (commands.at(i) == "||") {
      //TODO: Implement Or
    }
    else if (commands.at(i) == ";") {
      //TODO: Implement Semicolon
    }
  }
}

bool executeCommand(vector<string> commands) {
  for (unsigned i = 0; i < commands.size(); i++) {
    if (commands.at(i) == ";" || commands.at(i).back() == ';') {
      if(commands.at(i).back() == ';') {
        commands.at(i) = commands.at(i).substr(0, commands.at(i).size() - 2);
      }
      vector<string> lhs;
      vector<string> rhs;
      for (unsigned j = 0; j < i; j++) {
        lhs.push_back(commands.at(j));
      }
      for (unsigned j =  i + 1; j < commands.size(); j++) {
        rhs.push_back(commands.at(j));
      }
      executeCommand(lhs); 
      executeCommand(rhs);
      return true;
    }
    else if(commands.at(i) == "||") {
      vector<string> lhs;
      for(unsigned j = 0; j < i; ++j) {
        lhs.push_back(commands.at(j));
      }
      if(executeCommand(lhs)) {
          return true;
      }
      else {
        vector<string> rhs;
        for(unsigned j = i + 1; j < commands.size(); j++) {
          rhs.push_back(commands.at(j));
        }
        if(executeCommand(rhs)) {
          return true;
        }
      }
    }
    else if(commands.at(i) == "test" || ((commands.at(i) == "[") && (commands.at(i + 3) == "]")) ) {
      if(commands.at(i + 1) == "-e") {
        if(fileExists(commands.at(i + 2)) == true) {
          cout << "(True)";
        }
        else {
          cout << "(False)" << endl;
        }
      }
      else if(commands.at(i + 1) == "-d") {
        if(isDirectory(commands.at(i + 2)) == true) {
           cout << "(True)" << endl;
        }
        else {
          cout << "(False)" << endl;
        }
      }
      else if(commands.at(i + 1) == "-f") {
        if(isFile(commands.at(i + 2)) == true) {
          cout << "(True)" << endl;
        }
        else {
          cout << "(False)" << endl;
        }
      }
      else {
        if(fileExists(commands.at(i + 1)) == true) {
          cout << "(True)" << endl;
        }
        else {
          cout << "(False)" << endl;
        }
      }
    }

  }

  char* args[500];

  for (unsigned i = 0; i < commands.size(); i++) {
    args[i] = (char*)commands.at(i).c_str();
  }

  args[commands.size()] = 0;

  pid_t pid = fork();

  if (pid == 0) {
    if (execvp(args[0], args) == -1) {
      perror("exec");
      return false;
    }
  }
  if (pid > 0) {
    if (wait(0) == -1) {
      perror("wait");
    }
  }

  return true;
}

//---------------------------------------------------
//Functions for path/file/directory existance
//Passes in filename and returns true if found, false if not

bool fileExists(string& fileName) {
  struct stat buf;

  return (stat(fileName.c_str(), &buf) == 0);
}

bool isDirectory(string& fileName) {
  struct stat path;
  
  if( stat(fileName.c_str(), &path) == 0) {
    if(path.st_mode & S_IFDIR) {
      return true;
    }
    else {
      return false;
    }
  }
  
  return false;
}

bool isFile(string& fileName) {
  struct stat filePath;

  if( stat(fileName.c_str(), &filePath) == 0) {
    if(filePath.st_mode & S_IFREG) {
      return true;
    }
    else {
      return false;
    }
  }
  
  return false;
}
//---------------------------------------------------

bool isExit(vector<string> commands) {
  if (commands.at(0) == "exit") {
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
      // Call execute to exit terminal
      userExit->execute(); 
    }
    // Parse through commands to find comment character #
    for (unsigned int i = 0; i < currCommand->commands.size(); i++) { 
      if (currCommand->commands.at(i) == "#") { 
        int commentIndex = i; 
          for (unsigned j = commentIndex; j < currCommand->commands.size(); j++) {
            // Starting at commentIndex, set # and elements after to null
            currCommand->commands.at(j) = ""; 
          }
        break; 
      }
    }
    // Function for syscalls
    executeCommand(currCommand->commands);    
  }
  return 0;
}
