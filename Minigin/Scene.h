#pragma once
#include "Observer.h"
#include <map>
#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include "GameContext.h"
#include "Structs.h"

namespace dae
{
	class GameObject;
	class Texture2D;
	class Renderer;

	struct Contact
	{
		Contact(b2Contact* b2Contact, GameObject* other)
			: B2Contact(b2Contact)
			, Other(other)
		{}

		b2Contact* B2Contact;
		GameObject* Other;
	};

	class Scene : public b2ContactListener
	{
	public:
		explicit Scene(const std::string& name);

		void AddGameObject(GameObject* object);
		void RemoveGameObject(GameObject* object);

		void AddTexture(Texture2D* pTexture);
		void RemoveTexture(Texture2D* pTexture);

		const std::string GetName() const;
		SceneContext GetSceneContext() const { return m_SceneContext; }

		void AddDebugDrawPoint(const SDL_Point &point);
		void AddDebugDrawPointVec(const std::vector<SDL_Point> &point);

		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	protected:
		// Did not make these pure virtual on purpose, so making quick and dirty scenes is still possible
		// without having to override every single function
		virtual void Initialize(const SceneContext &) {}
		virtual void Update(const SceneContext &) {}
		virtual void LateUpdate(const SceneContext &) {}
		virtual void OnCollisionEnter(const Contact &, GameObject* ) {}
		virtual void OnCollisionStay(const Contact &, GameObject* ) {}
		virtual void OnCollisionExit(const Contact &, GameObject* ) {}

	private:
		friend class SceneManager;

		void RootInitialize(const GameContext &gameContext);
		void RootUpdate();
		void RootLateUpdate();
		void DestroyUpdate();

		void Render(Renderer* pRenderer, float extrapolate) const;

		void FixedUpdate(float msPerFrame);
		void BeginContact(b2Contact* contact) override;
		void ContactUpdate();
		void EndContact(b2Contact* contact) override;

		SceneContext m_SceneContext;
		std::map<b2Contact*, std::pair<GameObject*, GameObject*>> m_pActiveCollisionMap;
		std::string m_Name{};
		std::vector<GameObject*> m_Objects{};
		std::vector<GameObject*> m_ObjectsToRemove{};
		std::vector<Texture2D*> m_pTextureVec{};
		std::vector<Texture2D*> m_pTexturesToRemove{};
		// TODO: Fix this vector of pointers bullshit

		std::vector<SDL_Point> m_DebugDrawPoints{};
	};

}
