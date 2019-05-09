#pragma once
#include "Scene.h"

class Level_1 final : public dae::Scene
{
public:
	Level_1();
	~Level_1();

protected:
	void Initialize(const dae::GameContext &gameContext) override;
	void Update(const dae::GameContext &gameContext) override;
};

