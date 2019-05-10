#include "MiniginPCH.h"
#include "FPSComponent.h"

#include "TextComponent.h"
#include "Time.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Font.h"
#include "Texture2D.h"

namespace dae
{
	FPSComponent::FPSComponent(bool isCentered, unsigned int fontSize, SDL_Color color)
		: m_Color(color)
		, m_FontSize(fontSize)
		, m_pTexture(nullptr)
		, m_pFont(nullptr)
		, m_Text(" ")
		, m_IsCentered(isCentered)
	{

	}

	FPSComponent::~FPSComponent()
	{
		delete m_pFont;
		delete m_pTexture;
	}

	void FPSComponent::Initialize(const GameContext &gameContext)
	{
		m_pFont = gameContext.Resources->LoadFont("Lingua.otf", m_FontSize);
		gameContext.Resources->CreateTextTexture(m_Color, m_pFont, m_Text, m_pTexture, m_pParent->GetPosition(), m_IsCentered);
		m_pParent->GetScene()->AddTexture(m_pTexture);
	}

	void FPSComponent::Update(const GameContext &gameContext)
	{
		std::string text = std::to_string(gameContext.Time->GetFPS());
		text.append(" FPS");
		m_Text = text;

		gameContext.Resources->CreateTextTexture(m_Color, m_pFont, m_Text, m_pTexture, m_pParent->GetPosition(), m_IsCentered);
	}
}