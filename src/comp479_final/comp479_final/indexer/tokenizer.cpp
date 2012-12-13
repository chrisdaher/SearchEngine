#include "tokenizer.h"
#include <algorithm>

namespace{

#pragma region STOP_WORDS
const unsigned stopWordsCount = 319;
std::string stopWords[] = {"a", "about", "above", "above", "across", "after", "afterwards", "again", 
						   "against", "all", "almost", "alone", "along", "already", "also","although",
						   "always","am","among", "amongst", "amoungst", "amount",  "an", "and", "another", 
						   "any","anyhow","anyone","anything","anyway", "anywhere", "are", "around", "as",  
						   "at", "back","be","became", "because","become","becomes", "becoming", "been", 
						   "before", "beforehand", "behind", "being", "below", "beside", "besides", "between", 
						   "beyond", "bill", "both", "bottom","but", "by", "call", "can", "cannot", "cant", "co", 
						   "con", "could", "couldnt", "cry", "de", "describe", "detail", "do", "done", "down", "due", 
						   "during", "each", "eg", "eight", "either", "eleven","else", "elsewhere", "empty", "enough", "etc", 
						   "even", "ever", "every", "everyone", "everything", "everywhere", "except", "few", "fifteen", "fify", 
						   "fill", "find", "fire", "first", "five", "for", "former", "formerly", "forty", "found", "four", "from", 
						   "front", "full", "further", "get", "give", "go", "had", "has", "hasnt", "have", "he", "hence", "her", 
						   "here", "hereafter", "hereby", "herein", "hereupon", "hers", "herself", "him", "himself", "his", "how", 
						   "however", "hundred", "ie", "if", "in", "inc", "indeed", "interest", "into", "is", "it", "its", "itself", 
						   "keep", "last", "latter", "latterly", "least", "less", "ltd", "made", "many", "may", "me", "meanwhile", 
						   "might", "mill", "mine", "more", "moreover", "most", "mostly", "move", "much", "must", "my", "myself", "name", 
						   "namely", "neither", "never", "nevertheless", "next", "nine", "no", "nobody", "none", "noone", "nor", "not", 
						   "nothing", "now", "nowhere", "of", "off", "often", "on", "once", "one", "only", "onto", "or", "other", 
						   "others", "otherwise", "our", "ours", "ourselves", "out", "over", "own","part", "per", "perhaps", 
						   "please", "put", "rather", "re", "same", "see", "seem", "seemed", "seeming", "seems", "serious", 
						   "several", "she", "should", "show", "side", "since", "sincere", "six", "sixty", "so", "some", 
						   "somehow", "someone", "something", "sometime", "sometimes", "somewhere", "still", "such", "system", 
						   "take", "ten", "than", "that", "the", "their", "them", "themselves", "then", "thence", "there", 
						   "thereafter", "thereby", "therefore", "therein", "thereupon", "these", "they", "thickv", "thin", 
						   "third", "this", "those", "though", "three", "through", "throughout", "thru", "thus", "to", "together", 
						   "too", "top", "toward", "towards", "twelve", "twenty", "two", "un", "under", "until", "up", "upon", 
						   "us", "very", "via", "was", "we", "well", "were", "what", "whatever", "when", "whence", "whenever", 
						   "where", "whereafter", "whereas", "whereby", "wherein", "whereupon", "wherever", "whether", "which", 
						   "while", "whither", "who", "whoever", "whole", "whom", "whose", "why", "will", "with", "within",
						   "without", "would", "yet", "you", "your", "yours", "yourself", "yourselves", "the"};
const unsigned stripCount = 30;
std::string stripChars[] = {"'", ",", "/" , "\\", "`","~","!","\"", ")", 
							"(", "-", "]","[", "+", "*", "%", "}", "{", ";", ".",
							"”", ":", "!", "<div>", "<h1>", "<h2>", "<h3>", "<li>", "<class>", "<title>"};
#pragma endregion
}

namespace Tokenizer
{
	size_t stringCount(const std::string& referenceString,
		               const std::string& subString) 
	{

		const size_t step = subString.size();

		size_t count(0);
		size_t pos(0) ;

		while( (pos=referenceString.find(subString, pos)) !=std::string::npos) {
		    pos +=step;
			++count ;
		}

		return count;

	}

	void strReplace(std::string& str, const std::string& oldStr, const std::string& newStr)
	{
		size_t pos = 0;
		while((pos = str.find(oldStr, pos)) != std::string::npos)
		{
			str.replace(pos, oldStr.length(), newStr);
			pos += newStr.length();
		}
	}

	const std::string tokenizeUrl(const std::string& url)
	{
		std::string ret(url.c_str());
		strReplace(ret, "+", "-");
		strReplace(ret, "*", "");
		strReplace(ret, ",", "");
		strReplace(ret, "%", "");
		return ret;
	}
  const std::string tokenize(const std::string& token)
  {
		std::string ret(token.c_str());
		std::transform(ret.begin(), ret.end(), ret.begin(), ::tolower);
		for (unsigned i=0;i<stripCount;i++)
		{
			strReplace(ret, std::string(stripChars[i]), "");
		}
    
		return ret;
  }

  bool isValidWord(const std::string& word)
  {
	  // link validation
	  if (word.find("href") != std::string::npos) return false;
	  if (word.find("#") != std::string::npos) return false;
	  if (word.find("&") != std::string::npos) return false;
	  if (word.find("?") != std::string::npos) return false;
	  if (word.find("strongli") != std::string::npos) return false;
	  if (word.find("<") != std::string::npos) return false;
	  if (word.find(">") != std::string::npos) return false;
	  if (word.find("=") != std::string::npos) return false;
	  if (word.find("_") != std::string::npos) return false;
	  if ( word[0]<97 || word[0]>122) return false;
	  return true;
	  
  }

  bool isStopWord(const std::string& term)
  {
	  for (unsigned i = 0;i<stopWordsCount;i++){
		  if (term == stopWords[i]) return true;
	  }
	  return false;
  }
}
