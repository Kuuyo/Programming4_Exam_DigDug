#include "MiniginPCH.h"
#include "Font.h"

namespace dae
{
	Font::Font(const std::string& fullPath, unsigned int size) : m_Font(nullptr), m_Size(size)
	{
		m_Font = TTF_OpenFont(fullPath.c_str(), size);
		if (m_Font == nullptr)
		{
			LogErrorC(std::string("Failed to load font : ") + SDL_GetError());
		}
	}

	Font::~Font()
	{
		TTF_CloseFont(m_Font);
	}

	TTF_Font* Font::GetFont() const
	{
		return m_Font;
	}
}