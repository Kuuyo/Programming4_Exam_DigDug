#include "MiniginPCH.h"
#include "Scene.h"

#include "GameObject.h"
#include "Renderer.h"
#include "Texture2D.h"

#include "BodyComponent.h"

#include <Box2D.h>

dae::Scene::Scene(const std::string& name) : m_Name(name) {}

dae::Scene::~Scene()
{
}

void dae::Scene::RootInitialize(const GameContext &gameContext)
{
	gameContext.Physics->SetContactListener(this);

	Initialize(gameContext);

	for (auto gameObject : m_Objects)
	{
		gameObject->Initialize(gameContext);
	}
}

void dae::Scene::RootUpdate(const GameContext &gameContext)
{
	Update(gameContext);

	for(auto gameObject : m_Objects)
	{
		gameObject->Update(gameContext);
	}
}

void dae::Scene::Render(Renderer* pRenderer, float extrapolate) const
{
	// TODO: Remember unreferenced parameter "extrapolate" in Scene::Render
	pRenderer->Render(m_pTextureVec, extrapolate);
}

void dae::Scene::BeginContact(b2Contact* contact)
{
	auto go = static_cast<BodyComponent*>(contact->GetFixtureA()->GetUserData())->GetGameObject();
	OnCollisionEnter(contact, go);
	go = static_cast<BodyComponent*>(contact->GetFixtureB()->GetUserData())->GetGameObject();
	OnCollisionEnter(contact, go);
}

void dae::Scene::EndContact(b2Contact* contact)
{
	auto go = static_cast<BodyComponent*>(contact->GetFixtureA()->GetUserData())->GetGameObject();
	OnCollisionExit(contact, go);
	go = static_cast<BodyComponent*>(contact->GetFixtureB()->GetUserData())->GetGameObject();
	OnCollisionExit(contact, go);
}

void dae::Scene::AddGameObject(const std::shared_ptr<GameObject>& object)
{
	object->SetScene(this);
	m_Objects.push_back(object);
}

void dae::Scene::AddTexture(Texture2D* &pTexture)
{
	m_pTextureVec.push_back(pTexture);
}

const std::string dae::Scene::GetName() const
{
	return m_Name;
}