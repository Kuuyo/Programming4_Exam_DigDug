#pragma once
#include "ResourceManager.h"

namespace dae
{
	class TransformComponent;

	class Texture2D final
	{
	public:
		Texture2D(SDL_Texture* pTexture, TransformComponent* pTransform, const SDL_Rect &sourceRect, bool isCentered);
		~Texture2D();

		SDL_Texture* GetSDLTexture() const;
		SDL_Rect GetSourceRect() const;

		glm::vec2 GetPosition() const;

		bool GetIsCentered() const;

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;
	private:
		SDL_Texture* m_pTexture;
		TransformComponent* m_pTransform;
		SDL_Rect m_SourceRect;
		bool m_IsCentered;

		friend void ResourceManager::CreateTextTexture(const SDL_Color &color, const Font* pFont,
			const std::string &text, Texture2D* &pTexture, TransformComponent* pTransform, bool isCentered);
	};
}
