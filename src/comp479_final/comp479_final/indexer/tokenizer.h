#include <string>

namespace Tokenizer
{
  void strReplace(std::string& str, const std::string& oldStr, const std::string& newStr);
  const std::string tokenize(const std::string& token);
  const std::string tokenizeUrl(const std::string& url);
  bool isStopWord(const std::string& term);
  bool isValidWord(const std::string& word);
  size_t stringCount(const std::string& referenceString, const std::string& subString);
}
