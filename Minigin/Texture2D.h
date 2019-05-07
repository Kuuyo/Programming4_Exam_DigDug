#pragma once
#include "ResourceManager.h"
struct SDL_Texture;

namespace dae
{
	class Texture2D final
	{
	public:
		explicit Texture2D(SDL_Texture* texture, glm::vec2 pos);
		~Texture2D();

		SDL_Texture* GetSDLTexture() const;
		glm::vec2 GetPosition() const;
		void SetPosition(float x, float y);

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;
	private:
		SDL_Texture* m_pTexture;
		glm::vec2 m_Position;

		friend void ResourceManager::CreateTextTexture(const SDL_Color &color, const Font* pFont, const std::string &text, Texture2D* &pTexture, const glm::vec2 &pos);
	};
}
