#pragma once
#include "json.hpp"

namespace dae
{
	class Texture2D;
	class Font;
	class Renderer;

	class ResourceManager final
	{		
	public:
		ResourceManager() = default;

		void Init(std::string&& data, Renderer* pRenderer);

		Texture2D* CreateTexture(const std::string &file, const glm::vec2 &pos, const SDL_Rect &sourceRect, bool isCentered);

		void CreateTextTexture(const SDL_Color &color, const Font* pFont, const std::string &text, Texture2D* &pTexture, const glm::vec2 &pos, bool isCentered);
		Font* LoadFont(const std::string& file, unsigned int size);

		nlohmann::json LoadJson(const std::string& file);

	private:
		SDL_Texture* CreateSDLTexture(const std::string &file);

		Renderer* m_pRenderer{ nullptr };
		std::string m_DataPath;
	};

}
