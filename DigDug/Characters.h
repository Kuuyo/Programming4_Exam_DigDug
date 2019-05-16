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
		static void CreateDigDugCharacter(dae::GameObject* &out);
		static unsigned short GetCategoryBits() { return m_CategoryBits; }

	private:
		static unsigned short m_CategoryBits;
	};
}