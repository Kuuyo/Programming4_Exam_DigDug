#pragma once
#include <Scene.h>

namespace dae
{
	class GameObject;
}

class DigDugLevel final : public dae::Scene
{
public:
	enum class GameMode
	{
		SinglePlayer,
		Coop,
		Versus
	};

	DigDugLevel(std::string &&sceneName, std::string &&levelName, const GameMode gameMode);
	~DigDugLevel();

protected:
	void Initialize(const dae::SceneContext &sceneContext) override;
	void Update(const dae::SceneContext &sceneContext) override;

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

	GameMode m_GameMode;
	dae::GameObject* m_pDigDug{ nullptr };
	dae::GameObject* m_pDigDug2{ nullptr };
	const std::string m_LevelName{};
};

