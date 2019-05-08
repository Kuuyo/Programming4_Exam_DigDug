#pragma once
#include <Box2D/Box2D.h>

namespace dae
{
	class Box2DDebugRender : public b2Draw
	{
	public:
		Box2DDebugRender(Renderer* pRenderer);
		virtual ~Box2DDebugRender() = default;

		void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color &color) override;
		void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color &color) override;
		void DrawCircle(const b2Vec2 &center, float32 radius, const b2Color &color) override;
		void DrawSolidCircle(const b2Vec2 &center, float32 radius, const b2Vec2 &axis, const b2Color &color) override;
		void DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color) override;
		void DrawTransform(const b2Transform &xf) override;
		void DrawPoint(const b2Vec2 &p, float32 size, const b2Color &color) override;

	private:
		SDL_Renderer* m_pRenderer;

		SDL_Point ConvertB2Vec2ToSDLPoint(const b2Vec2 &vertex);
		std::vector<SDL_Point> ConvertB2Vec2ToSDLPoint(const b2Vec2* vertices, int32 vertexCount);
		void SetRenderColor(SDL_Renderer* renderer, const b2Color &color);

		Box2DDebugRender(const Box2DDebugRender&) = delete;
		Box2DDebugRender& operator=(const Box2DDebugRender&) = delete;
	};
}

