#include <string>

#ifndef RANK_MANAGER_H
#define RANK_MANAGER_H
class RankManager
{
public:

	static RankManager* getInstance(bool load=true);

	void calculateAndAddBuffer(const std::string& buffer);
	int calculateDocLength(const std::string& buffer) const;
	void incrementDocCntr();
	void incrementWordCount(int cntr);
	void setTotalTokenCount(int count);

	int getTotalTokenCount() const;
	int getDocCount() const;
	int getCurrentWordCount() const;
	int getDocWordAverage() const;
	int getAverageWordCount() const;
	void finalize() const;
private:
	RankManager(bool load);
	void _import();
	int _currDocCntr;
	int _currWordCntr;
	int _totalToken;
};
#endif