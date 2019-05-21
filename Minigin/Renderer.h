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
		Renderer(SDL_Window* window, const GameContext &gameContext);		
		~Renderer();

		void Render(const SceneContext &sceneContext, const std::vector<Texture2D*> &pTextures,
			const std::vector<SDL_Point> &debugDraw, float extrapolate) const;

		SDL_Renderer* GetSDLRenderer() const { return m_pRenderer; }
		Box2DDebugRender* GetBox2DDebugRenderer() const { return m_pBox2DDebugRenderer; }

	private:
		void RenderTexture(const Texture2D& texture, float extrapolate) const;
		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		SDL_Renderer* m_pRenderer{ nullptr };
		Box2DDebugRender* m_pBox2DDebugRenderer{ nullptr };
	};
}

