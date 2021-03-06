#pragma once
#include <BaseComponent.h>

namespace dae
{
	class AnimatedSpriteComponent;
}

class EnemyComponent : public dae::BaseComponent
{
public:
	EnemyComponent(std::vector<dae::GameObject*> pPlayers);

	// Returns true if Enemy dead
	bool Pump();
	std::vector<dae::GameObject*> GetPlayers() const { return m_pPlayer; }

	EnemyComponent(const EnemyComponent &) = delete;
	EnemyComponent(EnemyComponent &&) = delete;
	EnemyComponent & operator= (const EnemyComponent &) = delete;
	EnemyComponent & operator= (const EnemyComponent &&) = delete;

protected:
	void Initialize(const dae::SceneContext &sceneContext) override;
	void Update(const dae::SceneContext &sceneContext) override;
	void LateUpdate(const dae::SceneContext &) override {}

	virtual ~EnemyComponent() = default;

private:
	unsigned int m_MaxPumps{ 3 };
	unsigned int m_CurrentPumps{ 0 };
	float m_Timer{ 0.f };
	float m_DeflationTime{ .5f };
	dae::AnimatedSpriteComponent* m_pSprite{ nullptr };
	std::vector<dae::GameObject*> m_pPlayer;
	bool m_IsBeingPumped{ false };
};

