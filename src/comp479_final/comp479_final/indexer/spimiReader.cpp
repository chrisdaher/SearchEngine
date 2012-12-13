#include "spimiReader.h"
#include "entry.h"
#include "memoryManager.h"
#include "logger.h"
#include "metadataHelper.h"
#include "tokenizer.h"
#include "rankManager.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <algorithm>

const std::string outputFilename = "out/spimi_final";

struct AddInfo{
public:
  AddInfo() :
    tokenAdded(false),
    nbEntriesAdded(0) {}
  
  bool tokenAdded;
  int nbEntriesAdded;
};

namespace AddStatus{
  enum AddStatusEnum{
    SNEW,
    SAPPEND,
    SNO_CHANGE
  };
}

namespace{

  const static std::string componentName = "SpimiReader";

	void deleteIndexOutput()
	{
		if (!std::remove(outputFilename.c_str())){
			Logger::log(componentName, "Deleted existing index", LogLevel::LCONDITIONAL);
		}
	}

  void freeEntryMap(std::map< std::string, std::vector<Entry*> >& map)
  {
    std::map< std::string, std::vector<Entry*> >::iterator itr;
    for(itr = map.begin(); itr != map.end(); ++itr){
      MemoryManager::freeEntryVector((*itr).second);
    }
    map.clear();
  } 

  Entry* findEntryInVector(const std::vector<Entry*>& vectors, const Entry& entry)
  {
    for (unsigned i=0;i<vectors.size();i++){
      if (*vectors[i] == entry) return vectors[i];
    }
    return 0;
  }

  Entry* findEntryInMap(const std::map< std::string, std::vector<Entry*> >& map, const std::string& term, const std::string docName)
  {
	std::map< std::string, std::vector<Entry*> >::const_iterator it;
	it = map.find(term);
	if (it == map.end()) return 0x0;
	Entry temp(docName, 0);
	return findEntryInVector(it->second, temp);
  }
    
  const std::vector< std::pair<int, int> > fillInverterPairs()
  {
    //
    // this will generate pairs ranging that go:
    // start->end 
    // example: a->f
    // ascii:
    // a-z: 97-122
    // A-Z: 65-90
    // 0-9: 48-57
    //
    
    std::vector< std::pair<int, int> > vect;
    const int INTERVAL = 3;
    int end;
    
    // Starting with lower alpha
    for (unsigned i=97;i<123;i+=(INTERVAL+1)){
      if (i>=123) break;
      end = ((i+INTERVAL) >= 123) ? 122 : (i+INTERVAL);
      std::pair<int, int> pair(i, end);
      vect.push_back(pair);
    }
    
    /*
    // upper alpha
    for (unsigned i=65;i<91;i+=(INTERVAL+1)){
      if (i>=91) break;
      end = ((i+INTERVAL) >= 91) ? 90 : (i+INTERVAL);
      std::pair<int, int> pair(i, end);
      vect.push_back(pair);
    }
    */
    
    /*
    // numerical
    for (unsigned i=48;i<58;i+=(INTERVAL+1)){
      if (i>=58) break;
      end = ((i+INTERVAL) >= 58) ? 57 : (i+INTERVAL);
      std::pair<int, int> pair(i, end);
      vect.push_back(pair);
    }
    */
    return vect;
  }
   
  AddStatus::AddStatusEnum addEntryToDict(std::map< std::string, std::vector<Entry*> >& dict,
                                          const std::string& token,
                                          const std::string& fileName, 
										  int length)
  {
    std::map< std::string, std::vector<Entry*> >::iterator it;
    it = dict.find(token);
    if (it == dict.end()){
      // not found
      Entry* ent = new Entry(fileName, length);
 	    std::vector<Entry*> entries;
      entries.push_back(ent);
      dict.insert(std::pair< std::string, std::vector<Entry*> >(token, entries));
      return AddStatus::SNEW;
    }
 	  else{
      std::vector<Entry*> entries = it->second;
      Entry temp(fileName, length);
      Entry* found = findEntryInVector(it->second, temp);
      if (!found){
	      Entry* ent = new Entry(fileName, length);
	      it->second.push_back(ent);
        return AddStatus::SAPPEND;
	    }
      else{
       found->incrementFrequency();
	    }
    }  
    return AddStatus::SNO_CHANGE;
  }
  
