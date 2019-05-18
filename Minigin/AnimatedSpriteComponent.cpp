#include "MiniginPCH.h"
#include "AnimatedSpriteComponent.h"

namespace dae
{
	AnimatedSpriteComponent::AnimatedSpriteComponent(std::string && fileName, bool isCentered,
		const SDL_Rect & sourceRect)
		: m_FileName(std::move(fileName))
		, m_pTexture(nullptr)
		, m_SourceRect(sourceRect)
		, m_IsCentered(isCentered)
	{
	}
}