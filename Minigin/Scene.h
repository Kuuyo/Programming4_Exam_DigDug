#pragma once

namespace dae
{
	class GameObject;
	class Texture2D;
	class Renderer;
	struct GameContext;

	class Scene final
	{
	public:
		explicit Scene(const std::string& name);

		void Initialize(const GameContext &gameContext);
		void Update(const GameContext &gameContext);
		void Render(Renderer* pRenderer, float extrapolate) const;

		void AddGameObject(const std::shared_ptr<GameObject>& object);
		void AddTexture(Texture2D* &pTexture);

		const std::string GetName();

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private:
		std::string m_Name{};
		std::vector<std::shared_ptr<GameObject>> m_Objects{};
		std::vector<Texture2D*> m_pTextureVec{};
	};

}
