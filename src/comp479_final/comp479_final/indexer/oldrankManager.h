#include <string>
#include <vector>

namespace RankManagerold
{
  int calculateAverageDocumentSize(const std::vector<std::string>& docs, bool forceRecalculate = false);
  int calculateDocumentSize(std::string doc);
  int getAverageCollectionSize();
  void setTotalNumberOfDocuments(int total);
  int getTotalNumberOfDocuments();
  int calculateTermFrequency(const std::string& term, const std::string& doc);

  void addBufferToDocumentSize(const std::string& buffer);

  void exportInfo();
  bool import();
}
