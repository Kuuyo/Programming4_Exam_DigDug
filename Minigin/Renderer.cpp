#include "MiniginPCH.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "Box2DDebugRender.h"

namespace dae
{
	Renderer::Renderer(SDL_Window* window, const GameContext &gameContext)
	{
		m_pRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (m_pRenderer == nullptr)
		{
			LogErrorC(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
		}

		SDL_RenderSetScale(m_pRenderer, gameContext.GameSettings.GameScaleX, gameContext.GameSettings.GameScaleY);

#if defined(DEBUG) | defined(_DEBUG)	
		m_pBox2DDebugRenderer = new Box2DDebugRender(this);
		m_pBox2DDebugRenderer->SetFlags(b2Draw::e_shapeBit);
#endif
	}

	Renderer::~Renderer()
	{
		if (m_pRenderer != nullptr)
			SDL_DestroyRenderer(m_pRenderer);

		if (m_pBox2DDebugRenderer != nullptr)
			delete m_pBox2DDebugRenderer;
	}

	void Renderer::Render(const SceneContext &sceneContext, const std::vector<Texture2D*> &pTextures,
		float extrapolate) const
	{
		SDL_RenderClear(m_pRenderer);

		for (const auto pTexture : pTextures)
			RenderTexture(*pTexture, extrapolate);

#if defined(DEBUG) | defined(_DEBUG)
		sceneContext.Physics->DrawDebugData();

		SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
		SDL_RenderDrawPoints(m_pRenderer, m_DebugDrawPoints.data(), m_DebugDrawPoints.size());
		SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 0);
#endif

		SDL_RenderPresent(m_pRenderer);
	}

	void Renderer::AddDebugDrawPoint(const SDL_Point &point)
	{
		m_DebugDrawPoints.push_back(point);
	}

	void Renderer::RenderTexture(const Texture2D& texture, float) const
	{
		glm::vec2 pos = texture.GetPosition();
		RenderTexture(texture, pos.x, pos.y);
	}

	void Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
	{
		SDL_Rect src = texture.GetSourceRect();

		int width{ 0 }, height{ 0 };

		if (SDL_RectEmpty(&src))
		{
			SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &width, &height);
		}

		width = src.w > 0 ? src.w : width;
		height = src.h > 0 ? src.h : height;

		src.w = width;
		src.h = height;

		bool center = texture.GetIsCentered();
		SDL_Rect dst;
		dst.x = center ? static_cast<int>(x - (width*.5f)) : static_cast<int>(x);
		dst.y = center ? static_cast<int>(y - (height*.5f)) : static_cast<int>(y);
		dst.w = width;
		dst.h = height;

		SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst, 0.0, NULL,
			texture.GetOrientation());
	}

	void Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
	{
		SDL_Rect dst;
		dst.x = static_cast<int>(x);
		dst.y = static_cast<int>(y);
		dst.w = static_cast<int>(width);
		dst.h = static_cast<int>(height);
		SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
	}

}