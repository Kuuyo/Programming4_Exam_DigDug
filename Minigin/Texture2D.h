#pragma once
#include "ResourceManager.h"

namespace dae
{
	class GameObject;

	class Texture2D final
	{
	public:
		Texture2D(SDL_Texture* pTexture, GameObject* pTransform, const SDL_Rect &sourceRect, bool isCentered);
		~Texture2D();

		SDL_Texture* GetSDLTexture() const;
		SDL_Rect GetSourceRect() const;

		void SetSourceRect(const SDL_Rect &src);

		glm::vec2 GetPosition() const;
		SDL_RendererFlip GetOrientation() const;

		void SetIsCentered(bool isCentered);
		bool GetIsCentered() const;

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;
	private:
		SDL_Texture* m_pTexture;
		GameObject* m_pTransform;
		SDL_Rect m_SourceRect;
		bool m_IsCentered;

		friend void ResourceManager::CreateTextTexture(const SDL_Color &color, const Font* pFont,
			const std::string &text, Texture2D* &pTexture, GameObject* pTransform, bool isCentered);
	};
}
