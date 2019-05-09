#include "MiniginPCH.h"
#include "BodyComponent.h"

#include "GameObject.h"

dae::BodyComponent::BodyComponent(b2BodyType bodyType)
	: m_BodyType(bodyType)
{

}

dae::BodyComponent::~BodyComponent()
{
}

void dae::BodyComponent::Initialize(const GameContext &gameContext)
{
	b2BodyDef def;
	def.type = m_BodyType;
	def.angle = 0;
	auto pos = m_pParent->GetPosition();
	def.position.Set(pos.x, pos.y);
	m_pBody = gameContext.Physics->CreateBody(&def);

	for (auto fxtDef : m_FixtureDefVec)
	{
		m_pBody->CreateFixture(&*fxtDef);
	}
}

void dae::BodyComponent::Update(const GameContext &)
{
	auto pos = m_pBody->GetPosition();
	m_pParent->SetPosition(pos.x, pos.y, 0.f);
}

void dae::BodyComponent::SetBoxFixture(BoxFixtureDesc desc)
{
	auto shape = std::make_shared<b2PolygonShape>();
	shape->SetAsBox(desc.halfWidth, desc.halfHeight, desc.center, desc.angle);

	m_ShapeVec.push_back(shape);

	CreateFixtureDef(shape, desc);
}

void dae::BodyComponent::SetCircleFixture(CircleFixtureDesc desc)
{
	auto shape = std::make_shared<b2CircleShape>();
	shape->m_radius = desc.radius;

	m_ShapeVec.push_back(shape);

	CreateFixtureDef(shape, desc);
}

void dae::BodyComponent::SetPolygonFixture(PolygonFixtureDesc desc)
{
	auto shape = std::make_shared<b2PolygonShape>();
	shape->Set(desc.points.data(), static_cast<int32>(desc.points.size()));

	m_ShapeVec.push_back(shape);

	CreateFixtureDef(shape, desc);
}

void dae::BodyComponent::SetEdgeFixture(EdgeFixtureDesc desc)
{
	auto shape = std::make_shared<b2EdgeShape>();
	shape->Set(desc.start, desc.end);

	m_ShapeVec.push_back(shape);

	CreateFixtureDef(shape, desc);
}

void dae::BodyComponent::SetBoxFixtures(std::vector<BoxFixtureDesc> descVec)
{
	if (!descVec.empty())
	{
		for (auto fxt : descVec)
		{
			SetBoxFixture(fxt);
		}
	}
}

void dae::BodyComponent::SetCircleFixtures(std::vector<CircleFixtureDesc> descVec)
{
	if (!descVec.empty())
	{
		for (auto fxt : descVec)
		{
			SetCircleFixture(fxt);
		}
	}
}

void dae::BodyComponent::SetPolygonFixtures(std::vector<PolygonFixtureDesc> descVec)
{
	if (!descVec.empty())
	{
		for (auto fxt : descVec)
		{
			SetPolygonFixture(fxt);
		}
	}
}

void dae::BodyComponent::SetEdgeFixtures(std::vector<EdgeFixtureDesc> descVec)
{
	if (!descVec.empty())
	{
		for (auto fxt : descVec)
		{
			SetEdgeFixture(fxt);
		}
	}
}

void dae::BodyComponent::SetLinearVelocity(const b2Vec2 lVel)
{
	m_pBody->SetLinearVelocity(lVel);
}

void dae::BodyComponent::SetLinearVelocity(float lVelx, float lVely)
{
	m_pBody->SetLinearVelocity({lVelx, lVely});
}

void dae::BodyComponent::ApplyForce(float lVelx, float lVely)
{
	m_pBody->ApplyForce({ lVelx,lVely }, { 0,0 }, true);
}

void dae::BodyComponent::SetAngularVelocity(float aVel)
{
	m_pBody->SetAngularVelocity(aVel);
}

void dae::BodyComponent::SetLinearDamping(float d)
{
	m_pBody->SetLinearDamping(d);
}

bool dae::BodyComponent::HasContactList() const
{
	return m_pBody->GetContactList() != nullptr;
}

b2ContactEdge* dae::BodyComponent::GetContactList()
{
	return m_pBody->GetContactList();
}

void dae::BodyComponent::CreateFixtureDef(const std::shared_ptr<b2Shape> shape, const FixtureDesc desc)
{
	auto fixtureDef = std::make_shared<b2FixtureDef>();
	fixtureDef->shape = &*shape;
	fixtureDef->density = desc.density;
	fixtureDef->friction = desc.friction;
	fixtureDef->isSensor = desc.isSensor;
	fixtureDef->restitution = desc.restitution;
	fixtureDef->filter = desc.filter;
	fixtureDef->userData = this;

	m_FixtureDefVec.push_back(fixtureDef);
}
