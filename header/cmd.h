#ifndef __CMD_H__
#define __CMD_H__

#include "base.h"
#include "../header/cmd.h"
#include "../header/semicolon.h"
#include "../header/and.h"
#include "../header/or.h"

#include <iostream>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <vector>
#include <map>
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

class CMD : public Base {
  private:
    bool isLogicalOperator(std::vector<string>, unsigned); 
    std::vector<string> findOperators(const std::vector<string>);
    bool fileExists(string&);
    bool isDirectory(string&);
    bool isFile(string&);
    std::pair<int, int> checkParentheses(const std::vector<string>);
  public:
    std::vector<string> commands;
    bool execute();
};
#endif
