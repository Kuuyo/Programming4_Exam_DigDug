#include "MiniginPCH.h"
#include "Texture2D.h"

#include "TransformComponent.h"

namespace dae
{
	Texture2D::Texture2D(SDL_Texture* pTexture, TransformComponent* pTransform, const SDL_Rect &sourceRect, bool isCentered)
		: m_SourceRect(sourceRect)
		, m_IsCentered(isCentered)
	{
		m_pTexture = pTexture;
		m_pTransform = pTransform;
	}

	Texture2D::~Texture2D()
	{
	}

	SDL_Texture* Texture2D::GetSDLTexture() const
	{
		return m_pTexture;
	}

	SDL_Rect Texture2D::GetSourceRect() const
	{
		return m_SourceRect;
	}

	void Texture2D::SetSourceRect(const SDL_Rect &src)
	{
		m_SourceRect = src;
	}

	glm::vec2 Texture2D::GetPosition() const
	{
		return m_pTransform->GetPosition();
	}

	SDL_RendererFlip Texture2D::GetOrientation() const
	{
		auto orientation = m_pTransform->GetOrentation();

		if (orientation.x > 0)
		{
			return SDL_RendererFlip::SDL_FLIP_NONE;
		}
		else
		{
			return SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
		}
	}

	bool Texture2D::GetIsCentered() const
	{
		return m_IsCentered;
	}
}