#include "metadataHelper.h"
#include "entry.h"
#include "logger.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <algorithm>

namespace MetadataHelper
{
  const static std::string componentName = "Metadata Helper";

  void splitLineByWhitespace(const std::string& line,
	                           std::vector<std::string>& tokens)
  {
    tokens.clear();
    std::string buf; 
    std::stringstream ss(line);

    while (ss >> buf)
        tokens.push_back(buf);
  }

  void getMetadataFromLine(const std::string& line,
                           std::string& token,
                           std::vector<Entry*>& entries)
  {
    std::stringstream ss(line);
    std::string item;
    char delim = '+';
    std::vector<std::string> vec;
    while(std::getline(ss, item, delim)) {
        if (!item.empty()) vec.push_back(item);
    }
    
    if (vec.size() > 2){
      Logger::log(componentName, "Invalid vector size when reading metadata (" + line + ")", LogLevel::LALL);
	  return;
      assert(false);
    }

    // should have a vector with:
    // vec[0] = token
    // vec[1] = list of entries seperated by ',' and frequency '*'
    token = vec[0];
    
    ss.str(vec[1]);
    item = "";
    delim = ',';
    std::vector<std::string> entriesVec;
    int start = 0, end = 0;
    while ((end = ss.str().find(delim, start)) != std::string::npos) {
      entriesVec.push_back(ss.str().substr(start, end - start));
      start = end + 1;
    }
    entriesVec.push_back(ss.str().substr(start));
    
    const unsigned max = entriesVec.size();
    for (unsigned i=0;i<max;i++){
      ss.str(entriesVec[i]);
      item = "";
      delim = '*';
      std::vector<std::string> entryVec;
      start = end = 0;
      while ((end = ss.str().find(delim, start)) != std::string::npos) {
        entryVec.push_back(ss.str().substr(start, end - start));
        start = end + 1;
      }

	  entryVec.push_back(ss.str().substr(start));

	  std::stringstream freqLength(entryVec[entryVec.size() -1]);

	  delim = '%';
	  start = end = 0;
	  while ((end = freqLength.str().find(delim, start)) != std::string::npos) {
		entryVec[entryVec.size() - 1] = freqLength.str().substr(start, end - start);
        start = end + 1;
      }

      entryVec.push_back(freqLength.str().substr(start));
      
      // should have a vector with:
      // entryVec[0] = filename
      // entryVec[1] = frequency
	  // entryVec[2] = length
      if (entryVec.size() != 3){
        Logger::log(componentName, "Invalid vector size when reading metadata (" + entriesVec[i] + ")", LogLevel::LALL);
		return;
        assert(false);
      }
      
      int frequency;
	  int length;
      std::stringstream strStream(entryVec[1]);
      strStream >> frequency;

	  std::stringstream strLength(entryVec[2]);
	  strLength >> length;

      Entry* entry = new Entry(entryVec[0], length);
      entry->setFrequency(frequency);
      entries.push_back(entry);
    }
  }

  void splitLineByDelim(const std::string& line, 
     				    const char& delim,
						std::vector<std::string>& vector)
  {
    std::stringstream buffer(line);
	std::string item;
	while(std::getline(buffer, item, delim)) {
	  if (!item.empty()) vector.push_back(item);
	}
  }

}
