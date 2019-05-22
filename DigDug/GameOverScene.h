#pragma once
#include <Scene.h>

class GameOverScene final : public dae::Scene
{
public:
	GameOverScene();
	~GameOverScene();

	GameOverScene(const GameOverScene&) = delete;
	GameOverScene(GameOverScene&&) = delete;
	GameOverScene& operator= (const GameOverScene&) = delete;
	GameOverScene& operator= (const GameOverScene&&) = delete;

private:
	void Initialize(const dae::SceneContext &sceneContext) override;
	void Update(const dae::SceneContext &sceneContext) override;
};