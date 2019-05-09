#pragma once
#include "Scene.h"

namespace dae
{
	class GameObject;
}

class Level_1 final : public dae::Scene
{
public:
	Level_1();
	~Level_1();

protected:
	void Initialize(const dae::GameContext &gameContext) override;
	void Update(const dae::GameContext &gameContext) override;

	void OnCollisionEnter(b2Contact* contact, dae::GameObject* gameObject) override;
	void OnCollisionStay(b2Contact* contact, dae::GameObject* gameObject) override;
	void OnCollisionExit(b2Contact* contact, dae::GameObject* gameObject) override;

private:
	dae::GameObject* m_pDigDug{ nullptr };
};

