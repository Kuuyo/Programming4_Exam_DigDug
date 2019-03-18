#include "MiniginPCH.h"
#include "FPSComponent.h"

#include "TextComponent.h"
#include "Time.h"
#include "GameObject.h"

dae::FPSComponent::FPSComponent(unsigned int fontSize, SDL_Color color)
	: m_FpsDisplay(nullptr)
	, m_Color(color)
	, m_FontSize(fontSize)
{

}


dae::FPSComponent::~FPSComponent()
{
}

void dae::FPSComponent::Initialize()
{
	// TODO: TextComponent being added through FPSComponent: Decide to leave it this like this or find another solution
	// Inherit from TextComponent? (If this is even allowed..)
	// Let Components have components as children?
	m_FpsDisplay = new TextComponent(" ", m_FontSize, m_Color);
	m_FpsDisplay->Initialize();
	m_pParent->AddComponent(m_FpsDisplay);
}

void dae::FPSComponent::Update()
{
	std::string text = std::to_string(Time::GetInstance().GetFPS());
	text.append(" FPS");
	m_FpsDisplay->SetText(text);
}

void dae::FPSComponent::Render()
{
}
