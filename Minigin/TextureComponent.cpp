#include "MiniginPCH.h"
#include "TextureComponent.h"

#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Texture2D.h"
#include "Scene.h"

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

	void TextureComponent::Initialize(const SceneContext &sceneContext)
	{
		m_pTexture = sceneContext.GameContext->Resources->CreateTexture(m_FileName,
			m_pParent, m_SourceRect, m_IsCentered);
		m_pParent->GetScene()->AddTexture(m_pTexture);
	}

	SDL_Rect TextureComponent::GetSourceRect() const
	{
		return m_SourceRect;
	}

	void TextureComponent::SetSourceRect(const SDL_Rect &src)
	{
		m_SourceRect = src;
		m_pTexture->SetSourceRect(src);
	}
}