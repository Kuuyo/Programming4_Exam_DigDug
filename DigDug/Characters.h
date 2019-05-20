#pragma once

namespace dae
{
	class GameObject;
}

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

		static void CreateDigDugCharacter(dae::GameObject* &out, bool isPlayerOne);
		static unsigned short GetCategoryBits() { return m_CategoryBits; }

	private:
		static unsigned short m_CategoryBitsP1;
		static unsigned short m_CategoryBitsP2;
		static unsigned short m_CategoryBits;
	};
}