#pragma once

namespace dae
{
	class GameObject;
	class Scene;
}

class DigDugLevel;

namespace Characters
{
	class DigDug
	{
	public:
		enum class AnimationClips : unsigned int
		{
			Walking,
			Digging,
			SquishH,
			SquishV,
			Dying,
			ThrowPump,
			Pumping
		};

		static void CreateDigDugCharacter(dae::GameObject* &out, DigDugLevel* pScene, bool isPlayerOne);
		static unsigned short GetCategoryBits() { return m_CategoryBits; }
		static unsigned short GetPumpCategoryBits() { return m_CategoryBitsPump; }

	private:
		static unsigned short m_CategoryBitsP1;
		static unsigned short m_CategoryBitsP2;
		static unsigned short m_CategoryBits;
		static unsigned short m_CategoryBitsPump;
	};

	class Fygar
	{
	public:
		enum class AnimationClips : unsigned int
		{
			Walking,
			Ghosting,
			FireBreath,
			Squish,
			Pumped,
			Ballooning
		};

		static void CreateFygarCharacter(dae::GameObject* &out, DigDugLevel* pScene, bool isPlayer);
		static unsigned short GetCategoryBits() { return m_CategoryBits; }

	private:
		static unsigned short m_CategoryBits;

	};
}