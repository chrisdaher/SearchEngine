#ifdef WIN32
#include <windows.h>
#endif
#include <iostream>
#include <stdio.h>
#include <sstream>

#include <indexer/rankManager.h>
#include <indexer/memoryManager.h>
#include <indexer/logger.h>
#include <indexer/spimiReader.h>
#include <crawler/crawler.h>
#include <indexer/queryManager.h>
#include <indexer/tokenizer.h>
#include <cluster/clusterer.h>
#include <cluster/centroid.h>
#include <cluster/document.h>

namespace
{
	int depthSelected = 0;
	SpimiReader* sr;
	int crawlerCntr = 0;
	const std::string componentName = "MainManager";
}

void displayCluster(bool full)
{
	if (!Clusterer::getInstance()->isLoaded())
	{
		Clusterer::getInstance()->import();
	}

	const std::vector<Centroid> centroids = Clusterer::getInstance()->getResultCluster();

	int max = centroids.size();
	for (int i=0;i<max;i++){
		std::stringstream ss;
		std::cout << "------------------------------------------" << std::endl;
		ss << "Centroid #" << (i+1) << " - " << centroids[i].getName() << ":";
		Logger::log(componentName, ss.str(), LogLevel::LALL);
		std::cout << "------------------------------------------" << std::endl;
		if (full){
			const std::vector<Document>& docs = centroids[i].getDocs();
			int maxDocs = docs.size();
			for (int j=0;j<maxDocs;j++)
			{
				std::stringstream ss2;
				ss2 << "	Document #" << (j+1) << ":" << docs[j].getUrl();
				Logger::log(componentName, ss2.str(), LogLevel::LALL);
			}
		}
	}
}

void displayResultSet(const std::vector<Centroid> centroids)
{
	int max = centroids.size();
	for (int i=0;i<max;i++){
		std::stringstream ss;
		std::cout << "------------------------------------------" << std::endl;
		ss << "Centroid #" << (i+1) << " - " << centroids[i].getName() << ":";
		Logger::log(componentName, ss.str(), LogLevel::LALL);
		std::cout << "------------------------------------------" << std::endl;
		const std::vector<Document>& docs = centroids[i].getDocs();
		int maxDocs = docs.size();
		for (int j=0;j<maxDocs;j++)
		{
			std::stringstream ss2;
			ss2 << "	Document #" << (j+1) << ":" << docs[j].getUrl();
			Logger::log(componentName, ss2.str(), LogLevel::LALL);
		}
	}
}

void crawlerCb(Crawler::Data data)
{
	std::stringstream ss;
	crawlerCntr++;
	ss << crawlerCntr << ". " << data.getUrl();
	std::cout << ss.str() << std::endl;
	sr->parse(data.getHtml(), Tokenizer::tokenizeUrl(data.getUrl()));
}

void clusterIndex()
{
	std::string input;
	int k;
	bool good = false;

	while(!good){
		std::cout << "Input number of clusters to generate (k) (input -1 for optimal)" << std::endl;
		std::getline(std::cin, input);  
    
		std::stringstream strStream(input);
		strStream >> k;

		good = true;
		if (k > depthSelected){
			std::stringstream ss;
			ss << "Invalid k input (" << k << " > " << depthSelected << ")" << " - k must be <= " << depthSelected << ".";
			std::cout << ss.str() << std::endl;
			good = false;
		}
	}
	bool optimal = k == -1;
	Clusterer::getInstance()->prepare(k, optimal);
	displayResultSet(Clusterer::getInstance()->getResultCluster());
}

void crawlerDone()
{
	std::cout << "Crawler is done" << std::endl;
	sr->finalize();

	clusterIndex();
}

void setMemory()
{
	std::string input;
	int memoryLimit;

	std::cout << "Input memory limit (>0)" << std::endl;
	std::getline(std::cin, input);  
    
  std::stringstream strStream(input);
  strStream >> memoryLimit;
    
  MemoryManager::setMaxMemoryEntries(memoryLimit);    

	strStream.str();
	strStream << memoryLimit;
	std::cout << "Memory set to: " << strStream.str() << std::endl;
}

void generateIndex()
{
	crawlerCntr = 0;
	std::string input;
	int depth;

	std::cout << "Input crawl depth" << std::endl;
	std::getline(std::cin, input);  
    
	std::stringstream strStream(input);
	strStream >> depth;

	depthSelected = depth;

	sr = new SpimiReader();
	Crawler crawl;
	crawl.setCrawlerCallback(crawlerCb);
	crawl.setDoneCallback(crawlerDone);

	crawl.start("http://www.concordia.ca", depth);	
}

void inputQuery()
{
	if (!Clusterer::getInstance()->isLoaded())
	{
		Clusterer::getInstance()->import();
	}

	QueryManager qm;
  std::string query;
	std::cout << "Input query" << std::endl;
	std::getline(std::cin, query);
  qm.executeQuery(query);
}

void showMenu()
{
	bool doneMenu = false;
	std::string inputStr;
	int inputNb;
	while(!doneMenu){
		std::cout << "------------------------" << std::endl;
		std::cout << "Please select an option:" << std::endl;
		std::cout << "1. Crawl and generate index with cluster" << std::endl;
		std::cout << "2. Input query" << std::endl;
		std::cout << "3. Set memory limit" << std::endl;
		std::cout << "4. Cluster index" << std::endl;
		std::cout << "5. View cluster centroids (min)" << std::endl;
		std::cout << "6. View cluster centroids (full)" << std::endl;
		std::cout << "7. Exit" << std::endl;

		inputStr = "";
		std::getline(std::cin, inputStr);
		std::stringstream ss(inputStr);
		ss >> inputNb;
		
		switch(inputNb){
			case 1:
				generateIndex();
				break;	
			case 2:
				inputQuery();
				break;
			case 3:
				setMemory();
				break;
			case 4:
				clusterIndex();
				break;
			case 5:
				displayCluster(false);
				break;
			case 6:
				displayCluster(true);
				break;
			case 7:
				std::cout << "bye" << std::endl;
				if (sr) delete sr;
				exit(0);
				break;
			default:
				std::cout << "Invalid input" << std::endl;
				break;
		}
	}
	
}

int main()
{
	depthSelected = RankManager::getInstance()->getDocCount();
	showMenu();
}
