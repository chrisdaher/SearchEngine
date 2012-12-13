#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <algorithm>

#include "preprocessor.h"
#include "docidMapper.h"

namespace
{
	bool replace(std::string& str, const std::string& from, const std::string& to) {
		bool good = false;
		while (!good){
			size_t start_pos = str.find(from);
			
			if (start_pos == std::string::npos) break;
			
			str.replace(start_pos, from.length(), to);
		}
		return true;
	}

	bool getTitleFromLine(std::string line, std::string& title)
	{
		const std::string TITLE_START = "<TITLE>";
		const std::string TITLE_END = "</TITLE>";

		if (std::string::npos == line.find(TITLE_START)) return false;
		if (std::string::npos == line.find(TITLE_END)) return false;

		replace(line, TITLE_START, "");
		replace(line, TITLE_END, "");
    replace(line, "&lt;", "<");

		
		title = std::string(line);
		return true;
	}

	bool isBodyTag(const std::string& line)
	{
		const std::string BODY_START= "<BODY>";
		return (std::string::npos != line.find(BODY_START));
	}

	int bodyStartTagLocation(const std::string& line)
	{
		const std::string BODY_START= "<BODY>";
		return line.find(BODY_START) + BODY_START.size();
	}

	bool isBodyEndTag(const std::string& line)
	{
		const std::string BODY_END = "</BODY>";
		return (std::string::npos != line.find(BODY_END));
	}

	int bodyEndTagLocation(const std::string& line)
	{
		const std::string BODY_END = "</BODY>";
		return line.find(BODY_END) + BODY_END.size();
	}
}

namespace Preprocessor
{
	std::string preprocessBuffer(const std::string& buffer)
	{
		const int bodyStart = (buffer.find("<BODY>"));
		if (bodyStart == std::string::npos) return buffer;
		const int bodyEnd = (buffer.find("</BODY>"));
		if (bodyEnd == std::string::npos) return buffer;

		return buffer.substr(bodyStart + std::string("<BODY>").size(), bodyEnd -1);

	}

	std::vector<std::string> preprocessFiles(const std::vector<std::string>& files)
	{
		std::string file;
		std::vector<std::string> preprocessedFiles;

		int docCntr = 0;
		const unsigned max = files.size();
		for (unsigned i = 0; i < max; i++){    
			file = files[i];
			std::string line;
			std::ifstream myfile (file.c_str());

			std::ofstream outfile;

			bool inBody = false;
			bool foundTitle = false;
			std::string title;

			std::cout << "Preprocessing " << files[i] << std::endl;

			if (myfile.is_open()){
				while ( myfile.good() )
				{
					getline (myfile,line);
					if (!foundTitle)
					{
						if (getTitleFromLine(line, title))
						{
							foundTitle = true;
						}
					}

					if (isBodyEndTag(line))
					{
						outfile.close();
						inBody = false;
						foundTitle = false;
					}

					if (inBody)
					{
						outfile << line.c_str() << std::endl;
					}

					if (isBodyTag(line))
					{
						inBody = true;

						std::stringstream fileName;
            docCntr++;
						fileName << "prep_docs/" << docCntr;

            DocIdMapper::getInstance()->insertIdForTitle(docCntr, title);

						outfile.open(fileName.str().c_str(), (std::ios::out | std::ios::app));

						preprocessedFiles.push_back(fileName.str());
						
						outfile << line.substr(bodyStartTagLocation(line), line.size() - bodyStartTagLocation(line));
					}
				} 
			}
		}
    DocIdMapper::getInstance()->exportMapper();
		return preprocessedFiles;
	}
}

