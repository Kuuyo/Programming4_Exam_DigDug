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
	ResourceManager::~ResourceManager()
	{
		//for (auto t : m_pSDLTextureMap)
		//{
		//	SDL_DestroyTexture(t.second);
		//}
		
		for (auto f : m_pFontMap)
		{
			delete f.second;
		}
	}

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

	Texture2D* ResourceManager::CreateTexture(const std::string &file, TransformComponent* pTransform, SDL_Rect &sourceRect, bool isCentered)
	{
		auto pTexture = CreateSDLTexture(file);

		int width{ 0 }, height{ 0 };

		if (SDL_RectEmpty(&sourceRect))
		{
			SDL_QueryTexture(pTexture, nullptr, nullptr, &width, &height);
		}

		width = sourceRect.w > 0 ? sourceRect.w : width;
		height = sourceRect.h > 0 ? sourceRect.h : height;

		sourceRect.w = width;
		sourceRect.h = height;

		return new Texture2D(pTexture, pTransform, sourceRect, isCentered);
	}

	void ResourceManager::CreateTextTexture(const SDL_Color &color, const Font* pFont,
		const std::string &text, Texture2D* &pTexture, TransformComponent* pTransform, bool isCentered)
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

		SDL_Rect sourceRect{};
		int width{ 0 }, height{ 0 };

		SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

		width = sourceRect.w > 0 ? sourceRect.w : width;
		height = sourceRect.h > 0 ? sourceRect.h : height;

		sourceRect.w = width;
		sourceRect.h = height;

		if (pTexture != nullptr)
		{
			SDL_DestroyTexture(pTexture->m_pTexture);
			pTexture->m_pTexture = texture;
			pTexture->SetSourceRect(sourceRect);
			return;
		}

		pTexture = new Texture2D(texture, pTransform, sourceRect, isCentered);
	}

	Font* ResourceManager::LoadFont(const std::string &file, unsigned int size)
	{
		const std::string fullPath = m_DataPath + file;

		if (std::find_if(m_pFontMap.begin(), m_pFontMap.end(),
			[fullPath, size](std::pair<std::pair<std::string, unsigned int>, Font*> f)
				{ return f.first == std::make_pair(fullPath, size); })
			!= m_pFontMap.end())
			return m_pFontMap.at(std::make_pair(fullPath, size));

		Font* pFont = new Font(m_DataPath + file, size);
		m_pFontMap.insert({ std::make_pair(fullPath, size) , pFont });

		return pFont;
	}

	nlohmann::json ResourceManager::LoadJson(const std::string &file)
	{
		// TODO: WRITE ERROR LOGGING
		// CHECK IF IT HAS .json EXTENSION
		const std::string fullPath = m_DataPath + file;

		std::ifstream ifile{ fullPath };

		return nlohmann::json::parse(ifile);
	}

	SDL_Texture* ResourceManager::CreateSDLTexture(const std::string &file)
	{
		const std::string fullPath = m_DataPath + file;

		if (std::find_if(m_pSDLTextureMap.begin(), m_pSDLTextureMap.end(),
			[fullPath](std::pair<std::string, SDL_Texture*> p){ return p.first == fullPath; })
			!= m_pSDLTextureMap.end())
			return m_pSDLTextureMap.at(fullPath);

		SDL_Texture* texture = IMG_LoadTexture(m_pRenderer->GetSDLRenderer(), fullPath.c_str());
		if (texture == nullptr)
		{
			LogErrorC(std::string("Failed to load texture: ") + SDL_GetError());
		}

		m_pSDLTextureMap.insert({ fullPath,texture });

		return texture;
	}
}