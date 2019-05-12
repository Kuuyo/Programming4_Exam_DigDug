#pragma once
#include "Scene.h"

#pragma warning (push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning (pop)

#include "TransformComponent.h"

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
		GameObject(std::string &&tag);
		~GameObject();

		void Initialize(const GameContext &gameContext);
		void Update(const GameContext &gameContext);
		void LateUpdate(const GameContext &gameContext);

		void AddComponent(BaseComponent* component);

		void SetPosition(float x = 0, float y = 0, Anchor anchor = Anchor::TopLeft);
		void SetPosition(glm::vec2 pos);
		const glm::vec2 GetPosition() const;
		Scene* GetScene() const;
		std::string GetTag() const { return m_Tag; }

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

#pragma region Templates
		// based on OverLord Engine
		template <class T>
		bool HasComponent()
		{
			// TODO: Effectively you're calling GetComponent twice with this
			// as the most logical action after is to do GetComponent, maybe just delete this
			return GetComponent<T>() != nullptr;
		}

		template <class T>
		T* GetComponent()
		{
			const type_info& ti = typeid(T);
			for (auto* component : m_pVecComponents)
			{
				if (component && typeid(*component) == ti)
					return static_cast<T*>(component);
			}

			LogErrorC(std::string("Component not found: ")
				+ std::string(ti.name()));

			return nullptr;
		}
#pragma endregion

	private:
		friend void Scene::AddGameObject(GameObject* object);

		void SetScene(Scene* pScene);

		template <class T>
		T* GetComponentNoError()
		{
			const type_info& ti = typeid(T);
			for (auto* component : m_pVecComponents)
			{
				if (component && typeid(*component) == ti)
					return static_cast<T*>(component);
			}

			return nullptr;
		}

		std::string m_Tag;
		bool m_IsInitialized;
		std::vector<BaseComponent*> m_pVecComponents;
		TransformComponent* m_pTransform;
		Scene* m_pScene;
	};
}
