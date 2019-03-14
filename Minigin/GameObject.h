#pragma once
#include <memory>

#include "Transform.h"
#include "Texture2D.h"
#include "SceneObject.h"

namespace dae
{
	class BaseComponent;
	class TransformComponent;

	class GameObject : public SceneObject
	{
	public:
		GameObject();
		virtual ~GameObject();

		void Initialize() override;
		void Update() override;
		void Render() const override;

		void AddComponent(BaseComponent* component);

		void SetPosition(float x, float y);
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
