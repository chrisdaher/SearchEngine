#include "clusterer.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <fstream>

#include <indexer/tokenizer.h>
#include <indexer/entry.h>
#include <indexer/metadataHelper.h>
#include <indexer/memoryManager.h>
#include <cluster/metrics.h>
#include <cluster/centroid.h>
#include <indexer/logger.h>
#include <indexer/rankManager.h>

namespace
{
	const static std::string exportFileName = "out/clusterInfo";
	const static std::string componentName = "Clusterer";
	const static std::string dataCentroidStart = "<CENTROID_START>";
	const static std::string dataCentroidEnd = "<CENTROID_END>";
	const static std::string dataCentroidName = "	CENTROID_NAME=";
	const static std::string dataCentroidUrl = "	CENTROID_URL=";
	const static std::string dataCentroidVectorSpaceStart = "<CENTROID_VECTOR_SPACE_START>";
	const static std::string dataCentroidVectorSpaceEnd = "<CENTROID_VECTOR_SPACE_END>";

	Clusterer* _pInstance = 0x0;
	
	void generateKUniqueNumbers(int max, int k, std::vector<int>& uniques)
	{
		srand ( (unsigned int)time(NULL) );

		int num = rand() % max;
		for (int i=0;i<k;i++){
			while (std::find(uniques.begin(), uniques.end(), num) != uniques.end())
			{
				num = rand() % max;
			}
			uniques.push_back(num);
		}
	}

	float findTFD(int docLength, int freq)
	{
		if (freq == -1 || freq == 0){
			assert(false);
		}

		return (float)((float)freq/(float)docLength);
	}

	float findIDF(int docsFrequency, int totalDocs)
	{
		/*
		std::vector<Document>::const_iterator docIt;
		const unsigned max = docs.size();
		int cntr = 0;
		for (docIt = docs.begin(); docIt!=docs.end(); docIt++)
		{
			if ((*docIt).getContent().find(term) != std::string::npos)
			{
				cntr ++;
			}
		}
		*/

		return (float)(log10((float)totalDocs/(float)docsFrequency));
	}

	void initCluster(std::vector<Centroid>& centroids, int count)
	{
		centroids.clear();
		Centroid c;
		for (int i=0;i<count;i++)
		{
			centroids.push_back(c);
		}
	}

	void calculateMeanPoints(std::vector<Centroid>& initial)
	{
		const int max = initial.size();
		for (int i=0;i<max;i++)
		{
			if (initial[i].getDocs().size() > 0)
			{
				const int max2 = initial[i].getDocs()[0].getVectorSpace().size();
				for (int j=0;j<max2;j++)
				{
					float total = 0;
					const unsigned max3 = initial[i].getDocs().size();
					for (unsigned k = 0; k<max3;k++)
					{
						total+=initial[i].getDocs()[k].getVectorSpace()[j];
					}
					initial[i].getDocs()[0].getVectorSpace()[j] = total/initial[i].getDocs().size();
				}
			}
		}
	}

	int closestCentroidToDoc(const std::vector<Centroid>& centroids, const Document& doc)
	{
		std::vector<float> similarityMeasure;
		const int max = centroids.size();

		for (int i=0;i<max;i++)
		{
			if (centroids[i].getDocs().size() != 0){
				similarityMeasure.push_back(ClusterMetrics::calculateCosine(centroids[i].getDocs()[0].getVectorSpace(), doc.getVectorSpace()));
			}
		}
		
		int index = 0;
		float maxValue = similarityMeasure[0];
		for (int i=0;i<max;i++)
		{
			if (similarityMeasure[i] > maxValue)
			{
				maxValue = similarityMeasure[i];
				index = i;
			}
		}
		return index;
	}

	static int globalCounter = 0;
	bool checkStopCriteria(const std::vector<Centroid>& previous, const std::vector<Centroid>& current)
	{
		globalCounter++;
		const int max = 11000;
		if (globalCounter > max) return true;

		std::vector<int> changeIndex;
		const unsigned currentMax = current.size();
		for (unsigned i=0;i<currentMax;i++)
		{
			changeIndex.push_back(0);
		}

		int index = 0;
		do
		{
			int count = 0;
			if (current[index].getDocs().size() == 0 && 
				previous[index].getDocs().size() == 0)
			{
				index++;
			}
			else if (current[index].getDocs().size() != 0 &&
					 previous[index].getDocs().size() != 0)			
			{
				for (unsigned j=0;j<current[index].getDocs()[0].getVectorSpace().size();j++)
				{
					if (current[index].getDocs()[0].getVectorSpace()[j] == previous[index].getDocs()[0].getVectorSpace()[j]){
						count++;
					}
				}

				if (count == current[index].getDocs()[0].getVectorSpace().size()){
					changeIndex[index] = 0;
				}
				else{
					changeIndex[index] = 1;
				}
				index++;
			}
			else{
				index++;
				continue;
			}
		}while(index < (int)current.size());

		for (unsigned i=0;i<changeIndex.size();i++)
		{
			if (changeIndex[i] != 0) return false;
		}
		return true;
	}
}

