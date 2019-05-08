#include "MiniginPCH.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "Box2DDebugRender.h"

dae::Renderer::Renderer(SDL_Window* window, b2World* pPhysics)
{
	m_pRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_pRenderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	m_pPhysics = pPhysics;

#if defined(DEBUG) | defined(_DEBUG)	
	m_pBox2DDebugRenderer = new Box2DDebugRender(this);
	m_pPhysics->SetDebugDraw(m_pBox2DDebugRenderer);
	m_pBox2DDebugRenderer->SetFlags(b2Draw::e_shapeBit);
	m_pBox2DDebugRenderer->AppendFlags(b2Draw::e_centerOfMassBit);
#endif
}

dae::Renderer::~Renderer()
{
	if (m_pRenderer != nullptr)
		SDL_DestroyRenderer(m_pRenderer);

	if (m_pBox2DDebugRenderer != nullptr)
		delete m_pBox2DDebugRenderer;
}

void dae::Renderer::Render(const std::vector<Texture2D*> &pTextures, float extrapolate) const
{
	SDL_RenderClear(m_pRenderer);

	for (const auto pTexture : pTextures)
		RenderTexture(*pTexture, extrapolate);

#if defined(DEBUG) | defined(_DEBUG)
	m_pPhysics->DrawDebugData();
#endif
	
	SDL_RenderPresent(m_pRenderer);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, float ) const
{
	glm::vec2 pos = texture.GetPosition();
	RenderTexture(texture, pos.x, pos.y);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}
