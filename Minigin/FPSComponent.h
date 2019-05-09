#pragma once
#include "BaseComponent.h"

#include <SDL_ttf.h>

namespace dae
{
	class TextComponent;
	class Texture2D;
	class Font;

	class FPSComponent final : public BaseComponent
	{
	public:
		FPSComponent(bool isCentered = false, unsigned int fontSize = 20, SDL_Color color = { 255,255,100 });
		virtual ~FPSComponent();

		FPSComponent(const FPSComponent &) = delete;
		FPSComponent(FPSComponent &&) = delete;
		FPSComponent & operator= (const FPSComponent &) = delete;
		FPSComponent & operator= (const FPSComponent &&) = delete;

		void Initialize(const GameContext &gameContext) override;
		void Update(const GameContext &gameContext) override;

	private:
		Texture2D* m_pTexture;
		Font* m_pFont;
		std::string m_Text;
		unsigned int m_FontSize;
		SDL_Color m_Color;
		bool m_IsCentered;
	};
}