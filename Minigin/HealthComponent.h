#pragma once
#include "BaseComponent.h"

namespace dae
{// TODO: Maybe use something else than a component for Health?

	enum class HealthStatus
	{
		Alive,
		LostLife,
		Dead,
		OverHealed
	};

	class HealthComponent final : public BaseComponent
	{
	public:
		HealthComponent(float maxHealth, float startHealth, unsigned int maxNrOfLives, unsigned int startLives);
		HealthComponent(float maxHealth, unsigned int maxNrOfLives);

		bool Damage(float value);
		void Heal(float value, bool isOverHealingAllowed = false);
		HealthStatus ChangeHealth(float value, bool isOverHealingAllowed = false);
		bool IsAlive() const;
		void SetHealth(float value);

		void AddLives(unsigned int value);
		bool RemoveLives(unsigned int value);
		bool NextLife();
		void Reset();

		void SetMaxHealth(float value);
		void SetMaxNrOfLives(unsigned int value);

		HealthComponent(const HealthComponent&) = delete;
		HealthComponent(HealthComponent&&) = delete;
		HealthComponent& operator= (const HealthComponent&) = delete;
		HealthComponent& operator= (const HealthComponent&&) = delete;

	protected:
		void Initialize(const GameContext &) override {}
		void Update(const GameContext &) override {}
		void LateUpdate(const GameContext &) override {}

		virtual ~HealthComponent() = default;

		float m_MaxHealth;
		float m_CurrentHealth;
		unsigned int m_MaxNrOfLives;
		unsigned int m_CurrentNrOfLives;
	};
}