float Clusterer::calculateTFIDF(int docLength, int termFreq, int docFreq, int totalDocs) const
{
	return findTFD(docLength, termFreq) * findIDF(docFreq, totalDocs);
	/*
	std::pair< std::string, Document > pair(term, doc);
	std::map< std::pair< std::string, Document >, int>::const_iterator it;

	it = _termFrequencyMapper.find(pair);

	if (it == _termFrequencyMapper.end()){
		return 0.0f;
	}

	int freq = it->second;

	_termFrequencyMapper.erase(pair);
	*/
}

Clusterer::Clusterer() : _imported(false), _loadedVectorSpace(false) {}

Clusterer* Clusterer::getInstance()
{
	if (!_pInstance){
		_pInstance = new Clusterer();
	}
	return _pInstance;
}

void Clusterer::generateDocumentVectorSpace(Document& doc) const
{
	const std::string indexFilename = "out/spimi_final";
	const int totTerms = RankManager::getInstance()->getTotalTokenCount();
	const int docCount = RankManager::getInstance()->getDocCount();

	std::vector<std::string> queryTerms;
	MetadataHelper::splitLineByWhitespace(doc.getContent(), queryTerms);
	if (queryTerms.size() == 0) return;
	
	std::string line;
	std::ifstream myfile (indexFilename.c_str());
	
	while(myfile.good())
	{
		getline(myfile, line);
		if (line.empty()) continue;

		std::string token;
		std::vector<Entry*> entries;
		MetadataHelper::getMetadataFromLine(line, token, entries);
		float tfidf = 0.0f;
		
		for (unsigned i=0;i<queryTerms.size();i++){
			if (queryTerms[i] == token){
				tfidf = calculateTFIDF(doc.getTokenCount(), Tokenizer::stringCount(doc.getContent(), token), entries.size(), docCount);
				break;
			}
		}
		doc.getVectorSpace().push_back(tfidf);
	}
}

