#include "MiniginPCH.h"
#include "FPSComponent.h"

#include "TextComponent.h"
#include "Time.h"
#include "GameObject.h"


dae::FPSComponent::FPSComponent()
	: m_FpsDisplay(nullptr)
{

}


dae::FPSComponent::~FPSComponent()
{
}

void dae::FPSComponent::Initialize()
{
	m_FpsDisplay = new TextComponent();
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
