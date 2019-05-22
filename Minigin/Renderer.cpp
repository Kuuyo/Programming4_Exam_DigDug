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
		const std::vector<SDL_Point> &debugDraw, float extrapolate) const
	{
		SDL_RenderClear(m_pRenderer);

		for (const auto pTexture : pTextures)
			RenderTexture(*pTexture, extrapolate);

#if defined(DEBUG) | defined(_DEBUG)
		sceneContext.Physics->DrawDebugData();

		SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
		SDL_RenderDrawPoints(m_pRenderer, debugDraw.data(), int(debugDraw.size()));
		SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 0);
#else
		(sceneContext);
		(debugDraw);
#endif

		SDL_RenderPresent(m_pRenderer);
	}

	void Renderer::RenderTexture(const Texture2D& texture, float) const
	{
		glm::vec2 pos = texture.GetPosition();
		RenderTexture(texture, pos.x, pos.y);
	}

	void Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
	{
		SDL_Rect src = texture.GetSourceRect();

		bool center = texture.GetIsCentered();
		SDL_Rect dst;
		dst.x = center ? static_cast<int>(x - (src.w*.5f)) : static_cast<int>(x);
		dst.y = center ? static_cast<int>(y - (src.h*.5f)) : static_cast<int>(y);
		dst.w = src.w;
		dst.h = src.h;

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