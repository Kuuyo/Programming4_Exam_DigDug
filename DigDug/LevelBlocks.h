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
	enum class LevelSectionType : int
	{
		Empty = 0,
		Block = 1,
		Rock = 2,
		DigDug = 3,
		Pooka = 4,
		Fygar = 5
	};

	void CreateLevelBlock(dae::GameObject* &out, const int blockSize = 8);
	void CreateLevel(const std::string &level, dae::Scene* pScene,
		const dae::GameSettings &gameSettings, const dae::GameContext &gameContext,
		const int blockSize = 16, const int topBorder = 32, const int bottomBorder = 16);
}