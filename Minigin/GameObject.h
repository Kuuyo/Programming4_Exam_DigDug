#pragma once

#pragma warning (push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning (pop)

// TODO: Add possibility to add GameObject as a child to a GameObject ?

namespace dae
{
	class BaseComponent;
	class TransformComponent;

	class GameObject final
	{
	public:
		GameObject();
		~GameObject();

		void Initialize();
		void Update();
		void Render() const;

		void AddComponent(BaseComponent* component);

		void SetPosition(float x = 0, float y = 0, float z = 0);
		const glm::vec3& GetPosition() const;

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector<BaseComponent*> m_pVecComponents;
		TransformComponent* m_pTransform;
	};
}
