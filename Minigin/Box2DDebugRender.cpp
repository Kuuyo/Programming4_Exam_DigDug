#include "MiniginPCH.h"

#include "Box2DDebugRender.h"
#include <SDL.h>
#include "Renderer.h"

#include <glm/gtc/constants.hpp>

dae::Box2DDebugRender::Box2DDebugRender(Renderer* pRenderer)
{
	m_pRenderer = pRenderer->GetSDLRenderer();
}

SDL_Point dae::Box2DDebugRender::ConvertB2Vec2ToSDLPoint(const b2Vec2 &vertex)
{
	SDL_Point point;

	point.x = static_cast<int>(vertex.x);
	point.y = static_cast<int>(vertex.y);

	return point;
}

std::vector<SDL_Point> dae::Box2DDebugRender::ConvertB2Vec2ToSDLPoint(const b2Vec2* vertices, int32 vertexCount)
{
	std::vector<b2Vec2> verticesVec;
	verticesVec.reserve(vertexCount);

	for (int32 i = 0; i < vertexCount; ++i)
	{
		verticesVec.push_back(vertices[i]);
	}

	std::vector<SDL_Point> points;
	points.reserve(vertexCount);

	for (int32 i = 0; i < vertexCount; ++i)
	{
		points.push_back(ConvertB2Vec2ToSDLPoint(verticesVec.at(i)));
	}

	return points;
}

void dae::Box2DDebugRender::SetRenderColor(SDL_Renderer* renderer, const b2Color &color)
{
	Uint8 r, g, b, a;
	r = static_cast<Uint8>(color.r * 255);
	g = static_cast<Uint8>(color.g * 255);
	b = static_cast<Uint8>(color.b * 255);
	a = static_cast<Uint8>(color.a * 255);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void dae::Box2DDebugRender::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color &color)
{
	auto points = ConvertB2Vec2ToSDLPoint(vertices, vertexCount);
	points.push_back(points.at(0));

	SetRenderColor(m_pRenderer, color);
	SDL_RenderDrawLines(m_pRenderer, points.data(), vertexCount+1);
}

void dae::Box2DDebugRender::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color &color)
{
	auto points = ConvertB2Vec2ToSDLPoint(vertices, vertexCount);
	points.push_back(points.at(0));

	SetRenderColor(m_pRenderer, color);
	SDL_RenderDrawLines(m_pRenderer, points.data(), vertexCount+1);
}

void dae::Box2DDebugRender::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	SetRenderColor(m_pRenderer, color);

	float two_Pi = glm::two_pi<float>();
	UINT sides = static_cast<UINT>(two_Pi * radius / 2);

	float offset = two_Pi / static_cast<float>(sides),
		angle = offset;

	glm::vec2 start, end, centerP;
	end.x = radius;
	end.y = 0.0f;
	centerP.x = center.x;
	centerP.y = center.y;
	end = end + centerP;

	for (UINT i = 0; i < sides; ++i)
	{
		start = end;
		end.x = cos(angle) * radius;
		end.y = sin(angle) * radius;
		end = end + centerP;
		angle += offset;
		SDL_RenderDrawLine(m_pRenderer, static_cast<int>(start.x), static_cast<int>(start.y), static_cast<int>(end.x), static_cast<int>(end.y));
	}
}

void dae::Box2DDebugRender::DrawSolidCircle(const b2Vec2 &center, float32 radius, const b2Vec2&, const b2Color &color)
{
	SetRenderColor(m_pRenderer, color);

	float two_Pi = glm::two_pi<float>();
	UINT sides = static_cast<UINT>(two_Pi * radius / 2);

	float offset = two_Pi / static_cast<float>(sides),
		angle = offset;

	glm::vec2 start, end, centerP;
	end.x = radius;
	end.y = 0.0f;
	centerP.x = center.x;
	centerP.y = center.y;
	end = end + centerP;

	for (UINT i = 0; i < sides ; ++i)
	{
		start = end;
		end.x = cos(angle) * radius;
		end.y = sin(angle) * radius;
		end = end + centerP;
		angle += offset;
		SDL_RenderDrawLine(m_pRenderer, static_cast<int>(start.x), static_cast<int>(start.y), static_cast<int>(end.x), static_cast<int>(end.y));
	}
}

void dae::Box2DDebugRender::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color)
{
	SDL_Point start = ConvertB2Vec2ToSDLPoint(p1);
	SDL_Point end = ConvertB2Vec2ToSDLPoint(p2);

	SetRenderColor(m_pRenderer, color);

	SDL_RenderDrawLine(m_pRenderer, start.x, start.y, end.x, end.y);
}

void dae::Box2DDebugRender::DrawTransform(const b2Transform &)
{

}

void dae::Box2DDebugRender::DrawPoint(const b2Vec2 &p, float32, const b2Color &color)
{
	SDL_Point point = ConvertB2Vec2ToSDLPoint(p);

	SetRenderColor(m_pRenderer, color);

	SDL_RenderDrawPoint(m_pRenderer, point.x, point.y);
}
