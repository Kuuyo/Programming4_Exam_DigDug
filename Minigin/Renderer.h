#pragma once
struct SDL_Window;
struct SDL_Renderer;

namespace dae
{
	class Texture2D;
	class Box2DDebugRender;
	class Renderer final
	{		
	public:
		Renderer(SDL_Window* window, b2World* pPhysics);		
		~Renderer();

		void Render(const std::vector<Texture2D*> &pTextures, float extrapolate) const;

		SDL_Renderer* GetSDLRenderer() const { return m_pRenderer; }

	private:
		void RenderTexture(const Texture2D& texture, float extrapolate) const;
		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		b2World* m_pPhysics{ nullptr };
		SDL_Renderer* m_pRenderer{ nullptr };
		Box2DDebugRender* m_pBox2DDebugRenderer{ nullptr };
	};
}

