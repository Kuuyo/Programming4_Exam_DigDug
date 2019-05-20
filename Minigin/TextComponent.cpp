#include "MiniginPCH.h"
#include "TextComponent.h"

#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "ResourceManager.h"

namespace dae
{
	TextComponent::TextComponent(const std::string& text, unsigned int fontSize, SDL_Color color, const std::string& font)
		: m_bNeedsUpdate(false)
		, m_Text(text)
		, m_pFont(nullptr)
		, m_pTexture(nullptr)
		, m_FontSize(fontSize)
		, m_Font(font)
		, m_Color(color)
	{}

	TextComponent::~TextComponent()
	{
		m_pParent->GetScene()->RemoveTexture(m_pTexture);
		delete m_pTexture;
	}

	void TextComponent::SetText(const std::string& text)
	{
		m_Text = text;
		m_bNeedsUpdate = true;
	}

	void TextComponent::SetColor(const SDL_Color &color)
	{
		m_Color = color;
		m_bNeedsUpdate = true;
	}

	void TextComponent::Initialize(const GameContext &gameContext)
	{
		m_pFont = gameContext.Resources->LoadFont(m_Font, m_FontSize);
		gameContext.Resources->CreateTextTexture(m_Color, m_pFont, m_Text, m_pTexture,
			m_pParent->GetComponent<TransformComponent>(), false);
		m_pParent->GetScene()->AddTexture(m_pTexture);
	}

	void TextComponent::Update(const GameContext &gameContext)
	{
		if (m_bNeedsUpdate)
		{
			gameContext.Resources->CreateTextTexture(m_Color, m_pFont, m_Text, m_pTexture,
				m_pParent->GetComponent<TransformComponent>(), false);
			m_bNeedsUpdate = false;
		}
	}
}
