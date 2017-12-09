#include <iostream>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <vector>
#include <string.h>
#include <unistd.h>
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
}

bool executeCommand(vector<string> commands);

void semicolon(vector<string> commands, unsigned i) {
  if (commands.at(i).back() == ';') {
    commands.at(i) = commands.at(i).substr(0, commands.at(i).size() - 1);
  }
  vector<string> lhs;
  vector<string> rhs;

  if(i == 0) {
    lhs.push_back(commands.at(0));
  }
  else {
    for (unsigned int j = 0; j < i; j++) {
      lhs.push_back(commands.at(j));
    }
  }
  
  for (unsigned int j =  i + 1; j < commands.size(); j++) {
    rhs.push_back(commands.at(j));
  }
  executeCommand(lhs); 
  executeCommand(rhs);
}

bool isLogicalOperator(vector<string> commands, int index) {
  int  size = commands.size();
  if(index <=  -1 || index >= size) {
    return false;
  }
  if(commands.at(index) == "||" || commands.at(index) == "&&" || commands.at(index) == ";" || commands.at(index).back() == ';') {
    return true;
  }
  return false;
}

vector<string> findOperators(vector<string> commands) {
  vector<string> operators;

  for(unsigned int index = 0; index < commands.size(); index++) {
    if(isLogicalOperator(commands, index)) {
      operators.push_back(commands.at(index));
    }
  } 
  return operators;
}

