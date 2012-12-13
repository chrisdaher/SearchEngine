#include "queryManager.h"
#include "entry.h"
#include "tokenizer.h"
#include "metadataHelper.h"
#include "memoryManager.h"
#include "logger.h"
#include "rankManager.h"
#include "docidMapper.h"
#include <cluster/clusterer.h>
#include <cluster/document.h>
#include <cluster/centroid.h>

#include "assert.h"
#include "limits.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>

const static std::string componentName = "Query Manager";

namespace{

  void freeListOfEntries(std::vector< std::vector<Entry*> >& entries)
  {
    unsigned max = entries.size();
    for (unsigned i=0;i<max;i++){
      MemoryManager::freeEntryVector(entries[i]);
    }
    entries.clear();
  }

  const std::vector<int> charMatchesComparators(const char& c,
                                                const std::vector<char>& comparators)
  {
    const unsigned max = comparators.size();
    std::vector<int> res;
    for (unsigned i=0;i<max;i++){
      if (comparators[i] == c){
        res.push_back(i);
      }
    }
    return res;
  }
 
  void dumpEntries(const std::vector< std::vector<Entry*> >& res)
  {
    for (unsigned i=0;i<res.size();i++){
      std::cout << "I found:" << std::endl << "--------------------" << std::endl;
      const std::vector<Entry*> entries = res[i];
	  const unsigned gomax = (entries.size() <=10) ? entries.size() : 10;
      for (unsigned k=0;k<gomax;k++){
        std::stringstream ss;
        ss << entries[k]->getFrequency();

        std::string docFileName = entries[k]->getDocFilename();
        int posOfSlash = docFileName.find('/');
        posOfSlash++;
        
        docFileName = docFileName.substr(posOfSlash, docFileName.size() - posOfSlash);
        
        std::stringstream ssId;
        ssId << docFileName;
        int docId;
        ssId >> docId;

        std::string title = entries[k]->getDocFilename();
        //assert(DocIdMapper::getInstance()->getDocumentTitleFromId(docId, title));

        std::cout << (k+1) << ". " << title << " (" << ss.str() << ")" <<       std::endl;
      }                            
      std::cout << "----------------------------" << std::endl;
    }
  }
  
  void dumpEntry(const std::vector<Entry*>& res)
  {
    std::cout << "Final Results" << std::endl << "--------------------" << std::endl;
	const unsigned gomax = (res.size() <=10) ? res.size() : 10;
    for (unsigned k=0;k<gomax;k++){
      std::stringstream ss;
      ss << res[k]->getFrequency();

        std::string title = res[k]->getDocFilename();
        //assert(DocIdMapper::getInstance()->getDocumentTitleFromId(docId, title));

      std::cout << (k+1) << ". " << title << " (" << ss.str() << ")" <<       std::endl;
    }                            
    std::cout << "----------------------------" << std::endl;
  }
  
  void dumpEntry(const std::map<float, Entry*>& res)
  {
    std::cout << "Final Results" << std::endl << "--------------------" << std::endl;
    std::map<float, Entry*>::const_iterator it;
    int k = 0;
    std::map<float, Entry*>::const_iterator start = res.end();
    start--;
    std::map<float, Entry*>::const_iterator end = res.begin();
	int cntr = 0;
    for (it = start;it!=end;it--)
    {
	  if (cntr == 10) break;
	  cntr++;
      const Entry* temp = it->second;
      if (!temp) continue;
      
      std::string title = temp->getDocFilename();
      
      std::cout << (k+1) << ". " << title << std::endl;
      k++;
    }
    
    it = res.begin();
    const Entry* temp = it->second;
    if (!temp) return;

    std::string title = temp->getDocFilename();

    std::cout << (k+1) << ". " << title <<  std::endl;
    k++;
    
    std::cout << "----------------------------" << std::endl;
  }
  
  const std::vector<Entry*> unionEntries(const std::vector< std::vector<Entry*> >& res)
  {
	  std::vector<Entry*> toRet;
	  std::vector<Entry*>::const_iterator resultEntryIt;
	  std::vector<Entry*>::const_iterator returnEntryIt;
	  std::vector< std::vector<Entry*> >::const_iterator vecEntryIt;

	  for (vecEntryIt = res.begin(); vecEntryIt != res.end(); vecEntryIt++)
	  {
		  for (resultEntryIt = (*vecEntryIt).begin(); resultEntryIt != (*vecEntryIt).end(); resultEntryIt++)
		  {
			  bool found = false;
			  for (unsigned i=0;i<toRet.size();i++)
			  {
				  if (*toRet[i] == **resultEntryIt){
					  found = true;
					  break;
				  }
			  }
			  if (!found)
			  {
				  toRet.push_back(*resultEntryIt);
			  }
		  }
	  }
	  return toRet;
  }

