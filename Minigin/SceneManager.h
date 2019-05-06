#pragma once
#include "Singleton.h"
#include <map>

namespace dae
{
	class Scene;

	// Based on OverlordEngine SceneManager
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void Initialize();
		void Cleanup();

		void Update();
		void Render(float extrapolate);		

		void AddScene(Scene* pScene);
		void RemoveScene(Scene* pScene);
		void RemoveScene(const std::string& sceneName);

		void SetActiveScene(const std::string& sceneName);
		Scene* GetActiveScene() const;
		
	private:
		std::map<std::string, Scene*> m_pScenesMap;
		Scene* m_pActiveScene;
	};

}