bool executeCommand(vector<string> commands) {
  vector<string> operators = findOperators(commands);
  

  stack<string> depthStack;
  int beginCount = 0;
  int closeCount = 0;

  //check number of parenthesis before command execution
  for(unsigned int i = 0; i < commands.size(); i++) {
    if(commands.at(i).front() == '(') {
      ++beginCount;
    }
    if(commands.at(i).back() == ')') {
      ++closeCount;
    }
  }
  
  if(beginCount != closeCount) {
    cout << "Error: Parentheses don't match." << endl;
    return false;
  }

  for (unsigned int i = 0; i < commands.size(); i++) {
  
    if(!operators.empty()) {
      int operatorIndex;

      for (unsigned int j = 0; j < operators.size(); j++) {
        if(operators.at(j) == "||") {
          operatorIndex = j;
        } 
      }
      for (unsigned int j = 0; j < operators.size(); j++) {
        if(operators.at(j) == "&&") {
          operatorIndex = j;
        }
      }
      for (unsigned int j = 0; j < commands.size(); j++) {
        if (commands.at(j) == operators.at(operatorIndex)) {
          i = j;
        }
      }
    }
        // Precedence operators
    if(commands.at(i).front() == '(') {
      commands.at(i) = commands.at(i).substr(1);
      depthStack.push(commands.at(i));
      for(unsigned j = 0; j < commands.size(); j++) {
        if(commands.at(j).back() == ')') {
        commands.at(j) = commands.at(j).substr(0, commands.at(j).size() - 1);
          break;
        }
      }
    }
    // Semicolon
    if (commands.at(i) == ";" || commands.at(i).back() == ';') {
      semicolon(commands, i);
      return true;
    }
        // And
    else if(commands.at(i) == "&&") {
      vector<string> lhs;
      vector<string> rhs;
      
      stack<string> lhsStack;
      for(int j = i - 1;  j >= 0 ; j--) {
        lhsStack.push(commands.at(j));
      }
      while(!lhsStack.empty()) {
        lhs.push_back(lhsStack.top());
        lhsStack.pop();
      }
      for(unsigned int j = i + 1; j < commands.size(); j++) {
        rhs.push_back(commands.at(j));
      }
      if(executeCommand(lhs) && executeCommand(rhs)) {
        return true;
      }
    }
    // Or
    else if(commands.at(i) == "||") {
      vector<string> lhs;
      stack<string> lhsStack;
      for(int j = i - 1; j >= 0; j--) {
        lhsStack.push(commands.at(j));
      }
      while(!lhsStack.empty()) {
        lhs.push_back(lhsStack.top());
        lhsStack.pop();
      }
      if(executeCommand(lhs)) {
          return true ;
      }
      else {
        vector<string> rhs;
        for(unsigned int j = i + 1; j < commands.size(); j++) {
          cout << commands.at(j) << endl;
          rhs.push_back(commands.at(j));
        }
        if(executeCommand(rhs)) {
          return true;
        }
      }
      return false;
    }
    // Test
    else if ((commands.at(i) == "test" || ((commands.at(i) == "[") && (commands.at(i + 3) == "]")))) {
      if(commands.at(i + 1) == "-e") {
        if(fileExists(commands.at(i + 2))) {
          cout << "(True)" << endl;
          return true;
        }
        else {
          cout << "(False)" << endl;
          return false;
        }
      }
      else if(commands.at(i + 1) == "-d") {
        if(isDirectory(commands.at(i + 2))) {
          cout << "(True)" << endl;
          return true;
        }
        else {
          cout << "(False)" << endl;
          return false;
        }
      }
      else if(commands.at(i + 1) == "-f") {
        if(isFile(commands.at(i + 2))) {
          cout << "(True)" << endl;
          return true;
        }
        else {
          cout << "(False)" << endl;
          return false;
        }
      }
      else {
        if(fileExists(commands.at(i + 1))) {
          cout << "(True)" << endl;
          return true;
        }
        else {
          cout << "(False)" << endl;
          return false;
        }
      }
    }
    else if(commands.at(i) == ">") {
      // Populate lhs for execution
      vector<string> lhs;
      // File follows the > symbol
      string rhs = commands.at(i + 1);

      for (unsigned int j = 0; j != i; j++) {
        lhs.push_back(commands.at(j));
      }

      // Save file descriptors
      int saved_stdout;
      saved_stdout = dup(1);
      int fd = open((char*)rhs.c_str(), O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
      if (fd < 0) {
        perror("fd");
        return false;
      }
      if (dup2(fd, 1) < 0) {
        perror("dup2");
        return false;
      }
      executeCommand(lhs);

      if( dup2(saved_stdout, 1) < 0) {
        perror("dup2");
        return false;
      }
      // Cease redirection to file and bring it back to stdout
      close(saved_stdout);
      return true;      
    }
    else if(commands.at(i) == ">>") {
      // Populate lhs for execution
      vector<string> lhs;
      string rhs = commands.at(i + 1);

      for (unsigned int j = 0; j != i; j++) {
        lhs.push_back(commands.at(j));
      }

      // Save file descriptors
      int saved_stdout;
      saved_stdout = dup(1);
      // We use O_APPEND instead of O_TRUNCATE
      int fd = open((char*)rhs.c_str(), O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
      if (fd < 0) {
        perror("fd");
        return false;
      }
      if (dup2(fd, 1) < 0) {
        perror("dup2");
        return false;
      }
      executeCommand(lhs);

      if( dup2(saved_stdout, 1) < 0) {
        perror("dup2");
        return false;
      }
      // Cease redirection to file and bring it back to stdout
      close(saved_stdout);
      return true;
    }
    else if(commands.at(i) == "<") {
      ifstream myFile(commands.at(i + 1).c_str());
      string entry;
      if (myFile.is_open()) {
        while (getline(myFile, entry)) {
          vector<string> cpy;
          cpy.push_back(commands.at(0));
          cpy.push_back(entry);
          executeCommand(cpy);
        }
        return true;
      }
      return false;
    }
    else if (commands.at(i) == "|") {
      vector<string> lhs;
      vector<string> rhs;
      vector<string> deleteDummy;
      stack<string> lhsStack;
      vector<string> entireLeft;
      
      int p[2];
      pid_t pid = fork();
      int fd = 0;

      for(unsigned j = 0; j < commands.size(); j++) {
        pipe(p);

        if((pid = fork()) == -1) {
          perror("exec");
          return false;
        }
        else if (pid == 0) {
          dup2(fd, 0);
          if((commands.size() + 1) != NULL) {
            dup2(p[1], 1);
          }
          close(p[0]);
          execvp((commands
          perror("exec");
          return false;
        }
        else {
          if (wait(0) == -1) {
            perror("wait");
            close(p[1]);
            fd = p[0];
          }
        }
        return true;

      /*for(unsigned int j = i; j != 0; j--) {
        lhsStack.push(commands.at(j));
      }
      
      while(!lhsStack.empty()) {
        entireLeft.push_back(lhsStack.top());
        pipeStack.pop();
      }
      
      deleteDummy.push_back("rm");
      deleteDummy.push_back("dummyFile.txt");
      
      for (int j = 0; j < i; j++) {
        lhs.push_back(commands.at(j));
      }

      lhs.push_back(">");
      lhs.push_back("dummyFile.txt");
      executeCommand(lhs);
      
      for (int j = i + 1; j < commands.size();  j++) {
        rhs.push_back(commands.at(j));
      }*/

      rhs.push_back("dummyFile.txt");
      executeCommand(rhs);
      executeCommand(deleteDummy);

      return true;

    }
  }
  // Populate character array with vector contents 
  char* args[500];

  for (unsigned i = 0; i < commands.size(); i++) {
    args[i] = (char*)commands.at(i).c_str();
  }
  
  // Last element set to null
  args[commands.size()] = 0;

  // Execute raw command
  pid_t pid = fork();

  if (pid == 0) {
    if (execvp(args[0], args) == -1) {
      perror("exec");
      // Command did not execute
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
  
  if (stat(fileName.c_str(), &path) == 0) {
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

  if (stat(fileName.c_str(), &filePath) == 0) {
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
      if (currCommand->commands.at(i) == "#" || currCommand->commands.at(i).front() == '#') { 
        unsigned commentIndex = i; 
        if (currCommand->commands.at(commentIndex).front() == '#') {
          currCommand->commands.at(commentIndex) = currCommand->commands.at(commentIndex).substr(1);
        }
        for (unsigned j = currCommand->commands.size() - 1; j >= commentIndex; j--) {
          // Starting at commentIndex, set # and elements after to null
          currCommand->commands.pop_back();
        }
        break; 
      }
    }
    // Function for syscalls
    executeCommand(currCommand->commands);   
  }
  return 0;
}

