#include <vector>
#include <map>
#include <string>

class Entry;

class SpimiReader
{
public:
  SpimiReader();
  ~SpimiReader();
  void parse(const std::vector<std::string>& docs);
  void parse(const std::string& buffer, const std::string& url);
  void finalize();

private:
  void _merge();
  void _exportBlock();
  bool _isOutOfSpace();  

  int _currentEntries;
  int _exportCntr;
  std::map< std::string, std::vector<Entry*> > _dics;
  std::vector<std::string> _outputBlocks;
};
