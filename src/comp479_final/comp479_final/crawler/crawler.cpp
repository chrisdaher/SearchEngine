#include <crawler/crawler.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <iostream>
#include <stdio.h>
#include <chilkat/CkSpider.h>
#include <chilkat/CkStringArray.h>

Crawler::Data::Data(const std::string& html, const std::string& url)
{
	_html = html;
	_url = url;
}

void Crawler::Data::setUrl(const std::string& url)
{
	_url = url;
}

void Crawler::Data::setHtml(const std::string& html)
{
	_html = html;
}

const std::string& Crawler::Data::getHtml() const
{
	return _html;
}

const std::string& Crawler::Data::getUrl() const
{
	return _url;
}

Crawler::Crawler(){}

void Crawler::setCrawlerCallback(void(*cb)(Crawler::Data))
{
	_crawlerCallbackFunc = cb;
}

void Crawler::setDoneCallback(void(*cb)(void))
{
	_crawlerDoneCallbackFunc = cb;
}

void Crawler::_sendCrawlerCallback(const Crawler::Data& data)
{
	if (!_crawlerCallbackFunc) return;
	_crawlerCallbackFunc(data);
}

void Crawler::_sendDoneCallback()
{
	if (!_crawlerDoneCallbackFunc) return;
	_crawlerDoneCallbackFunc();
}

void Crawler::start(const std::string& base, int depth)
{
    CkSpider spider;
	
	CkStringArray seedUrls;
	CkStringArray seenDomains;

	seenDomains.put_Unique(true);
    seedUrls.put_Unique(true);
	seedUrls.Append(base.c_str());

	spider.put_CacheDir("./spiderCache/");
    spider.put_FetchFromCache(true);
    spider.put_UpdateCache(true);

    //  Begin crawling the site by calling CrawlNext repeatedly.
	while(seedUrls.get_Count() > 0){
        bool success;
		const char * url;
        url = seedUrls.pop();
		spider.Initialize(url);

		const char * domain;
        domain = spider.getUrlDomain(url);
        seenDomains.Append(spider.getBaseDomain(domain));
		int cntr = 0;

		while(true && ((cntr < depth) || (depth == -1)))
		{
			cntr++;
			success = spider.CrawlNext();
			if (!success) break;

			Crawler::Data data(spider.lastHtml(), spider.lastUrl());
			_sendCrawlerCallback(data); 

			// dont wait if retrieved from cache
			if (spider.get_LastFromCache() != true) {
                spider.SleepMs(1000);
            }
		}
	}
	_sendDoneCallback();
}
