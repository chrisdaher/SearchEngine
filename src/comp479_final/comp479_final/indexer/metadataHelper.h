#include <string>
#include <vector>

class Entry;

namespace MetadataHelper
{
  void getMetadataFromLine(const std::string& line,
                           std::string& token,
                           std::vector<Entry*>& entries);
                           
  void splitLineByWhitespace(const std::string& line,
                             std::vector<std::string>& tokens);

  void splitLineByDelim(const std::string& line, 
						  const char& delim,
						  std::vector<std::string>& vector);
}
