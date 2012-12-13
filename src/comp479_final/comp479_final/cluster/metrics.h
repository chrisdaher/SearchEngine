#include <vector>

namespace ClusterMetrics
{

	float calculateCosine(const std::vector<float>& v1, const std::vector<float>& v2);
	float dotProduct(const std::vector<float>& v1, const std::vector<float>& v2);
	float magnitude(const std::vector<float>& v);
	float euclideanDistance(const std::vector<int>& v1, const std::vector<int>& v2);
	float extendedJaccard(const std::vector<float>& v1, const std::vector<float>& v2); 

}