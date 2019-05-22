#pragma once
#include "json.hpp"

namespace dae
{
	class Texture2D;
	class Font;
	class Renderer;
	class TransformComponent;

	class ResourceManager final
	{		
	public:
		ResourceManager() = default;
		~ResourceManager();

		void Init(std::string&& data, Renderer* pRenderer);

		Texture2D* CreateTexture(const std::string &file, TransformComponent* pTransform,
			SDL_Rect &sourceRect, bool isCentered);

		void CreateTextTexture(const SDL_Color &color, const Font* pFont, const std::string &text,
			Texture2D* &pTexture, TransformComponent* pTransform, bool isCentered);

		Font* LoadFont(const std::string& file, unsigned int size);

		nlohmann::json LoadJson(const std::string& file);

	private:
		SDL_Texture* CreateSDLTexture(const std::string &file);

		Renderer* m_pRenderer{ nullptr };
		std::string m_DataPath;
		std::map<std::string, SDL_Texture*> m_pSDLTextureMap;
		std::map<std::pair<std::string, unsigned int>, Font*> m_pFontMap;
	};

}
