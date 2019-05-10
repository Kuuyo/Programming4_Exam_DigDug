#include "MiniginPCH.h"
#include "Texture2D.h"

namespace dae
{
	Texture2D::Texture2D(SDL_Texture* texture, const glm::vec2 &pos, const SDL_Rect &sourceRect, bool isCentered)
		: m_Position(pos)
		, m_SourceRect(sourceRect)
		, m_IsCentered(isCentered)
	{
		m_pTexture = texture;
	}

	Texture2D::~Texture2D()
	{
		// TODO: FIX DESTROYING TEXTURES
		// SDL_DestroyTexture(m_pTexture);
	}

	SDL_Texture* Texture2D::GetSDLTexture() const
	{
		return m_pTexture;
	}

	SDL_Rect Texture2D::GetSourceRect() const
	{
		return m_SourceRect;
	}

	glm::vec2 Texture2D::GetPosition() const
	{
		return m_Position;
	}

	void Texture2D::SetPosition(float x, float y)
	{
		m_Position = { x,y };
	}

	bool Texture2D::GetIsCentered() const
	{
		return m_IsCentered;
	}
}