  void incrementEntryFrequency(std::map< std::string, std::vector<Entry*> >& dict,
                               const std::string& token,
                               const std::string& fileName,
                               int freq)
  {
    std::map< std::string, std::vector<Entry*> >::iterator it;
    it = dict.find(token);
    if (it == dict.end()) return;
    
    std::vector<Entry*> entries = it->second;
    Entry temp(fileName, 0);
    Entry* found = findEntryInVector(it->second, temp);
    if (!found) return;
    
    
    found->incrementFrequency(freq);
  }
  
  AddInfo mergeEntriesToDict(std::map< std::string, std::vector<Entry*> >& dict,
                                              const std::string& token,
                                              const std::vector<Entry*>& entries)
  {
    AddInfo toRet;
    const unsigned max = entries.size();
    for (unsigned i=0;i<max;i++){
      Entry* temp = entries[i];
      const unsigned maxFreq = temp->getFrequency();
      for (unsigned k=0;k<maxFreq;k++){
        AddStatus::AddStatusEnum status = addEntryToDict(dict, token, temp->getDocFilename(), temp->getLength());
        if (k==0){
          if (status == AddStatus::SNEW){
            toRet.tokenAdded = true;
            toRet.nbEntriesAdded++;
          }
          else if(status == AddStatus::SAPPEND){
            toRet.nbEntriesAdded++;
          }
          break;
        } 
      }
      incrementEntryFrequency(dict, token, temp->getDocFilename(), temp->getFrequency() - 1);
    }

    return toRet;
  }
      
  bool exportDict(const std::map< std::string, std::vector<Entry*> >& dict,
                  const std::string& fileName,
                  bool append = false)
  {
    Logger::log(componentName, "Attemping to export to: "  + fileName);

    std::ofstream myfile;
    
    myfile.open(fileName.c_str(), (append) ? (std::ios::out | std::ios::app) : std::ios::out);
    if (myfile.is_open())
    {
      std::stringstream outLine;
      std::map< std::string, std::vector<Entry*> >::const_iterator it;
      for ( it=dict.begin() ; it != dict.end(); it++ ){
        outLine.str(std::string());
        outLine << (*it).first << "+";
        for (unsigned i=0;i<(*it).second.size();i++){
          outLine << (*it).second[i]->getDocFilename() << 
            "*" << (*it).second[i]->getFrequency() << "%" << (*it).second[i]->getLength();
          if ((i+1) != (*it).second.size()){
            outLine << ",";
          }
        }
        outLine << std::endl;
        myfile << outLine.str().c_str();
      }
      myfile.close();
      Logger::log(componentName, "Exported block to: " + fileName, LogLevel::LALL);
      return true;
    }
    else{
      Logger::log(componentName, "Error: Couldn't open file to write for export block (" + fileName + ")",
                  LogLevel::LALL);   
      assert(false);
    }
    return false;
  }
}

SpimiReader::SpimiReader()
{
  deleteIndexOutput();
  _currentEntries = 0;
  _exportCntr = 1;
}

SpimiReader::~SpimiReader()
{
}

