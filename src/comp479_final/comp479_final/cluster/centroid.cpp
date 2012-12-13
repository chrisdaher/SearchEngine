#include <vector>
#include <sstream>

#include "centroid.h"
#include <indexer/tokenizer.h>
#include <indexer/metadataHelper.h>

Centroid::Centroid() {}

void Centroid::addDoc(const Document& doc)
{
	_docs.push_back(doc);
}

const std::vector<Document>& Centroid::getDocs() const
{
	return _docs;
}

std::vector<Document>& Centroid::getDocs()
{
	return _docs;
}

void Centroid::generateName()
{
	const int max = _docs.size();
	if (max == 0) return;

	std::vector<std::string> docsUrl;
	docsUrl.reserve(max);

	std::stringstream fullLine;

	for (int i=0;i<max;i++)
	{
		std::string temp = _docs[i].getUrl();
		Tokenizer::strReplace(temp, "http://", "");
		Tokenizer::strReplace(temp, "https://", "");

		std::vector<std::string> slashSplits;
		MetadataHelper::splitLineByDelim(temp, '/', slashSplits);

		for (unsigned i=0;i<slashSplits.size();i++)
		{
			if (slashSplits[i].find("www.") != std::string::npos) continue;

			std::vector<std::string> dashSplits;
			MetadataHelper::splitLineByDelim(slashSplits[i], '-', dashSplits);

			for (unsigned k=0;k<dashSplits.size();k++)
			{
				docsUrl.push_back(dashSplits[k]);
				fullLine << dashSplits[k] << " ";
			}
		}
	}

	std::vector<int> counter;
	const int maxWords = docsUrl.size();

	if (maxWords == 0) return;

	counter.reserve(maxWords);
	for (int i=0;i<maxWords;i++)
	{
		counter.push_back(Tokenizer::stringCount(fullLine.str(), docsUrl[i]));
	}

	// find max
	int index = 0;
	int currentMax = counter[index];
	for (int i=0;i<maxWords;i++)
	{
		if (counter[i] > currentMax && !Tokenizer::isStopWord(docsUrl[i]))
		{
			index = i;
			currentMax = counter[i];
		}
	}

	_name = docsUrl[index];
}

const std::string& Centroid::getName() const
{
	return _name;
}

void Centroid::setName(const std::string& name)
{
	_name = name;
}