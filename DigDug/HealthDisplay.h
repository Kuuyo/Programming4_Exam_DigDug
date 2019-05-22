#pragma once

namespace dae
{
	class GameObject;
}

namespace HealthDisplay
{
	void CreateHealthDisplay(dae::GameObject* &out, const std::string &playerName);
}