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

void dae::TextureComponent::Initialize()
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(m_FileName);
}

void dae::TextureComponent::Update()
{
}

void dae::TextureComponent::Render()
{
	auto pos = m_pParent->GetPosition();
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}
