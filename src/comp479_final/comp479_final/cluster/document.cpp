#include "document.h"

Document::Document(const std::string& url)
{
	_url = url;
}

Document::Document(const std::string& content, const std::string& url, int tokenCount)
{
	_content = content;
	_url = url;
	_tokenCount = tokenCount;
}

void Document::assignTemporaryFrequency(int freq)
{
	_tempFrequency = freq;
}

bool Document::operator<(const Document& rhs) const
{
	return (_url < rhs._url);
}

bool Document::operator==(const Document& rhs) const
{
	return (_url == rhs._url);
}

void Document::reserveVectorSpaceSize(int size)
{
	vectorSpace.reserve(size);
}

std::vector<float>& Document::getVectorSpace()
{
	return vectorSpace;
}

const std::vector<float>& Document::getVectorSpace() const
{
	return vectorSpace;
}