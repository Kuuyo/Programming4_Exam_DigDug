#include "pch.h"
#include "PlayerComponent.h"


PlayerComponent::PlayerComponent(const std::string &hAxisMapping, const std::string &vAxisMapping,
	const std::string &pumpMapping)
	: m_HAxis(hAxisMapping)
	, m_VAxis(vAxisMapping)
	, m_Pump(pumpMapping)
{
}
