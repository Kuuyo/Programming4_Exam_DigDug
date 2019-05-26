#pragma once
#include <BaseComponent.h>

class PlayerComponent : public dae::BaseComponent
{
public:
	PlayerComponent(const std::string &hAxisMapping, const std::string &vAxisMapping,
		const std::string &pumpMapping);

	std::string GetHAxisMapping() const { return m_HAxis; }
	std::string GetVAxisMapping() const { return m_VAxis; }
	std::string GetPumpMapping() const { return m_Pump; }

	PlayerComponent(const PlayerComponent &) = delete;
	PlayerComponent(PlayerComponent&&) = delete;
	PlayerComponent& operator= (const PlayerComponent&) = delete;
	PlayerComponent& operator= (const PlayerComponent&&) = delete;

protected:
	void Initialize(const dae::SceneContext &) override {}
	void Update(const dae::SceneContext &) override {}
	void LateUpdate(const dae::SceneContext &) override {}

	virtual ~PlayerComponent() = default;

private:
	std::string m_HAxis, m_VAxis, m_Pump;
};

