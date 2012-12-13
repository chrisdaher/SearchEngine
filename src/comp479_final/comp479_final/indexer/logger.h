#include <string>

namespace LogLevel
{
  enum LogLevelEnum{
    LDEBUG,
    LCONDITIONAL,
    LALL
  };
}

namespace Logger
{

  void log(const std::string& componentName,
           const std::string& str, 
           LogLevel::LogLevelEnum level = LogLevel::LDEBUG);
           
  void setLogging(bool on);

}
