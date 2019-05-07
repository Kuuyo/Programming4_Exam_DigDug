#include "MiniginPCH.h"
#include "Texture2D.h"

dae::Texture2D::Texture2D(SDL_Texture* texture, glm::vec2 pos)
{
	m_pTexture = texture;
	m_Position = pos;
}

dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_pTexture);
}

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return m_pTexture;
}

glm::vec2 dae::Texture2D::GetPosition() const
{
	return m_Position;
}

void dae::Texture2D::SetPosition(float x, float y)
{
	m_Position = { x,y };
}
