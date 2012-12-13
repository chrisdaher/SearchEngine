#include "rankManager.h"
#include "metadataHelper.h"
#include "logger.h"
#include "tokenizer.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>

namespace
{
  static int savedAverage = -1;
  static int totalDocs = -1;
  const static std::string exportFileName = "out/rankInfo";
  const static std::string componentName = "RankManager";
}


namespace RankManagerold
{
  void setTotalNumberOfDocuments(int total)
  {
    totalDocs = total;
  }
  
  int getTotalNumberOfDocuments()
  {
    return totalDocs;
  }
  
  int calculateAverageDocumentSize(const std::vector<std::string>& docs, bool forceRecalculate)
  {
    if (savedAverage != -1 && !forceRecalculate) return savedAverage;
    
    int cntr = 0;
    const unsigned max = docs.size();
    
    for (unsigned i=0;i<max;i++){
      std::ifstream infile (docs[i].c_str());
      std::string line;
      
      if (infile.is_open()){
        while ( infile.good() )
        {
          getline (infile,line);
          std::vector<std::string> terms;
          MetadataHelper::splitLineByWhitespace(line, terms);
          for (unsigned k=0;k<terms.size();k++){
            if (!terms[k].empty()){
              cntr ++;
            }
          }
        }
      }
      else{
        assert(false);
      }
    }
    
    if (forceRecalculate) return cntr/docs.size();
    
    savedAverage = cntr/docs.size();
    
    return savedAverage;
  }
  int calculateDocumentSize(std::string doc)
  {
    std::vector<std::string> temp;
    temp.push_back(doc);
    
    return calculateAverageDocumentSize(temp, true);
  }
  
  int getAverageCollectionSize()
  {
    if (savedAverage == -1) assert(false);
    
    return savedAverage;
  }
  
  int calculateTermFrequency(const std::string& term, const std::string& doc)
  {
    std::ifstream infile (doc.c_str());
    std::string line;
    
    int cntr = 0;
    
    if (infile.is_open()){
      while ( infile.good() )
      {
        getline (infile,line);
        std::vector<std::string> terms;
        MetadataHelper::splitLineByWhitespace(line, terms);
        for (unsigned k=0;k<terms.size();k++){
          const std::string toComp = Tokenizer::tokenize(terms[k]);
          if (toComp == term){
            cntr ++;
          }
        }
      }
    }
    else{
      assert(false);
    }
    
    return cntr;
  }
  
  void exportInfo()
  {
    std::ofstream outfile;
    
    outfile.open(exportFileName.c_str(),  std::ios::out);

    Logger::log(componentName, "Attempting to export rank info...", LogLevel::LALL);
    
    if (outfile.is_open())
    {
      std::stringstream ss;
      
      if (savedAverage == -1 || totalDocs == -1)
      {
        Logger::log(componentName, "Error: couldn't export rank info because indexing was not ran.");
        return;
      }
      
      ss << savedAverage << std::endl;
      ss << totalDocs << std::endl;
      outfile << ss.str().c_str();
    }
    else{
      Logger::log(componentName, "Error: Couldn't open file to write rank info (" + exportFileName + ")",
                  LogLevel::LALL);
      assert(false);
      
    }
    Logger::log(componentName, "Exported successfully to " + exportFileName, LogLevel::LALL);
  }
  
  bool import()
  {
    std::ifstream infile (exportFileName.c_str());
    
    Logger::log(componentName, "Attempting to import rank info from: " + exportFileName, LogLevel::LALL);
    
    if (infile.is_open()){
      std::string line;
      
      // first line is savedAverage
      // second line is totalDocs
      getline (infile,line);
      std::stringstream ss1(line);
        
      ss1 >> savedAverage;
      
      getline (infile, line);
      std::stringstream ss2(line);
      
      ss2 >> totalDocs;
      
    }
    else{
      return false;
    }
    
    Logger::log(componentName, "Successfully imported rank info.", LogLevel::LALL);
    
    return true;
  }

  void addBufferToDocumentSize(const std::string& buffer)
  {

  }
  
}