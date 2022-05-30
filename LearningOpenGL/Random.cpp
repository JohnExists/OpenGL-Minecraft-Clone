#include "Random.h"
#include <iostream>


float random::generateRandom(int seed, float min, float max)
{
	static std::mt19937 mt(seed);
	std::uniform_real_distribution<float> randOutput(min, max);

	return randOutput(mt);
}

void random::generateNoise(int seed, int nWidth, int nHeight, int nOctaves,
	float* fOutput)
{
	float* fSeed = new float[nWidth * nHeight];

	for (int i = 0; i < nWidth * nHeight; i++)
	{
		fSeed[i] = generateRandom(seed, 0.0f, 1.0f);
	}

	for (int x = 0; x < nWidth; x++)
		for (int y = 0; y < nHeight; y++)
		{
			float fNoise = 0.0f;
			float fScaleAcc = 0.0f;
			float fScale = 1.0f;

			for (int o = 0; o < nOctaves; o++)
			{ 
				int nPitch = nWidth >> o;
				int nSampleX1 = (x / nPitch) * nPitch;
				int nSampleY1 = (y / nPitch) * nPitch;

				int nSampleX2 = (nSampleX1 + nPitch) % nWidth;
				int nSampleY2 = (nSampleY1 + nPitch) % nWidth;

				float fBlendX = (float)(x - nSampleX1) / (float)nPitch;
				float fBlendY = (float)(y - nSampleY1) / (float)nPitch;

				float fSampleT = ((1.0f - fBlendX) * fSeed[nSampleY1 * nWidth + nSampleX1] + 
					fBlendX * fSeed[nSampleY1 * nWidth + nSampleX2]);
				float fSampleB = (1.0f - fBlendX) * fSeed[nSampleY2 * nWidth + nSampleX1] + 
					fBlendX * fSeed[nSampleY2 * nWidth + nSampleX2];

				fScaleAcc += fScale;
				fNoise += (fBlendY * (fSampleB - fSampleT) + fSampleT) * fScale;
				fScale = fScale / 2.0f;
			}

			fOutput[y * nWidth + x] = fNoise / fScaleAcc;
		}

	delete[] fSeed;
}
float random::generateNoise(int seed, float x, float y)
{


	return 0.0f;
}

