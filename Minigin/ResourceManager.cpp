#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <fstream>

#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

namespace dae
{
	void ResourceManager::Init(std::string&& dataPath, Renderer* pRenderer)
	{
		m_DataPath = std::move(dataPath);
		m_pRenderer = pRenderer;

		// load support for png and jpg, this takes a while!

		if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
		{
			LogErrorC(std::string("Failed to load support for png's: ") + SDL_GetError());
		}

		if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG)
		{
			LogErrorC(std::string("Failed to load support for jpg's: ") + SDL_GetError());
		}

		if (TTF_Init() != 0)
		{
			LogErrorC(std::string("Failed to load support for fonts: ") + SDL_GetError());
		}
	}

	// TODO: Texture library
	Texture2D* ResourceManager::CreateTexture(const std::string &file, const glm::vec2 &pos, const SDL_Rect &sourceRect, bool isCentered)
	{
		return new Texture2D(CreateSDLTexture(file), pos, sourceRect, isCentered);
	}

	void ResourceManager::CreateTextTexture(const SDL_Color &color, const Font* pFont, const std::string &text, Texture2D* &pTexture, const glm::vec2 &pos, bool isCentered)
	{
		const auto surf = TTF_RenderText_Blended(pFont->GetFont(), text.c_str(), color);
		if (surf == nullptr)
		{
			LogErrorC(std::string("Render text failed: ") + SDL_GetError());
		}

		auto texture = SDL_CreateTextureFromSurface(m_pRenderer->GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			LogErrorC(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}

		SDL_FreeSurface(surf);

		if (pTexture != nullptr)
		{
			SDL_DestroyTexture(pTexture->m_pTexture);
			pTexture->m_pTexture = texture;
			return;
		}

		pTexture = new Texture2D(texture, pos, SDL_Rect(), isCentered);
	}

	// TODO: Create a font library
	Font* ResourceManager::LoadFont(const std::string &file, unsigned int size)
	{
		return new Font(m_DataPath + file, size);
	}

	nlohmann::json ResourceManager::LoadJson(const std::string &file)
	{
		const std::string fullPath = m_DataPath + file;

		std::ifstream ifile{ fullPath };

		return nlohmann::json::parse(ifile);
	}

	SDL_Texture* ResourceManager::CreateSDLTexture(const std::string &file)
	{
		std::string fullPath = m_DataPath + file;
		SDL_Texture *texture = IMG_LoadTexture(m_pRenderer->GetSDLRenderer(), fullPath.c_str());
		if (texture == nullptr)
		{
			LogErrorC(std::string("Failed to load texture: ") + SDL_GetError());
		}

		return texture;
	}
}