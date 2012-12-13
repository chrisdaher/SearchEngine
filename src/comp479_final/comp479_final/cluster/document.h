#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <map>
#include <vector> 
class Document
{
public:
	Document(const std::string& url);
	Document(const std::string& content, const std::string& url, int tokenCount);
	void setTfd(const std::string& term);

	inline void setTokenCount(int count){ _tokenCount = count; }

	bool operator<(const Document& rhs) const;
	bool operator==(const Document& rhs) const;

	inline const std::string& getContent() const { return _content; }
	inline const std::string& getUrl() const { return _url; }
	inline int getTokenCount() const { return _tokenCount; }
	inline int getTemporaryFrequency() const { return _tempFrequency; }

	void reserveVectorSpaceSize(int size);
	std::vector<float>& getVectorSpace();
	const std::vector<float>& getVectorSpace() const;
	void assignTemporaryFrequency(int freq);
private:
	int _tempFrequency;
	int _tokenCount;
	std::string _url;
	std::string _content;
	
	std::vector<float> vectorSpace;
};

#endif