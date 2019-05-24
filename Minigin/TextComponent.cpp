#include "MiniginPCH.h"
#include "TextComponent.h"

#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Scene.h"

namespace dae
{
	TextComponent::TextComponent(const std::string& text, bool isCentered, unsigned int fontSize, SDL_Color color, const std::string& font)
		: m_NeedsUpdate(false)
		, m_IsCentered(isCentered)
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
		m_NeedsUpdate = true;
	}

	void TextComponent::SetColor(const SDL_Color &color)
	{
		m_Color = color;
		m_NeedsUpdate = true;
	}

	void TextComponent::Initialize(const SceneContext &sceneContext)
	{
		m_pFont = sceneContext.GameContext->Resources->LoadFont(m_Font, m_FontSize);
		sceneContext.GameContext->Resources->CreateTextTexture(m_Color, m_pFont, m_Text, m_pTexture,
			m_pParent, false);
		m_pTexture->SetIsCentered(m_IsCentered);
		m_pParent->GetScene()->AddTexture(m_pTexture);
	}

	void TextComponent::Update(const SceneContext &sceneContext)
	{
		if (m_NeedsUpdate)
		{
			sceneContext.GameContext->Resources->CreateTextTexture(m_Color, m_pFont, m_Text, m_pTexture,
				m_pParent, false);
			m_NeedsUpdate = false;
		}
	}
}
