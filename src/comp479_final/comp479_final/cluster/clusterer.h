#ifndef CLUSTERER_H
#define CLUSTERER_H

#include <set>
#include <cluster/document.h>
#include <cluster/centroid.h>

class Clusterer
{
public:
	static Clusterer* getInstance();
	void import();
	void prepare(int k, bool optimal = false);
	float calculateTFIDF(int docLength, int termFreq, int docFreq, int totalDocs) const;
	const std::vector<Centroid>& getResultCluster() const;
	inline bool isLoaded() const{ return _imported; }
	const Centroid& findClosestCentroid(const Document& doc) const;
	void generateDocumentVectorSpace(Document& doc) const;

	bool inline isVectorSpaceLoaded() const { return _loadedVectorSpace; }
private:
	Clusterer();
	bool _prepareVectorSpace();
	void _prepareCentroid(int k, bool optimal = false);
	void _export() const;
	void _import();
private:
	bool _loadedVectorSpace;
	bool _imported;
	std::vector<Centroid> _resultSet;
	std::vector<Document> _docs;
};

#endif