#include "rankManager.h"
#include "metadataHelper.h"
#include "logger.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>

namespace
{  
  const static std::string exportFileName = "out/rankInfo";
  const static std::string componentName = "RankManager";
  static RankManager* instance = 0x0;
  static bool loaded = false;
}

RankManager* RankManager::getInstance(bool load)
{
	if (!instance){
		instance = new RankManager(!loaded && load);
	}
	return instance;
}
void RankManager::_import()
{
	std::ifstream infile (exportFileName.c_str());
    
    Logger::log(componentName, "Attempting to import rank info from: " + exportFileName, LogLevel::LALL);
    
    if (infile.is_open()){
      std::string line;
      
      // first line is savedAverage
      // second line is totalDocs
      getline (infile,line);
      std::stringstream ss1(line);
      int avg;
      ss1 >> avg;
      
      getline (infile, line);
      std::stringstream ss2(line);
      
      ss2 >> _currDocCntr;

	  getline(infile, line);
	  std::stringstream ss3(line);

	  ss3 >> _totalToken;

	  _currWordCntr = avg*_currDocCntr;

	  Logger::log(componentName, "Successfully imported rank info.", LogLevel::LALL);
    }
    else{
      Logger::log(componentName, "Could not load RankManager data", LogLevel::LALL);
    }

}

int RankManager::getTotalTokenCount() const
{
	return _totalToken;
}

int RankManager::getAverageWordCount() const
{
	return _currWordCntr/_currDocCntr;
}

void RankManager::incrementWordCount(int cntr)
{
	_currWordCntr+=cntr;
}

int RankManager::getDocCount() const
{
	return _currDocCntr;
}

void RankManager::setTotalTokenCount(int count)
{
	_totalToken = count;
}

RankManager::RankManager(bool load)
{
	_currDocCntr = 0;
	_currWordCntr = 0;
	_totalToken = 0;

	if (!load) return;

	_import();
}

void RankManager::finalize() const
{ 
	std::ofstream outfile;
    
    outfile.open(exportFileName.c_str(),  std::ios::out);

    Logger::log(componentName, "Attempting to export rank info...", LogLevel::LALL);
    
    if (outfile.is_open())
    {
      std::stringstream ss;
      
      ss << getDocWordAverage() << std::endl;
      ss << _currDocCntr << std::endl;
	  ss << _totalToken << std::endl;
      outfile << ss.str().c_str();
    }
    else{
      Logger::log(componentName, "Error: Couldn't open file to write rank info (" + exportFileName + ")",
                  LogLevel::LALL);
      assert(false);
      
    }
    Logger::log(componentName, "Exported successfully to " + exportFileName, LogLevel::LALL);
}

void RankManager::incrementDocCntr()
{
	_currDocCntr++;
}

int RankManager::getCurrentWordCount() const
{
	return _currDocCntr;
}

int RankManager::getDocWordAverage() const
{
	return _currWordCntr/_currDocCntr;
}

int RankManager::calculateDocLength(const std::string& buffer) const
{
	return buffer.size();

	std::vector<std::string> terms;
    MetadataHelper::splitLineByWhitespace(buffer, terms);

	int cntr = 0;

	for (unsigned k=0;k<terms.size();k++){
		if (!terms[k].empty()){
			cntr ++;
		}
	}
	return cntr;
}

void RankManager::calculateAndAddBuffer(const std::string& buffer)
{
	_currWordCntr += calculateDocLength(buffer);
}