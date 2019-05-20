#pragma once
#include <map>

namespace dae
{
	class Scene;

	// Based on OverlordEngine SceneManager
	class SceneManager final
	{
	public:
		~SceneManager();

		void Initialize(const GameContext &gameContext);

		void FixedUpdate(float msPerFrame);
		void Update();
		void LateUpdate();
		void DestroyUpdate();
		void Render(const GameContext &gameContext, float extrapolate);		

		void AddScene(Scene* pScene);
		void RemoveScene(Scene* pScene);
		void RemoveScene(const std::string& sceneName);

		void SetActiveScene(const std::string& sceneName);
		Scene* GetActiveScene() const;
		
	private:
		std::map<std::string, Scene*> m_pScenesMap;
		Scene* m_pActiveScene{ nullptr };
	};

}
