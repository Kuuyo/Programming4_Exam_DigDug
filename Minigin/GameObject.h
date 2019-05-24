#pragma once

#pragma warning (push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning (pop)

namespace dae
{
	class BaseComponent;
	class Scene;
	struct SceneContext;

	enum class Anchor
	{
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight,
		TopCenter,
		BottomCenter,
		Center
	};

	class GameObject final
	{
	public:
		GameObject();
		GameObject(std::string &&tag);
		~GameObject();

		void AddComponent(BaseComponent* component);
		void RemoveComponent(BaseComponent* component);

		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);

		Scene* GetScene() const;
		std::string GetTag() const { return m_Tag; }

#pragma region Transform
		glm::vec2 GetPosition(Anchor anchor = Anchor::TopLeft) const;
		void SetPosition(float x, float y, Anchor anchor = Anchor::TopLeft);
		void SetPosition(const glm::vec2 &newPos, Anchor anchor = Anchor::TopLeft);

		glm::vec2 GetLocalPosition() const;
		void SetLocalPosition(float x, float y);
		void SetLocalPosition(const glm::vec2 &lPos);

		glm::vec2 GetOrentation() const;
		void SetOrientation(const glm::vec2 &orientation);
		void SetOrientation(float x, float y);
		void SetOrientationX(float x);
		void SetOrientationY(float y);
#pragma endregion

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
#pragma endregion

	private:
		friend Scene;

		void SetScene(Scene* pScene);

		void Initialize(const SceneContext &sceneContext);
		void Update(const SceneContext &sceneContext);
		void LateUpdate(const SceneContext &sceneContext);
		void TransformUpdate();

		GameObject* m_pParent{ nullptr };

		glm::vec2 m_LocalPosition;
		glm::vec2 m_Position;
		glm::vec2 m_Orientation;

		Scene* m_pScene{ nullptr };
		std::vector<BaseComponent*> m_pVecComponents;		
		std::vector<GameObject*> m_pChildren;
		std::string m_Tag; // TODO: Is a string really what I want for tagging ?
		bool m_IsInitialized;
	};
}
