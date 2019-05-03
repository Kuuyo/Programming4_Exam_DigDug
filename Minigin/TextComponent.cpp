#include "MiniginPCH.h"
#include "TextComponent.h"

#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "ResourceManager.h"

dae::TextComponent::TextComponent(const std::string& text, unsigned int fontSize, SDL_Color color, const std::string& font)
	: m_bNeedsUpdate(true)
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

void dae::TextComponent::Initialize()
{
	m_pFont = ResourceManager::GetInstance().LoadFont(m_Font, m_FontSize);
	CreateTextTexture();
}

void dae::TextComponent::Update()
{
	if (m_bNeedsUpdate)
	{
		CreateTextTexture();
	}
}

void dae::TextComponent::Render()
{
	if (m_pTexture != nullptr)
	{
		const auto pos = m_pParent->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}

void dae::TextComponent::CreateTextTexture()
{
	const SDL_Color color = m_Color; // only white text is supported now
	const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);

	if(m_pTexture != nullptr)
		delete m_pTexture;

	m_pTexture = new Texture2D(texture);
	m_bNeedsUpdate = false;
}
