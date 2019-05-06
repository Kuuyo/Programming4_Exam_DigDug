#include "MiniginPCH.h"
#include "TextureComponent.h"

#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Texture2D.h"

dae::TextureComponent::TextureComponent(const std::string& fileName)
	: m_FileName(fileName)
	, m_pTexture(nullptr)
{
}


dae::TextureComponent::~TextureComponent()
{
	delete m_pTexture;
}

void dae::TextureComponent::Initialize(const GameContext &gameContext)
{
	m_pTexture = gameContext.Resources->CreateTexture(m_FileName, m_pParent->GetPosition());
	m_pParent->GetScene()->AddTexture(m_pTexture);
}

void dae::TextureComponent::Update(const GameContext &)
{
}
