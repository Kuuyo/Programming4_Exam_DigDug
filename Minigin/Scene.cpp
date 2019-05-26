#include "MiniginPCH.h"
#include "Scene.h"

#include "GameObject.h"
#include "Renderer.h"
#include "Texture2D.h"

#include "BodyComponent.h"
#include "Box2DDebugRender.h"
#include "HelperFunctions.h"

#include <Box2D.h>

namespace dae
{
	Scene::Scene(const std::string& name) : m_Name(name)
	{
		m_pTextureVec.push_back({});
	}

	Scene::~Scene()
	{
		Cleanup();
	}

	void Scene::RootInitialize(const GameContext &gameContext)
	{
		m_SceneContext.GameContext = &gameContext;
		m_SceneContext.Physics = new b2World({ 0.f,0.f }); // TODO: GRAVITY HARDCODED
		m_SceneContext.Physics->SetContactListener(this);

#if defined(DEBUG) | defined(_DEBUG)	
		m_SceneContext.Physics->SetDebugDraw(gameContext.Renderer->GetBox2DDebugRenderer());
#endif

		Initialize(m_SceneContext);

		for (auto gameObject : m_Objects)
		{
			gameObject->Initialize(m_SceneContext);
		}

		m_Reset = false;
	}

	void Scene::RootUpdate()
	{
		Update(m_SceneContext);

		for (auto gameObject : m_Objects)
		{
			gameObject->Update(m_SceneContext);
		}
	}

	void Scene::RootLateUpdate()
	{
		LateUpdate(m_SceneContext);

		for (auto gameObject : m_Objects)
		{
			gameObject->LateUpdate(m_SceneContext);
		}
	}

	void Scene::DestroyUpdate()
	{
		// TODO: Maybe find a prettier way to do this
		for (auto gO : m_ObjectsToRemove)
		{
			auto it = std::find(m_Objects.begin(), m_Objects.end(), gO);
			if (it != m_Objects.end())
			{
				delete (*it);
				m_Objects.erase(it);
			}
		}

		m_ObjectsToRemove.clear();

		for (auto tX : m_pTexturesToRemove)
		{
			for (auto& pSortingLayer : m_pTextureVec)
			{
				EraseRemoveFromVector(pSortingLayer, tX);
			}
		}

		m_pTexturesToRemove.clear();

		if (m_Reset)
		{
			Cleanup();
			RootInitialize(*m_SceneContext.GameContext);
		}
	}

	void Scene::Render(Renderer* pRenderer, float extrapolate) const
	{
		// TODO: Remember unreferenced parameter "extrapolate" in Scene::Render
		pRenderer->Render(m_SceneContext, m_pTextureVec, m_DebugDrawPoints, extrapolate);
	}

	void Scene::FixedUpdate(float msPerFrame)
	{
		m_SceneContext.Physics->Step(msPerFrame, 8, 3);
		ContactUpdate();
	}

	void Scene::BeginContact(b2Contact* contact)
	{
		auto goA = static_cast<BodyComponent*>(contact->GetFixtureA()->GetUserData())->GetGameObject();
		auto goB = static_cast<BodyComponent*>(contact->GetFixtureB()->GetUserData())->GetGameObject();

		OnCollisionEnter({ contact, goB }, goA);
		OnCollisionEnter({ contact, goA }, goB);

		m_pActiveCollisionMap.insert({ contact,{ goA,goB } });
	}

	void Scene::ContactUpdate()
	{
		for (auto col : m_pActiveCollisionMap)
		{
			OnCollisionStay({ col.first, col.second.second }, col.second.first);
			OnCollisionStay({ col.first, col.second.first }, col.second.second);
		}
	}

	void Scene::EndContact(b2Contact* contact)
	{
		auto goA = static_cast<BodyComponent*>(contact->GetFixtureA()->GetUserData())->GetGameObject();
		auto goB = static_cast<BodyComponent*>(contact->GetFixtureB()->GetUserData())->GetGameObject();

		OnCollisionExit({ contact, goB }, goA);
		OnCollisionExit({ contact, goA }, goB);

		m_pActiveCollisionMap.erase(contact);
	}

	void Scene::Cleanup()
	{
		m_pActiveCollisionMap.clear();

		for (auto gameObject : m_Objects)
		{
			if (gameObject != nullptr)
				delete gameObject;
		}

		m_Objects.clear();
		m_pTexturesToRemove.clear();
		m_pTextureVec.clear();

		m_DebugDrawPoints.clear();

		delete m_SceneContext.Physics;
	}

	void Scene::AddGameObject(GameObject* object)
	{
		object->SetScene(this);
		m_Objects.push_back(object);
	}

	void Scene::RemoveGameObject(GameObject* object)
	{
		m_ObjectsToRemove.push_back(object);
	}

	void Scene::AddTexture(Texture2D* pTexture, unsigned int sortingLayer)
	{
		if (sortingLayer >= m_pTextureVec.size())
		{
			const unsigned int layersToAdd = (unsigned int(m_pTextureVec.size()) - sortingLayer - 1) * -1;

			for (size_t i = 0; i < layersToAdd; ++i)
			{
				m_pTextureVec.push_back({});
			}
		}

		m_pTextureVec[sortingLayer].push_back(pTexture);
	}

	void Scene::RemoveTexture(Texture2D* pTexture)
	{
		m_pTexturesToRemove.push_back(pTexture);
	}

	void Scene::AddDebugDrawPoint(const SDL_Point &point)
	{
		m_DebugDrawPoints.push_back(point);
	}

	void Scene::AddDebugDrawPointVec(const std::vector<SDL_Point>& point)
	{
		m_DebugDrawPoints.insert(m_DebugDrawPoints.end(), point.begin(), point.end());
	}

	void Scene::ResetScene()
	{
		m_Reset = true;
	}

	const std::string Scene::GetName() const
	{
		return m_Name;
	}
}