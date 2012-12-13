#include <string>
#include <vector>

class Entry;

class QueryManager
{
public:
  QueryManager();
  ~QueryManager();
  const std::vector<Entry*> executeQuery(const std::string& query);

private:
  std::vector< std::vector<Entry*> > _results;
  std::vector< Entry* > _finalResults;
};
