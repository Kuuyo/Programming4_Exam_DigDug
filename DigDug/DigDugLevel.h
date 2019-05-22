#pragma once
#include <Scene.h>
#include <Observer.h>
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

namespace dae
{
	class GameObject;
}

class DigDugLevel final : public dae::Scene, public dae::Observer
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

private:
	void Initialize(const dae::SceneContext &sceneContext) override;
	void Update(const dae::SceneContext &sceneContext) override;

	void OnCollisionEnter(const dae::Contact &contact, dae::GameObject* gameObject) override;
	void OnCollisionStay(const dae::Contact &contact, dae::GameObject* gameObject) override;
	void OnCollisionExit(const dae::Contact &contact, dae::GameObject* gameObject) override;

	void OnNotify(const dae::Subject* entity, int nrArgs, va_list args) override;

	void ResetPlayer(dae::GameObject* gameObject);

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
	glm::vec2 m_PlayerSpawn{};
	const std::string m_LevelName{};
};

