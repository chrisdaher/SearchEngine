#include "logger.h"
#include <iostream>

namespace Logger
{
  static bool isLogging = false;

  void setLogging(bool on)
  {
    isLogging = on;
  }

  void log(const std::string& componentName,
           const std::string& str, 
           LogLevel::LogLevelEnum level)
  {
    switch(level){
      case LogLevel::LDEBUG:
        #ifndef DEBUG
          return;
        #endif
        break;
      case LogLevel::LCONDITIONAL:
        if (!isLogging) return;
    }
    
    std::cout << componentName << ": " << str << std::endl;
  }         
}
