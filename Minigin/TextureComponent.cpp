#include "MiniginPCH.h"
#include "TextureComponent.h"

#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Texture2D.h"

namespace dae
{
	TextureComponent::TextureComponent(std::string&& fileName, bool isCentered, const SDL_Rect &sourceRect)
		: m_FileName(std::move(fileName))
		, m_pTexture(nullptr)
		, m_SourceRect(sourceRect)
		, m_IsCentered(isCentered)
	{
	}


	TextureComponent::~TextureComponent()
	{
		m_pParent->GetScene()->RemoveTexture(m_pTexture);
		delete m_pTexture;
	}

	void TextureComponent::Initialize(const GameContext &gameContext)
	{
		m_pTexture = gameContext.Resources->CreateTexture(m_FileName,
			m_pParent->GetComponent<TransformComponent>(), m_SourceRect, m_IsCentered);
		m_pParent->GetScene()->AddTexture(m_pTexture);
	}
}