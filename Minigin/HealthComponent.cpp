#include "MiniginPCH.h"
#include "HealthComponent.h"

namespace dae
{
	HealthComponent::HealthComponent(float maxHealth, float startHealth, unsigned int maxNrOfLives,
		unsigned int startLives)
		: m_MaxHealth(maxHealth)
		, m_CurrentHealth(startHealth)
		, m_MaxNrOfLives(maxNrOfLives)
		, m_CurrentNrOfLives(startLives)
	{}

	HealthComponent::HealthComponent(float maxHealth, unsigned int maxNrOfLives)
		: HealthComponent(maxHealth, maxHealth, maxNrOfLives, maxNrOfLives)
	{}

	bool HealthComponent::Damage(float value)
	{
		ChangeHealth(-value);
		return IsAlive();
	}

	void HealthComponent::Heal(float value, bool isOverHealingAllowed)
	{
		ChangeHealth(value, isOverHealingAllowed);
	}

	HealthStatus HealthComponent::ChangeHealth(float value, bool isOverHealingAllowed)
	{
		m_CurrentHealth += value;

		if (m_CurrentHealth <= 0.f)
			RemoveLives(1);

		if (!isOverHealingAllowed) glm::max(m_CurrentHealth, m_MaxHealth);

		if (m_CurrentHealth <= 0.f && m_CurrentNrOfLives > 0)
			return HealthStatus::LostLife;

		if (m_CurrentHealth <= 0.f && m_CurrentNrOfLives <= 0)
			return HealthStatus::Dead;

		if (m_CurrentHealth > m_MaxHealth)
			return HealthStatus::OverHealed;

		return HealthStatus::Alive;
	}

	bool HealthComponent::IsAlive() const
	{
		return m_CurrentHealth > 0.f;
	}

	void HealthComponent::SetHealth(float value)
	{
		m_CurrentHealth = value;
	}

	void HealthComponent::AddLives(unsigned int value)
	{
		m_CurrentNrOfLives += value;
	}

	bool HealthComponent::RemoveLives(unsigned int value)
	{
		m_CurrentNrOfLives -= value;
		return IsAlive();
	}

	bool HealthComponent::NextLife()
	{
		m_CurrentHealth = m_MaxHealth;
		--m_MaxNrOfLives;
		return IsAlive();
	}

	void HealthComponent::Reset()
	{
		m_CurrentHealth = m_MaxHealth;
		m_CurrentNrOfLives = m_MaxNrOfLives;
	}

	void HealthComponent::SetMaxHealth(float value)
	{
		m_MaxHealth = value;
	}

	void HealthComponent::SetMaxNrOfLives(unsigned int value)
	{
		m_MaxNrOfLives = value;
	}
}