  const std::vector<Entry*> intersectEntries( const std::vector< std::vector<Entry*> >& res)
  {
    if (res.size() == 0){
      return std::vector<Entry*>();
    }
    if (res.size() == 1){
      return res[0];
    }

    // base case
    if (res.size() == 2){
      std::vector<Entry*> toReturn;
      const int max1 = res[0].size();
      const int max2 = res[1].size();
      std::vector<Entry*>::const_iterator start1 = (max1 < max2) ? res[0].begin() : res[1].begin();
      std::vector<Entry*>::const_iterator end1 = (max1 < max2) ? res[0].end() : res[1].end();
      std::vector<Entry*>::const_iterator start2 = (max1 < max2) ? res[1].begin() : res[0].begin();
      std::vector<Entry*>::const_iterator end2 = (max1 < max2) ? res[1].end() : res[0].end();

      for (start1;start1<end1;start1++){
        for (start2;start2<end2;start2++){
          if (*(*start1) == *(*start2)){
            toReturn.push_back(*start1);
            break;
          }
        }
        start2 = (max1 < max2) ? res[1].begin() : res[0].begin();
      }
      return toReturn;
    }
    
    // > 2 so recursively pick the smallest 2 and continue
    
    // find the smallest size between all vectors
    unsigned currMin = INT_MAX;
    int currMinIndex = -1;
    const int max = res.size();
    for (int i=0;i<max;i++){
      if (res[i].size() < currMin){
        currMin = res[i].size();
        currMinIndex = i;
      }
    }
    if (currMinIndex == -1){
      assert( false == "We got a negative result when looking for smallest vector..." );
    }
        
    // find the second smallest one
    unsigned currMin2 = INT_MAX;
    int currMin2Index = -1;
    for (int i=0;i<max;i++){
      if ( res[i].size() <= currMin2 && i != currMinIndex){
        currMin2 = res[i].size();
        currMin2Index = i;
      }
    }
    
    if (currMin2Index == -1){
      // shouldnt happen...
      assert( false == "We got a negative result when looking for smallest vector..." );
    }
    
    if (currMin2Index == currMinIndex){
      // shouldnt happen...
      assert(false == "We found the same index for the smallest vectors...");
    }
    
    std::vector< std::vector<Entry*> > toRecurse;
    toRecurse.push_back(res[currMinIndex]);
    toRecurse.push_back(res[currMin2Index]);
    
    std::vector<Entry*> intersected = intersectEntries(toRecurse);
    // if this is empty, we return empty right away
    if (intersected.size() == 0) return std::vector<Entry*>();

    toRecurse.clear();
    for (int i=0;i<max;i++){
      if (i != currMinIndex && i != currMin2Index){
        toRecurse.push_back(res[i]);
      }
    }
    
    toRecurse.push_back(intersected);

    return intersectEntries(toRecurse);
  }

  Centroid findClosestCentroidToQuery(const std::string& query)
  {
	  if (!Clusterer::getInstance()->isLoaded()){
		  Clusterer::getInstance()->import();
	  }
	  
	  std::vector<std::string> whitespace;
	  MetadataHelper::splitLineByWhitespace(query, whitespace);
	  
	  Document queryDoc(query, "Query Document", whitespace.size());
	  if (Clusterer::getInstance()->isVectorSpaceLoaded()){
		Clusterer::getInstance()->generateDocumentVectorSpace(queryDoc);
	  }

	  return Clusterer::getInstance()->findClosestCentroid(queryDoc);
  }
}

QueryManager::QueryManager() {}

QueryManager::~QueryManager()
{
  int max = _finalResults.size();
  for (int i=0;i<max;i++)
  {
	  if (_finalResults[i]){
		  delete _finalResults[i];
	  }
  }
  //freeListOfEntries(_results);
}


