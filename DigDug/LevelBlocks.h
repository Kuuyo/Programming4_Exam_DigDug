#pragma once
namespace dae
{
	class GameObject;
	class Scene;
	struct GameSettings;
}

namespace Prefabs
{
	void CreateLevelBlock(dae::GameObject* out);
	void CreateLevel(dae::Scene* pScene, const dae::GameSettings &gameSettings, const int blockSize = 8, const int topBorder = 38, const int bottomBorder = 16);
}