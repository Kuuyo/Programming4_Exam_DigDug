#include "MiniginPCH.h"
#include "TextureComponent.h"

#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Texture2D.h"

dae::TextureComponent::TextureComponent(std::string&& fileName, bool isCentered, const SDL_Rect &sourceRect)
	: m_FileName(std::move(fileName))
	, m_pTexture(nullptr)
	, m_SourceRect(sourceRect)
	, m_IsCentered(isCentered)
{
}


dae::TextureComponent::~TextureComponent()
{
	delete m_pTexture;
	m_pParent->GetScene()->RemoveTexture(m_pTexture);
}

void dae::TextureComponent::Initialize(const GameContext &gameContext)
{
	m_pTexture = gameContext.Resources->CreateTexture(m_FileName, m_pParent->GetPosition(), m_SourceRect, m_IsCentered);
	m_pParent->GetScene()->AddTexture(m_pTexture);
}

void dae::TextureComponent::Update(const GameContext &)
{
	auto pos = m_pParent->GetPosition();
	m_pTexture->SetPosition(pos.x, pos.y);
}
