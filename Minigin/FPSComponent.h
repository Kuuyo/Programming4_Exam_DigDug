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

		FPSComponent(const FPSComponent &) = delete;
		FPSComponent(FPSComponent &&) = delete;
		FPSComponent & operator= (const FPSComponent &) = delete;
		FPSComponent & operator= (const FPSComponent &&) = delete;

	protected:
		void Initialize(const GameContext &gameContext) override;
		void Update(const GameContext &gameContext) override;
		void LateUpdate(const GameContext &) override {}

		virtual ~FPSComponent();

	private:
		Texture2D* m_pTexture;
		Font* m_pFont;
		std::string m_Text;
		unsigned int m_FontSize;
		SDL_Color m_Color;
		bool m_IsCentered;
	};
}