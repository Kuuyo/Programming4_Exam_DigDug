#include "MiniginPCH.h"
#include "Box2DRaycastCallback.h"

namespace dae
{
	Box2DRaycastCallback::Box2DRaycastCallback()
	{
	}


	Box2DRaycastCallback::~Box2DRaycastCallback()
	{
	}

	float32 Box2DRaycastCallback::ReportFixture(b2Fixture* fixture, const b2Vec2 &,
		const b2Vec2 &, float32 fraction)
	{
		//TODO: Expand this
		m_pFixtues.push_back(fixture);

		return fraction;
	}
}