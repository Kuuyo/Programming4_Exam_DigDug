#include "MiniginPCH.h"
#include "Texture2D.h"

dae::Texture2D::Texture2D(SDL_Texture* texture, const glm::vec2 &pos, const SDL_Rect &sourceRect, bool isCentered)
	: m_Position(pos)
	, m_SourceRect(sourceRect)
	, m_IsCentered(isCentered)
{
	m_pTexture = texture;
}

dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_pTexture);
}

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return m_pTexture;
}

SDL_Rect dae::Texture2D::GetSourceRect() const
{
	return m_SourceRect;
}

glm::vec2 dae::Texture2D::GetPosition() const
{
	return m_Position;
}

void dae::Texture2D::SetPosition(float x, float y)
{
	m_Position = { x,y };
}

bool dae::Texture2D::GetIsCentered() const
{
	return m_IsCentered;
}
