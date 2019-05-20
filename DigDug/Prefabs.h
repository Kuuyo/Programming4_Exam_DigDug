#pragma once
namespace dae
{
	class GameObject;
	class Scene;
	struct GameSettings;
	struct GameContext;
}

namespace Level
{
	// TODO: Make a baseclass for this kind or find another structure
	// As this is mainly to keep the filter bits, maybe make an enum or something

	class LevelBlock
	{
	public:
		static void CreateLevelBlock(dae::GameObject* &out, const int blockSize = 8);
		static unsigned short GetCategoryBits() { return m_CategoryBits; }

	private:
		static unsigned short m_CategoryBits;
	};

	class Rock
	{
	public:
		enum class AnimationClips : unsigned int
		{
			Wiggle,
			Break
		};

		static void CreateRock(dae::GameObject* &out, const int blockSize);
		static unsigned short GetCategoryBits() { return m_CategoryBits; }

	private:
		static unsigned short m_CategoryBits;
	};
}