#include <map>
#include <string>

class DocIdMapper
{
 public:
  
  static DocIdMapper* getInstance();
  bool getDocumentTitleFromId(int id, std::string& title);
  bool insertIdForTitle(int id, const std::string& title);
  bool isIdUsed(int id);
  void exportMapper();
  bool import();

 private:

  DocIdMapper();
  std::map<int, std::string> _mapper;
};
