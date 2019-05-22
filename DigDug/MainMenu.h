#pragma once
#include <Scene.h>

class MainMenu final : public dae::Scene
{
public:
	MainMenu();
	~MainMenu();

	MainMenu(const MainMenu&) = delete;
	MainMenu(MainMenu&&) = delete;
	MainMenu& operator= (const MainMenu&) = delete;
	MainMenu& operator= (const MainMenu&&) = delete;

private:
	void Initialize(const dae::SceneContext &sceneContext) override;
	void Update(const dae::SceneContext &sceneContext) override;

	void SelectGameObject(dae::GameObject* gameObject);
	void UnSelectGameObject(dae::GameObject* gameObject);

	std::vector<dae::GameObject*> m_MenuSelectableObjects;
	int m_CurrentlySelected;
	float m_PreviousAxis;
};

