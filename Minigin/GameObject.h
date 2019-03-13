#pragma once
#include <memory>

#include "Transform.h"
#include "Texture2D.h"
#include "SceneObject.h"

namespace dae
{
	class BaseComponent;

	class GameObject : public SceneObject
	{
	public:
		GameObject() = default;
		virtual ~GameObject();

		void Initialize() override;
		void Update() override;
		void Render() const override;

		void AddComponent(BaseComponent* component);

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector<BaseComponent*> m_pVecComponents;
		Transform mTransform;
		std::shared_ptr<Texture2D> mTexture;
	};
}