#ifdef OLD_IMPLEMENTATION
bool Clusterer::_prepareVectorSpace()
{
	const unsigned maxTerms = _distinctTerms.size();
	const unsigned maxDocs = _docs.size();

	std::vector<Document>::iterator docIt;
	std::set<std::string>::iterator termIt;

	std::stringstream ss;
	ss << "We have: " << maxTerms << " distinct terms, with: " << _docs.size() << " documents";
	std::cout << ss.str() << std::endl;

	// calculate idf for each doc
	int docCntr = 0;
	for (docIt = _docs.begin(); docIt!=_docs.end(); docIt++)
	{
		docCntr++;
		std::stringstream ss2;
		ss2 << "Cluster preparing docs..." << (float)(((float)docCntr/(float)maxDocs)*100.0f) << "%" << std::endl;
		Logger::log(componentName, ss2.str(), LogLevel::LALL);

		int cntr = 0;
		(*docIt).reserveVectorSpaceSize(maxTerms);
		for (termIt = _distinctTerms.begin(); termIt!=_distinctTerms.end();termIt++)
		{
			const float tfidf = calculateTFIDF((*docIt), (*termIt));
			/*
			std::stringstream ss3;
			ss3 << "TFIDF for: " << *termIt << " = " << tfidf;
			std::cout << ss3.str() << std::endl;
			*/

			(*docIt).getVectorSpace().push_back(tfidf);
			cntr++;
			if (cntr % 20 == 0){
				std::stringstream percentage;
				percentage << ((float)cntr/(float)maxTerms) * 100.0f << "%...";
				std::cout << percentage.str();
			}
		}
		std::cout << std::endl;

	}
}
#else
bool Clusterer::_prepareVectorSpace()
{
	const std::string indexFilename = "out/spimi_final";

	if (RankManager::getInstance()->getDocCount() == 0)
	{
		Logger::log(componentName, "No docs to prepare...", LogLevel::LALL);
		return false;
	}

	_docs.clear();
	const int docCount = RankManager::getInstance()->getDocCount();
	_docs.reserve(docCount);

	const int totTerms = RankManager::getInstance()->getTotalTokenCount();

	std::string line;
	std::ifstream myfile (indexFilename.c_str());
	int termCntr = 0;

	Logger::log(componentName, "Preparing document vector space...", LogLevel::LALL);

	while(myfile.good())
	{
		getline(myfile, line);
		if (line.empty()) continue;
		std::string token;
		std::vector<Entry*> entries;
        MetadataHelper::getMetadataFromLine(line, token, entries);

		const int max = entries.size();
		std::vector<Document>::iterator it;
		std::vector< int > usedIndex;

		for (int i=0;i<max;i++)
		{
			Document doc("NO_CONTENT", entries[i]->getDocFilename(), entries[i]->getLength());
			it = std::find(_docs.begin(), _docs.end(), doc);

			const float tfidf = calculateTFIDF(entries[i]->getLength(), entries[i]->getFrequency(), max, docCount);
			if (it != _docs.end())
			{
				it->getVectorSpace().push_back(tfidf);
				usedIndex.push_back(it - _docs.begin());
			}
			else
			{
				_docs.push_back(doc);
				for (int k=0;k<termCntr;k++)
				{
					_docs[_docs.size()-1].getVectorSpace().push_back(0.0f);
				}

				_docs[_docs.size()-1].getVectorSpace().push_back(tfidf);
				usedIndex.push_back(_docs.size() - 1);
			}
		}
		for (unsigned i=0;i<_docs.size();i++)
		{
			if (std::find(usedIndex.begin(), usedIndex.end(), i) == usedIndex.end())
			{
				_docs[i].getVectorSpace().push_back(0.0f);
			}
		}

		if (termCntr % 50 == 0){
			const float perc = ((float)termCntr/(float)totTerms)*100.0f;
			std::stringstream percentage;
			percentage << perc << "%...";
			std::cout << percentage.str();
		}

		MemoryManager::freeEntryVector(entries);

		termCntr++;
	}
	std::cout << std::endl;
	std::stringstream result;
	result << "Done generating vector space (" << _docs.size() << " documents with " << termCntr << " distinct terms)";
	Logger::log(componentName, result.str(), LogLevel::LALL);
	
	return true;
}
#endif

const Centroid& Clusterer::findClosestCentroid(const Document& doc) const
{
	if (!_loadedVectorSpace) _resultSet[0];
	const int index = closestCentroidToDoc(_resultSet, doc);
	return _resultSet[index];
}

void Clusterer::_prepareCentroid(int k, bool optimal)
{
	if (optimal)
	{
		k = (int)sqrt((float)_docs.size()/2.0f);
	}
	// prepare empty centroid
	std::vector<Centroid> centroids;
	std::vector<int> random;

	Logger::log(componentName, "Generating k centroids.", LogLevel::LALL);

	generateKUniqueNumbers(_docs.size(), k, random);
	assert(random.size() == k);

	Centroid c;

	for (int i=0;i<k;i++)
	{
		Centroid c;
		c.addDoc(_docs[i]);
		centroids.push_back(c);
	}

	bool stopCriteria;
	std::vector<Centroid> prevCluster;

	_resultSet.clear();

	initCluster(_resultSet, centroids.size());

	const int maxDocs = _docs.size();

	Logger::log(componentName, "Creating clusters.", LogLevel::LALL);

	do
	{
		prevCluster = centroids;

		for (int i=0;i<maxDocs;i++)
		{
			int index = closestCentroidToDoc(centroids, _docs[i]);
			_resultSet[index].addDoc(_docs[i]);
		}
		initCluster(centroids, centroids.size());
		calculateMeanPoints(centroids);
		stopCriteria = checkStopCriteria(prevCluster, centroids);
		if (!stopCriteria)
		{
			initCluster(_resultSet, centroids.size());
		}
	}while(!stopCriteria);
}

void Clusterer::prepare(int k, bool optimal)
{
	if (!_prepareVectorSpace()) return;
	_prepareCentroid(k, optimal);

	const unsigned max = _resultSet.size();
	for (unsigned i=0;i<max;i++)
	{
		_resultSet[i].generateName();
	}

	_export();

	_loadedVectorSpace = true;
	_imported = true;
}

