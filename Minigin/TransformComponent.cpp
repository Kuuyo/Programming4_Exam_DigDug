#include "MiniginPCH.h"
#include "TransformComponent.h"


dae::TransformComponent::TransformComponent()
{
}


dae::TransformComponent::~TransformComponent()
{
}

void dae::TransformComponent::SetPosition(float x, float y, float z)
{
	m_Position = glm::vec3{ x,y,z };
}

void dae::TransformComponent::Initialize()
{
}

void dae::TransformComponent::Update()
{
}

void dae::TransformComponent::Render()
{
}
