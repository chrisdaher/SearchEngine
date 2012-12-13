#include "metrics.h"
#include <math.h>
#include <cmath>


#ifdef WIN32
	#define ISNAN(x) _isnan(x)
#else
	#define ISNAN(x) isnan(x)
#endif

namespace ClusterMetrics
{
	float calculateCosine(const std::vector<float>& v1, const std::vector<float>& v2)
	{
		float dotProduct = ClusterMetrics::dotProduct(v1, v2);
		float m1 = magnitude(v1);
		float m2 = magnitude(v2);

		float result = dotProduct / (m1*m2);
		if (ISNAN(result)) return 0.0f;

		return result;
	}

	float dotProduct(const std::vector<float>& v1, const std::vector<float>& v2)
	{
		float dotProduct = 0;
		const int max1 = v1.size();
		const int max2 = v2.size();

		for (int i=0;i<max1;i++)
		{
			dotProduct += v1[i] * v2[i];
		}

		return dotProduct;
	}

	float magnitude(const std::vector<float>& v)
	{
		return (float)(sqrt(dotProduct(v, v)));
	}

	float euclideanDistance(const std::vector<int>& v1, const std::vector<int>& v2)
	{
		float euc = 0.0f;
		const int max = v1.size();
		for (int i=0;i<max;i++)
		{
			euc += (float)(pow(((float)v1[i] - (float)v2[i]), 2.0f));
		}
		return (float)(sqrt(euc));
	}

	float extendedJaccard(const std::vector<float>& v1, const std::vector<float>& v2)
	{
		float dotProduct = ClusterMetrics::dotProduct(v1, v2);
		float m1 = magnitude(v1);
		float m2 = magnitude(v2);

		return dotProduct/(m1+m2-dotProduct);
	}
}
