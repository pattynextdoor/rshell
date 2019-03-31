#ifndef __PROMPT_H__
#define __PROMPT_H__

#include <iostream>
#include <cstdlib>

class Prompt {
  private:
    std::string message;

  public:
    void setMessage(std::string newMessage); 
    void printMessage();
}

#endif