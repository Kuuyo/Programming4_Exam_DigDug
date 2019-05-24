#pragma once
#include <map>
#include "Minigin.h"

namespace dae
{
	class Scene;

	// Based on OverlordEngine SceneManager
	class SceneManager final
	{
	public:
		void AddScene(Scene* pScene);
		void RemoveScene(Scene* pScene);
		void RemoveScene(const std::string& sceneName);

		void SetActiveScene(const std::string& sceneName);
		Scene* GetActiveScene() const;

		Scene* GetScene(const std::string& sceneName) const;
		
	private:
		friend Minigin;

		~SceneManager();

		void Initialize(const GameContext &gameContext);

		void FixedUpdate(float msPerFrame);
		void Update();
		void LateUpdate();
		void DestroyUpdate();
		void TransformUpdate();
		void Render(const GameContext &gameContext, float extrapolate);

		std::map<std::string, Scene*> m_pScenesMap;
		Scene* m_pActiveScene{ nullptr };
		Scene* m_pNewActiveScene{ nullptr };
	};

}
