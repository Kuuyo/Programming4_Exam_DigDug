#include "MiniginPCH.h"
#include "Conversions.h"

namespace dae
{
	std::vector<SDL_Point> Conversions::GLM_To_SDL(const std::vector<glm::vec2>& vec)
	{
		std::vector<SDL_Point> out;

		for (auto& p : vec)
		{
			out.push_back({ int(p.x),int(p.y) });
		}

		return out;
	}
}