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

	private:
		static unsigned short m_CategoryBits;
	};
}