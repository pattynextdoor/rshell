#include "../header/cmd.h"
#include "../header/semicolon.h"
#include "../header/and.h"
#include "../header/or.h"

CMD::CMD() {}

<<<<<<< HEAD
bool CMD::fileExists(string& fileName) {
=======
bool fileExists(string& fileName) {
>>>>>>> 09b7b5b571d27509a20b96679c908d5902214f3c
  struct stat buf;

  return (stat(fileName.c_str(), &buf) == 0);
}

<<<<<<< HEAD
bool CMD::isDirectory(string& fileName) {
=======
bool isDirectory(string& fileName) {
>>>>>>> 09b7b5b571d27509a20b96679c908d5902214f3c
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

<<<<<<< HEAD
bool CMD::isFile(string& fileName) {
=======
bool isFile(string& fileName) {
>>>>>>> 09b7b5b571d27509a20b96679c908d5902214f3c
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

<<<<<<< HEAD
bool CMD::isLogicalOperator(std::vector<string> commands, unsigned index) {
=======
bool isLogicalOperator(std::vector<string> commands, unsigned index) {
>>>>>>> 09b7b5b571d27509a20b96679c908d5902214f3c
  if (index < 0 || index >= commands.size()) {
    return false;
  }
  if (commands.at(index) == "||" || commands.at(index) == "&&") {
    return true;
  }
  return false;
}

<<<<<<< HEAD
std::vector<string> CMD::findOperators(std::vector<string> commands) {
=======
std::vector<string> findOperators(std::vector<string> commands) {
>>>>>>> 09b7b5b571d27509a20b96679c908d5902214f3c
  std::vector<string> operators;

  for (unsigned i = 0; i < commands.size(); i++) {
    if (isLogicalOperator(commands, i)) {
      operators.push_back(commands.at(i));
    }
  }
  return operators;
}

bool CMD::execute() {
  std::vector<string> operators = findOperators(this->commands);
  

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
      CMD* left = new CMD();
      CMD* right = new CMD();
      left->commands.assign(commands.begin(), commands.begin() + i);
      right->commands.assign(commands.begin() + i + 1, commands.end());
      Semicolon* semi = new Semicolon(left, right);
      semi->execute();
      return true;
    }
        // And
    else if(commands.at(i) == "&&") {
      CMD* left = new CMD();
      CMD* right = new CMD();

      std::vector<string> lhs;
      std::vector<string> rhs;
      
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

      left->commands = lhs;
      right->commands = rhs;

      And* currAnd = new And(left, right);
      return currAnd->execute();
    }
    // Or
    else if(commands.at(i) == "||") {
      CMD* left = new CMD();
      CMD* right = new CMD();

      std::vector<string> lhs;
      stack<string> lhsStack;
      for(int j = i - 1; j >= 0; j--) {
        lhsStack.push(commands.at(j));
      }
      while(!lhsStack.empty()) {
        lhs.push_back(lhsStack.top());
        lhsStack.pop();
      }

      std::vector<string> rhs;
      for(unsigned int j = i + 1; j < commands.size(); j++) {
        cout << commands.at(j) << endl;
        rhs.push_back(commands.at(j));
      }

      left->commands = lhs;
      right->commands = rhs;

      Or* currOr = new Or(left, right);

      return currOr->execute();
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
      CMD* left = new CMD();
      std::vector<string> lhs;
      // File follows the > symbol
      string rhs = commands.at(i + 1);

      for (unsigned int j = 0; j != i; j++) {
        lhs.push_back(commands.at(j));
      }

      left->commands = lhs;

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

      left->execute();

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
      CMD* left = new CMD();
      std::vector<string> lhs;

      string rhs = commands.at(i + 1);

      for (unsigned int j = 0; j != i; j++) {
        lhs.push_back(commands.at(j));
      }

      left->commands = lhs;

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

      left->execute();

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
          CMD* cpyCMD = new CMD();
          std::vector<string> cpy;
          cpy.push_back(commands.at(0));
          cpy.push_back(entry);
          cpyCMD->commands = cpy;
          cpyCMD->execute();
        }
        return true;
      }
      return false;
    }
    else if (commands.at(i) == "|") {
      CMD* left = new CMD();
      CMD* right = new CMD();
      CMD* deleteCMD = new CMD();
      
      std::vector<string> lhs;
      std::vector<string> rhs;
      std::vector<string> deleteDummy;

      deleteDummy.push_back("rm");
      deleteDummy.push_back("dummyFile.txt");
      deleteCMD->commands = deleteDummy;

      for (unsigned int j = 0; j < i; j++) {
        lhs.push_back(commands.at(j));
      }

      lhs.push_back(">");
      lhs.push_back("dummyFile.txt");

      left->commands = lhs;
      left->execute();

      for (unsigned int j = i + 1; j < commands.size();  j++) {
        rhs.push_back(commands.at(j));
      }

      rhs.push_back("dummyFile.txt");

      right->commands = rhs;            
      right->execute();

      deleteCMD->execute();

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


