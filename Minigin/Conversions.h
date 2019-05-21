#pragma once

namespace dae
{
	class Conversions
	{
	public:
		static std::vector<SDL_Point> GLM_To_SDL(const std::vector<glm::vec2> &vec);
	};
}