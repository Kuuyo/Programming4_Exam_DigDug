#pragma once
#include <Scene.h>

namespace dae
{
	class GameObject;
}

class DigDugLevel final : public dae::Scene
{
public:
	DigDugLevel(std::string &&levelName);
	~DigDugLevel();

protected:
	void Initialize(const dae::GameContext &gameContext) override;
	void Update(const dae::GameContext &gameContext) override;

	void OnCollisionEnter(const dae::Contact &contact, dae::GameObject* gameObject) override;
	void OnCollisionStay(const dae::Contact &contact, dae::GameObject* gameObject) override;
	void OnCollisionExit(const dae::Contact &contact, dae::GameObject* gameObject) override;

private:
	enum class LevelSectionType : int
	{
		Empty = 0,
		Block = 1,
		Rock = 2,
		DigDug = 3,
		Pooka = 4,
		Fygar = 5
	};

	dae::GameObject* m_pDigDug{ nullptr };
	const std::string m_LevelName{};
};