const std::vector<Entry*> QueryManager::executeQuery(const std::string& query)
{
  freeListOfEntries(_results);
  Logger::log(componentName, "Fetching results for query: " + query, LogLevel::LALL);
  const std::string q = Tokenizer::tokenize(query);
  const std::string fileName = "out/spimi_final";
  std::vector<std::string> queries;
  MetadataHelper::splitLineByWhitespace(q, queries);
  const unsigned max = queries.size();
  std::vector<char> comparators;
  for (unsigned i=0;i<max;i++){
    comparators.push_back((queries[i])[0]);
  }
  
  std::string line;
  std::ifstream myfile (fileName.c_str());
  std::string word;
  
  std::map< std::string, std::vector<Document> > mapQueryToDocs;
  std::vector<Document> allDocs;

  while ( myfile.good() ){
    getline (myfile,line);
	if (line.empty()) continue;
    const std::vector<int> indexes = charMatchesComparators(line[0], comparators);
   
    if (indexes.size() != 0){
      unsigned maxIndex = indexes.size();
      for (unsigned i=0;i<maxIndex;i++){
        word = queries[indexes[i]];
        std::string token;
        std::vector<Entry*> entries;
        MetadataHelper::getMetadataFromLine(line, token, entries);
        if (token == word){
          _results.push_back(entries);

		  std::vector<Document> docs;
		  for (unsigned z=0;z<entries.size();z++)
		  {
			  Document doc("NO_CONTENT", entries[z]->getDocFilename(), entries[z]->getLength());
			  doc.assignTemporaryFrequency(entries[z]->getFrequency());
			  docs.push_back(doc);

			  if (std::find(allDocs.begin(), allDocs.end(), doc) == allDocs.end()){
				  allDocs.push_back(doc);
			  }
		  }

		  std::map< std::string, std::vector<Document> >::iterator it;
		  it = mapQueryToDocs.find(token);
		  if (it == mapQueryToDocs.end())
		  {
			  mapQueryToDocs.insert(std::pair< std::string, std::vector<Document> >(token, docs));
		  }
		  else
		  {
			  assert(false);
		  }
        }
      }
    }
  }
  dumpEntries(_results);
  //_finalResults = intersectEntries(_results);
  _finalResults = unionEntries(_results);
  
  
  const float N = (float)RankManager::getInstance()->getDocCount(); //::getTotalNumberOfDocuments();
  const float Lavg = (float)RankManager::getInstance()->getDocWordAverage(); //::getAverageCollectionSize();
  
  const float k1 = 1.4f;
  const float k3 = 1.3f;
  const float b = 0.75f;
  
  if (N == -1 || Lavg == -1) assert(false);
  
  std::vector<float> docWeight;
  std::map<float, Entry*> weightToResultMapper;
  
  for (unsigned i=0;i<_finalResults.size();i++)
  {
	Document temp(_finalResults[i]->getDocFilename());
	std::vector<Document>::iterator it;
	it = std::find(allDocs.begin(), allDocs.end(), temp);
	if (it == allDocs.end()) assert(false);

    const float Ld = (float)(*it).getTokenCount(); //(float)RankManager::calculateDocumentSize(finalResult[i]->getDocFilename());
    const float LdoLavg = (float)Ld/Lavg;
    docWeight.push_back(0.0f);
	int cntrr=0;
    for (unsigned k=0;k<queries.size();k++){
	  std::vector<Document> docs = mapQueryToDocs[queries[k]];
	  Document temp(_finalResults[i]->getDocFilename());
	  std::vector<Document>::iterator it;
	  it = std::find(docs.begin(), docs.end(), temp);
	  bool foundDoc = true;
	  if (it == docs.end()){ 
		  foundDoc = false;
		  //assert(false);
	  }

      const float df = (float)docs.size();
      const float tfd = (!foundDoc) ? 1.0f :(float)(*it).getTemporaryFrequency();
      
      const float NoLd = (df==0) ? 1 : log(N/df);
      const float n1 = (k1+1) * tfd;
      const float d1 = (k1 * ((1-b) + (b*LdoLavg))) + tfd;
      const float exp1 = n1/d1;
      
      float termWeight = NoLd * exp1;
      
      docWeight[i] += termWeight;
    }
    while (weightToResultMapper.find(docWeight[i]) != weightToResultMapper.end()){
      docWeight[i] += 0.0001f;
    }
    weightToResultMapper.insert(std::pair<float,Entry*>(docWeight[i], _finalResults[i]));
    std::stringstream ss;
    ss << docWeight[i];
	if (cntrr <= 10)
	{
		std::cout << "WEIGHT OF: " << _finalResults[i]->getDocFilename() << " = " << ss.str() << std::endl;
	}
	cntrr++;
  }
  //dumpEntry(finalResult);
  if (_finalResults.size() != 0){
    dumpEntry(weightToResultMapper);
	Centroid closest = findClosestCentroidToQuery(query);
	Logger::log("Closest centroid to the query is: ", closest.getName(), LogLevel::LALL);
  }
  else{
    std::cout << "No results" << std::endl;
  }

  return _finalResults;
}
