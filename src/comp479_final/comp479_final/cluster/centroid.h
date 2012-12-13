#ifndef CENTROID_H
#define CENTROID_H

#include <vector>
#include <string>
#include "document.h"

class Centroid
{
public:
	Centroid();
	void addDoc(const Document& doc);
	const std::vector<Document>& getDocs() const;
	std::vector<Document>& getDocs();
	void generateName();
	const std::string& getName() const;
	void setName(const std::string& name);
private:
	std::string _name;
	std::vector<Document> _docs;
};

#endif 