#pragma once
#include "Scene.h"

#pragma warning (push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning (pop)

// TODO: Add possibility to add GameObject as a child to a GameObject ?

namespace dae
{
	class BaseComponent;
	class TransformComponent;
	struct GameContext;

	class GameObject final
	{
	public:
		GameObject();
		~GameObject();

		void Initialize(const GameContext &gameContext);
		void Update(const GameContext &gameContext);

		void AddComponent(BaseComponent* component);

		void SetPosition(float x = 0, float y = 0, float z = 0);
		const glm::vec3& GetPosition() const;
		Scene* GetScene() const;

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		friend void Scene::AddGameObject(const std::shared_ptr<GameObject>& object);

		void SetScene(Scene* pScene);

		std::vector<BaseComponent*> m_pVecComponents;
		TransformComponent* m_pTransform;
		Scene* m_pScene;
	};
}
