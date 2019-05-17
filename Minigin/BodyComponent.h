#pragma once
#include <Box2D.h>
#include "BaseComponent.h"

namespace dae
{
	class BodyComponent final : public BaseComponent
	{
	private:
		struct FixtureDesc
		{
			FixtureDesc()
				: friction(.2f)
				, restitution(0.f)
				, density(0.f)
				, filter(b2Filter())
				, isSensor(false)
			{}

			float friction;
			float restitution;
			float density;
			b2Filter filter;
			bool isSensor;
		};

	public:
		struct BoxFixtureDesc : FixtureDesc
		{
			BoxFixtureDesc()
				: halfWidth(1.f)
				, halfHeight(1.f)
				, center({ 0.f,0.f })
				, angle(0.f)
			{}

			float halfWidth;
			float halfHeight;
			b2Vec2 center;
			float angle;
		};

		struct CircleFixtureDesc : FixtureDesc
		{
			CircleFixtureDesc()
				: radius(1.f)
			{}

			float radius;
		};

		struct PolygonFixtureDesc : FixtureDesc
		{
			std::vector<b2Vec2> points;
		};

		struct EdgeFixtureDesc : FixtureDesc
		{
			EdgeFixtureDesc()
				: start(0.f, 0.f)
				, end(1.f, 1.f)
			{}

			b2Vec2 start;
			b2Vec2 end;
		};

		BodyComponent(b2BodyType bodyType = b2BodyType::b2_dynamicBody);

		void SetBoxFixture(BoxFixtureDesc desc);
		void SetCircleFixture(CircleFixtureDesc desc);
		void SetPolygonFixture(PolygonFixtureDesc desc);
		void SetEdgeFixture(EdgeFixtureDesc desc);

		void SetBoxFixtures(std::vector<BoxFixtureDesc> descVec);
		void SetCircleFixtures(std::vector<CircleFixtureDesc> descVec);
		void SetPolygonFixtures(std::vector<PolygonFixtureDesc> descVec);
		void SetEdgeFixtures(std::vector<EdgeFixtureDesc> descVec);

		void SetLinearVelocity(const b2Vec2 lVel);// TODO: Fix the mixing between b2Vec2 and glm::vec2
		void SetLinearVelocity(float lVelx, float lVely);
		void ApplyForce(float lVelx, float lVely);
		b2Vec2 GetLinearVelocity() const { return m_pBody->GetLinearVelocity(); }
		void SetAngularVelocity(float aVel);

		void MoveToTarget(const glm::vec2 &target, float speed);
		void SetPosition(float x, float y);
		void SetPosition(const glm::vec2 &pos);

		void SetLinearDamping(float d);

		bool HasContactList() const;
		b2ContactEdge* GetContactList();

		bool Raycast(b2RayCastOutput* output, const b2RayCastInput &input, int32 childIndex) const;
		bool Raycast(b2RayCastOutput* output, const b2Vec2 &direction, float multiplier, int32 childIndex) const;

		BodyComponent(const BodyComponent &) = delete;
		BodyComponent(BodyComponent &&) = delete;
		BodyComponent & operator= (const BodyComponent &) = delete;
		BodyComponent & operator= (const BodyComponent &&) = delete;

	protected:
		void Initialize(const GameContext &gameContext) override;
		void Update(const GameContext &gameContext) override;
		void LateUpdate(const GameContext &) override {}

		virtual ~BodyComponent();

	private:
		void CreateFixtureDef(const std::shared_ptr<b2Shape> shape, const FixtureDesc desc);

		b2Body* m_pBody{ nullptr };
		b2World* m_pPhysics{ nullptr };
		b2BodyType m_BodyType;
		std::vector<std::shared_ptr<b2FixtureDef>> m_FixtureDefVec;
		std::vector<std::shared_ptr<b2Shape>> m_ShapeVec;
	};
}