#include "memoryManager.h"
#include "entry.h"

namespace MemoryManager{

  static int _maxMemoryEntries = 10000;

  int getMaxMemoryEntries(){
    return _maxMemoryEntries;
  }
  
  void freeEntryVector(std::vector<Entry*>& vec)
  {
    const unsigned max = vec.size();
    for (unsigned i=0;i<max;i++){
      if (vec[i] != 0x0){
        delete vec[i];  
        vec[i] = 0x0;
      }
    }
    vec.clear();
  }
  
  void setMaxMemoryEntries(int mem){
    _maxMemoryEntries = mem;
  }
}
