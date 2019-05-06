#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;

	class Scene final
	{
	public:
		explicit Scene(const std::string& name);

		void Add(const std::shared_ptr<GameObject>& object);

		const std::string GetName();

		void Initialize();
		void Update();
		void Render(float extrapolate) const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		std::string m_Name{};
		std::vector<std::shared_ptr<GameObject>> m_Objects{};

		static unsigned int idCounter; 
	};

}