const std::vector<Centroid>& Clusterer::getResultCluster() const
{
	return _resultSet;
}

void Clusterer::import()
{
	_import();
}

void Clusterer::_import()
{
	_resultSet.clear();
	std::ifstream infile (exportFileName.c_str());
    _loadedVectorSpace = false;
    Logger::log(componentName, "Attempting to import cluster info from: " + exportFileName, LogLevel::LALL);

	if (infile.is_open()){
		bool inCluster = false;
		bool inVectorSpace = false;
		while(infile.good()){
			std::string line;
      
			getline (infile,line);
			// detect a cluster start
			if (line.empty())
			{
				continue;
			}
			else if (line == dataCentroidStart)
			{
				Centroid currentCentroid;
				_resultSet.push_back(currentCentroid);
				inCluster = true;
				continue;
			}
			else if(line == dataCentroidEnd)
			{
				inCluster = false;
				continue;
			}
			else if (line.find(dataCentroidName) != std::string::npos)
			{
				Tokenizer::strReplace(line, dataCentroidName, "");
				_resultSet[_resultSet.size()-1].setName(line);
				continue;
			}
			else if (line.find(dataCentroidUrl) != std::string::npos)
			{
				Tokenizer::strReplace(line, dataCentroidUrl, "");
				Document doc(line);
				_resultSet[_resultSet.size()-1].addDoc(doc);
			}
			else if (line == dataCentroidVectorSpaceStart)
			{
				_loadedVectorSpace = true;
				inVectorSpace = true;
				continue;
			}
			else if (line == dataCentroidVectorSpaceEnd)
			{
				inVectorSpace = false;
				continue;
			}
			else if (inVectorSpace)
			{
				std::vector<std::string> vectorSpace;
				MetadataHelper::splitLineByDelim(line, '&', vectorSpace);

				const unsigned max = vectorSpace.size();
				const int currentDocId = _resultSet[_resultSet.size()-1].getDocs().size() -1;
				Document& currDoc = _resultSet[_resultSet.size()-1].getDocs()[currentDocId];
				for (unsigned k=0;k<max;k++)
				{
					std::stringstream ss(vectorSpace[k]);
					float value;
					ss >> value;

					currDoc.getVectorSpace().push_back(value);
				}
			}
			else{
				assert(false);
			}
		}
    }
    else{
		Logger::log(componentName, "Could not load cluster data", LogLevel::LALL);
	    _imported = false;
	    return;
    }
	
	Logger::log(componentName, "Successfully imported cluster info.", LogLevel::LALL);
	_imported = true;
}

void Clusterer::_export() const
{
	std::ofstream outfile;
    
    outfile.open(exportFileName.c_str(),  std::ios::out);

    Logger::log(componentName, "Attempting to export cluster info...", LogLevel::LALL);

	if (outfile.is_open())
    {
	  const int max = _resultSet.size();
	  for (int i=0;i<max;i++)
	  {
		  outfile << dataCentroidStart.c_str() << std::endl;

		  outfile << dataCentroidName.c_str() << _resultSet[i].getName() << std::endl;
		  const std::vector<Document>& docs = _resultSet[i].getDocs();
		  const int maxDocs = docs.size();

		  for (int k=0;k<maxDocs;k++)
		  {
			  outfile << dataCentroidUrl.c_str() << docs[k].getUrl() << std::endl;

			  outfile << dataCentroidVectorSpaceStart.c_str() << std::endl;

			  const std::vector<float>& vectorSpace = docs[k].getVectorSpace();
			  const unsigned maxVector = vectorSpace.size();
			  for (unsigned z=0;z<maxVector;z++)
			  {
				  std::stringstream vs;
				  vs << vectorSpace[z];
				  outfile << vs.str().c_str();
				  if ((z+1) == maxVector)
				  {
					  outfile << std::endl;
				  }
				  else
				  {
					  outfile << "&";
				  }
			  }

			  outfile << dataCentroidVectorSpaceEnd.c_str() << std::endl;
		  }		  

		  outfile << dataCentroidEnd.c_str() << std::endl;
	  }
    }
    else{
      Logger::log(componentName, "Error: Couldn't open file to write cluster info (" + exportFileName + ")",
                  LogLevel::LALL);
      assert(false);
    }
    Logger::log(componentName, "Exported successfully to " + exportFileName, LogLevel::LALL);
}