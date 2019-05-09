#include "MiniginPCH.h"
#include "TextComponent.h"

#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "ResourceManager.h"

dae::TextComponent::TextComponent(const std::string& text, unsigned int fontSize, SDL_Color color, const std::string& font)
	: m_bNeedsUpdate(false)
	, m_Text(text)
	, m_pFont(nullptr)
	, m_pTexture(nullptr)
	, m_FontSize(fontSize)
	, m_Font(font)
	, m_Color(color)
{}

dae::TextComponent::~TextComponent()
{
	delete m_pFont;
	delete m_pTexture;
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_bNeedsUpdate = true;
}

void dae::TextComponent::Initialize(const GameContext &gameContext)
{
	m_pFont = gameContext.Resources->LoadFont(m_Font, m_FontSize);
	gameContext.Resources->CreateTextTexture(m_Color, m_pFont, m_Text, m_pTexture, m_pParent->GetPosition(), false);
	m_pParent->GetScene()->AddTexture(m_pTexture);
}

void dae::TextComponent::Update(const GameContext &gameContext)
{
	if (m_bNeedsUpdate)
	{
		gameContext.Resources->CreateTextTexture(m_Color, m_pFont, m_Text, m_pTexture, m_pParent->GetPosition(), false);
		m_bNeedsUpdate = false;
	}
}
