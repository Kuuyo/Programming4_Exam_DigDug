#include "MiniginPCH.h"
#include "FPSComponent.h"

#include "TextComponent.h"
#include "Time.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Font.h"
#include "Texture2D.h"
#include "Scene.h"

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
		m_pParent->GetScene()->RemoveTexture(m_pTexture);
		delete m_pTexture;
	}

	void FPSComponent::Initialize(const SceneContext &sceneContext)
	{
		m_pFont = sceneContext.GameContext->Resources->LoadFont("Lingua.otf", m_FontSize);
		sceneContext.GameContext->Resources->CreateTextTexture(m_Color, m_pFont, m_Text, m_pTexture,
			m_pParent, m_IsCentered);
		m_pParent->GetScene()->AddTexture(m_pTexture);
	}

	void FPSComponent::Update(const SceneContext &sceneContext)
	{
		std::string text = std::to_string(sceneContext.GameContext->Time->GetFPS());
		text.append(" FPS");
		m_Text = text;

		sceneContext.GameContext->Resources->CreateTextTexture(m_Color, m_pFont, m_Text, m_pTexture,
			m_pParent, m_IsCentered);
	}
}