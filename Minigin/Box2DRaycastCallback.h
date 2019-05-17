#pragma once
#include <Box2D/Dynamics/b2WorldCallbacks.h>

namespace dae
{
	class Box2DRaycastCallback final : public b2RayCastCallback
	{
	public:
		Box2DRaycastCallback();
		~Box2DRaycastCallback();

		float32 ReportFixture(b2Fixture* fixture, const b2Vec2 &point,
			const b2Vec2 &normal, float32 fraction) override;

		std::vector<b2Fixture*> GetFixtures() const { return m_pFixtues; }

	private:
		std::vector<b2Fixture*> m_pFixtues;
	};
}
