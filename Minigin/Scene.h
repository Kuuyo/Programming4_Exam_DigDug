#pragma once
#include "Observer.h"

namespace dae
{
	class GameObject;
	class Texture2D;
	class Renderer;
	struct GameContext;

	class Scene
	{
	public:
		explicit Scene(const std::string& name);

		void AddGameObject(const std::shared_ptr<GameObject>& object);
		void AddTexture(Texture2D* &pTexture);

		const std::string GetName() const;

		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	protected:
		virtual void Initialize(const GameContext &) {}
		virtual void Update(const GameContext &) {}

	private:
		friend class SceneManager;

		void RootInitialize(const GameContext &gameContext);
		void RootUpdate(const GameContext &gameContext);
		void Render(Renderer* pRenderer, float extrapolate) const;

		std::string m_Name{};
		std::vector<std::shared_ptr<GameObject>> m_Objects{};
		std::vector<Texture2D*> m_pTextureVec{};
	};

}
