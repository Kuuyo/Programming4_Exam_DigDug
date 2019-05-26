#include "MiniginPCH.h"
#include "HelperFunctions.h"

#include <random>

namespace dae
{
	float Random::GetRandomFloat(float min, float max)
	{
		// https://stackoverflow.com/questions/686353/random-float-number-generation

		std::random_device rd;
		std::mt19937 engine{ rd() };
		std::uniform_real_distribution<float> dist(min, max);

		return glm::round(dist(engine));
	}
}