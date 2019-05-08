#pragma once
#include "ResourceManager.h"

namespace dae
{
	class Texture2D final
	{
	public:
		explicit Texture2D(SDL_Texture* texture, const glm::vec2 &pos, const SDL_Rect &sourceRect, bool isCentered);
		~Texture2D();

		SDL_Texture* GetSDLTexture() const;
		SDL_Rect GetSourceRect() const;

		glm::vec2 GetPosition() const;
		void SetPosition(float x, float y);

		bool GetIsCentered() const;

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;
	private:
		SDL_Texture* m_pTexture;
		glm::vec2 m_Position;
		SDL_Rect m_SourceRect;
		bool m_IsCentered;

		friend void ResourceManager::CreateTextTexture(const SDL_Color &color, const Font* pFont, const std::string &text, Texture2D* &pTexture, const glm::vec2 &pos);
	};
}
