#include <vector>

class Entry;

namespace MemoryManager{
  int getMaxMemoryEntries();
  void setMaxMemoryEntries(int mem);
  void freeEntryVector(std::vector<Entry*>& vec);
}
