#include "MiniginPCH.h"
#include "BodyComponent.h"

#include "GameObject.h"

namespace dae
{
	BodyComponent::BodyComponent(b2BodyType bodyType)
		: m_BodyType(bodyType)
	{

	}

	BodyComponent::~BodyComponent()
	{
		if (m_pPhysics->GetBodyCount() > 0)
			m_pPhysics->DestroyBody(m_pBody);
	}

	void BodyComponent::Initialize(const SceneContext &sceneContext)
	{
		m_pPhysics = sceneContext.Physics;

		b2BodyDef def;
		def.type = m_BodyType;
		def.angle = 0;
		auto pos = m_pParent->GetPosition();
		def.position.Set(pos.x, pos.y);
		def.userData = this;
		m_pBody = sceneContext.Physics->CreateBody(&def);

		for (auto fxtDef : m_FixtureDefVec)
		{
			m_pBody->CreateFixture(&*fxtDef);
		}
	}

	void BodyComponent::Update(const SceneContext &)
	{
		auto pos = m_pBody->GetPosition();
		m_pParent->SetPosition(pos.x, pos.y);
	}

	void BodyComponent::SetBoxFixture(BoxFixtureDesc desc)
	{
		auto shape = std::make_shared<b2PolygonShape>();
		shape->SetAsBox(desc.halfWidth, desc.halfHeight, desc.center, desc.angle);

		m_ShapeVec.push_back(shape);

		CreateFixtureDef(shape, desc);
	}

	void BodyComponent::SetCircleFixture(CircleFixtureDesc desc)
	{
		auto shape = std::make_shared<b2CircleShape>();
		shape->m_radius = desc.radius;

		m_ShapeVec.push_back(shape);

		CreateFixtureDef(shape, desc);
	}

	void BodyComponent::SetPolygonFixture(PolygonFixtureDesc desc)
	{
		auto shape = std::make_shared<b2PolygonShape>();
		shape->Set(desc.points.data(), static_cast<int32>(desc.points.size()));

		m_ShapeVec.push_back(shape);

		CreateFixtureDef(shape, desc);
	}

	void BodyComponent::SetEdgeFixture(EdgeFixtureDesc desc)
	{
		auto shape = std::make_shared<b2EdgeShape>();
		shape->Set(desc.start, desc.end);

		m_ShapeVec.push_back(shape);

		CreateFixtureDef(shape, desc);
	}

	void BodyComponent::SetBoxFixtures(std::vector<BoxFixtureDesc> descVec)
	{
		if (!descVec.empty())
		{
			for (auto fxt : descVec)
			{
				SetBoxFixture(fxt);
			}
		}
	}

	void BodyComponent::SetCircleFixtures(std::vector<CircleFixtureDesc> descVec)
	{
		if (!descVec.empty())
		{
			for (auto fxt : descVec)
			{
				SetCircleFixture(fxt);
			}
		}
	}

	void BodyComponent::SetPolygonFixtures(std::vector<PolygonFixtureDesc> descVec)
	{
		if (!descVec.empty())
		{
			for (auto fxt : descVec)
			{
				SetPolygonFixture(fxt);
			}
		}
	}

	void BodyComponent::SetEdgeFixtures(std::vector<EdgeFixtureDesc> descVec)
	{
		if (!descVec.empty())
		{
			for (auto fxt : descVec)
			{
				SetEdgeFixture(fxt);
			}
		}
	}

	void BodyComponent::SetLinearVelocity(const b2Vec2 lVel)
	{
		m_pBody->SetLinearVelocity(lVel);
	}

	void BodyComponent::SetLinearVelocity(float lVelx, float lVely)
	{
		m_pBody->SetLinearVelocity({ lVelx, lVely });
	}

	void BodyComponent::ApplyForce(float lVelx, float lVely)
	{
		m_pBody->ApplyForce({ lVelx,lVely }, { 0,0 }, true);
	}

	void BodyComponent::SetAngularVelocity(float aVel)
	{
		m_pBody->SetAngularVelocity(aVel);
	}

	void BodyComponent::MoveToTarget(const glm::vec2 &target, float speed)
	{
		auto vector = target - m_pParent->GetPosition();
		auto direction = (glm::length(vector) != 0.f) ? glm::normalize(vector) : vector;
		direction *= speed;

		// TODO: Check wheter the body would have passed the point between frames !!!

		SetLinearVelocity(direction.x, direction.y);
	}

	void BodyComponent::SetPosition(float x, float y)
	{
		m_pBody->SetTransform({ x,y }, m_pBody->GetAngle());
	}

	void BodyComponent::SetPosition(const glm::vec2 &pos)
	{
		SetPosition(pos.x, pos.y);
	}

	void BodyComponent::SetType(b2BodyType bodyType)
	{
		m_pBody->SetType(bodyType);
	}

	void BodyComponent::SetLinearDamping(float d)
	{
		m_pBody->SetLinearDamping(d);
	}

	bool BodyComponent::HasContactList() const
	{
		return m_pBody->GetContactList() != nullptr;
	}

	b2ContactEdge* BodyComponent::GetContactList()
	{
		return m_pBody->GetContactList();
	}

	bool BodyComponent::Raycast(b2RayCastOutput* output, const b2RayCastInput &input, int32 childIndex) const
	{
		// TODO: What if there's multiple fixtures ?
		return m_pBody->GetFixtureList()->RayCast(output, input, childIndex);
	}

	bool BodyComponent::Raycast(b2RayCastOutput* output, const b2Vec2 &direction, float multiplier, int32 childIndex) const
	{
		const auto pos = m_pParent->GetPosition();

		b2RayCastInput input;
		input.maxFraction = multiplier;
		input.p1 = { pos.x,pos.y };
		input.p2 = { pos.x + direction.x,pos.y + direction.y };

		return m_pBody->GetFixtureList()->RayCast(output, input, childIndex);
	}

	void BodyComponent::CreateFixtureDef(const std::shared_ptr<b2Shape> shape, const FixtureDesc desc)
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
}