void SpimiReader::_merge()
{
  Logger::log(componentName, "Merge export blocks process begin", LogLevel::LCONDITIONAL); 
 
  const unsigned maxBlocks = _outputBlocks.size();
  const std::vector< std::pair<int, int> > pairs = fillInverterPairs();
  const unsigned maxPairs = pairs.size();

  int nbTerms = 0;
  int nbPostings = 0;
  
  for (unsigned i=0;i<maxPairs;i++){
    std::stringstream strStream;
    strStream << "(" << pairs[i].first << "," << pairs[i].second << ")";
  
    Logger::log(componentName, "Merging interval: " + strStream.str(), LogLevel::LCONDITIONAL);

	std::stringstream percentage;
	percentage << (((float)i+1.0f)/(float)maxPairs)*100.0f << "%" << std::endl;
	Logger::log(componentName, percentage.str(), LogLevel::LALL);

    const unsigned start = pairs[i].first;
    const unsigned end = pairs[i].second + 1;
    for (unsigned k=start;k<end;k++){
      std::map< std::string, std::vector<Entry*> > tempDict;
      const char temp = k +'\0';    
      std::ostringstream oss;
      oss << temp;
      Logger::log(componentName, "Merging with: " + oss.str(), LogLevel::LCONDITIONAL);
      const char comparator = oss.str()[0];

      for (unsigned z=0;z<maxBlocks;z++){        
        std::string line;
        std::ifstream myfile (_outputBlocks[z].c_str());
        if (myfile.is_open()){
          Logger::log(componentName, "Reading file: " + _outputBlocks[z], LogLevel::LDEBUG);

          while ( myfile.good() )
          {
            getline (myfile,line);
			if (line.empty()) continue;
			if (line[0] > comparator) continue;
            if (line[0] == comparator){
              std::string token;
              std::vector<Entry*> entries;
              MetadataHelper::getMetadataFromLine(line, token, entries);

			  if (entries.size() == 0) continue;

              std::stringstream size;
              size << entries.size();

              Logger::log(componentName, "FOUND TOKEN: " + token + " WITH: " + size.str(), LogLevel::LDEBUG);       
              AddInfo info = mergeEntriesToDict(tempDict, token, entries);
              if (info.tokenAdded) nbTerms++;
              nbPostings += info.nbEntriesAdded;
            }
          }
        }
      }
      exportDict(tempDict, outputFilename, true);
      freeEntryMap(tempDict);
    }
  }
  std::stringstream tempss;
  tempss << "Terms = " << nbTerms << " | Postings = " << nbPostings;
  Logger::log(componentName, tempss.str(), LogLevel::LCONDITIONAL);

  RankManager::getInstance(false)->setTotalTokenCount(nbTerms);
}


bool SpimiReader::_isOutOfSpace()
{
  return (_currentEntries >= MemoryManager::getMaxMemoryEntries());
}

void SpimiReader::_exportBlock()
{
  std::stringstream ss;
  ss << "out/tmp_spimi_" << _exportCntr++ << ".txt";

  if (exportDict(_dics, ss.str())){      
     _outputBlocks.push_back(ss.str());
     freeEntryMap(_dics);
     _currentEntries = 0;
  }  
}

void SpimiReader::finalize()
{
	_exportBlock();
	_merge();
	RankManager::getInstance(false)->finalize();
}

void SpimiReader::parse(const std::string& buffer,
						const std::string& url)
{
	if (_isOutOfSpace()){
		_exportBlock();
	} 

	RankManager::getInstance(false)->incrementDocCntr();

	std::vector<std::string> tokens;
	MetadataHelper::splitLineByWhitespace(buffer, tokens);
	const unsigned max = tokens.size();

	RankManager::getInstance(false)->incrementWordCount(max);
	int tokenCntr = 0;

    for (unsigned k=0;k<max;k++){
		std::string tokenized = Tokenizer::tokenize(tokens[k]);

		if (tokenized.empty()) continue;
		if (!Tokenizer::isValidWord(tokenized)) continue;
		if (Tokenizer::isStopWord(tokenized)) continue;

		tokenCntr++;

        if (addEntryToDict(_dics, tokenized, url, max) != AddStatus::SNO_CHANGE)
		{
			_currentEntries++;
		}
	}
}

