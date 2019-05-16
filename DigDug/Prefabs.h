#pragma once
namespace dae
{
	class GameObject;
	class Scene;
	struct GameSettings;
	struct GameContext;
}

namespace Prefabs
{
	void CreateLevelBlock(dae::GameObject* &out, const int blockSize = 8);
}