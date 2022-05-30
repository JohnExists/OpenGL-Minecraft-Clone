#ifndef RANDOM_H
#define RANDOM_H

#include<random>
#include<string>
#include<cmath>
#include<vector>
#include <map>
#include <glm/glm.hpp>

namespace random
{
	float generateRandom(int seed, float min, float max);
	void generateNoise(int seed, int nWidth, int nHeight, int nOctaves,
		float* fOutput);

	float generateNoise(int seed, float x, float y);


}

#endif // !RANDOM_H
