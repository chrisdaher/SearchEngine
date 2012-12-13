#include <string>

#ifndef CRAWLER_H
#define CRAWLER_H
class Crawler
{
public:
	class Data
	{
	public:
		Data(const std::string& html, const std::string& url);
		void setUrl(const std::string& url);
		void setHtml(const std::string& html);
		const std::string& getUrl() const;
		const std::string& getHtml() const;
	private:
		std::string _url;
		std::string _html;
	};

	Crawler();
	void setCrawlerCallback(void(*cb)(Crawler::Data));
	void setDoneCallback(void(*cb)(void));
	void start(const std::string& base, int depth);
private:
	void _sendCrawlerCallback(const Crawler::Data& data);
	void _sendDoneCallback();	
	void(*_crawlerCallbackFunc)(Crawler::Data);
	void(*_crawlerDoneCallbackFunc)(void);
};
#endif