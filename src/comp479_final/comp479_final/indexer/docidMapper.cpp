#include "docidMapper.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
#include "logger.h"
#include <vector>

namespace{
  static DocIdMapper* _pInstance = 0x0;
  const static std::string exportFileName = "out/docidMapper";
  const static std::string componentName = "DocIdMapper";
  const char delimiter = '%';
}

DocIdMapper::DocIdMapper()
{  
  
}

DocIdMapper* DocIdMapper::getInstance()
{
  if (!_pInstance){
    _pInstance = new DocIdMapper();
  }

  return _pInstance;
}

bool DocIdMapper::import()
{
  std::ifstream infile (exportFileName.c_str());
  
  Logger::log(componentName, "Attempting to import id mapper from: " + exportFileName, LogLevel::LALL);
  
  if (infile.is_open()){
    std::string line;
    _mapper.clear();
    
    while ( infile.good() )
    {
      getline (infile,line);
      
      std::vector<std::string> vec;
      std::stringstream ss(line);
      std::string item;
      
      if (line.empty()) continue;
      
      while(std::getline(ss, item, delimiter)) {
        if (!item.empty()) vec.push_back(item);
      }
      
      // vec[0] = (int) id
      // vec[1] = (string) title;
      int id;
      std::stringstream idStr(vec[0]);
      idStr >> id;
      
      insertIdForTitle(id, vec[1]);
    }
    
  }
  else{
    return false;
  }
  
  Logger::log(componentName, "Successfully imported id map.", LogLevel::LALL);
  
  return true;
}

void DocIdMapper::exportMapper()
{
  std::ofstream outfile;
  
  outfile.open(exportFileName.c_str(),  std::ios::out);
  std::map< int, std::string >::iterator it = _mapper.begin();
  
  Logger::log(componentName, "Attempting to export id mapper...", LogLevel::LALL);
  
  if (outfile.is_open())
  {
    for (it = _mapper.begin(); it != _mapper.end();it++){
      std::stringstream outLine;
      
      outLine << it->first;
      outLine << delimiter;
      outLine << it->second;
      outLine << std::endl;
      
      outfile << outLine.str().c_str();
    }
    
  }
  else{
    Logger::log(componentName, "Error: Couldn't open file to write mapper blocks (" + exportFileName + ")",
                LogLevel::LALL);
    assert(false);
    
  }
  Logger::log(componentName, "Exported successfully to " + exportFileName, LogLevel::LALL);
}

bool DocIdMapper::isIdUsed(int id)
{
  std::map<int, std::string>::iterator it;

  it = _mapper.find(id);

  return (it != _mapper.end());
}

bool DocIdMapper::getDocumentTitleFromId(int id, std::string& title)
{
  std::map<int, std::string>::iterator it;

  it = _mapper.find(id);

  if (it == _mapper.end()) return false;


  title = it->second;
  return true;
}

bool DocIdMapper::insertIdForTitle(int id, const std::string& title)
{
  if (isIdUsed(id)) return false;

  _mapper.insert(std::pair<int, std::string>(id, title));
  return true;
}
