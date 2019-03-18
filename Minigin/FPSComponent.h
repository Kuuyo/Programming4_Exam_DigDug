#pragma once
#include "BaseComponent.h"

#include <SDL_ttf.h>

namespace dae
{
	class TextComponent;

	class FPSComponent : public BaseComponent
	{
	public:
		FPSComponent(unsigned int fontSize = 20, SDL_Color color = { 255,255,100 });
		virtual ~FPSComponent();

		FPSComponent(const FPSComponent &) = delete;
		FPSComponent(FPSComponent &&) = delete;
		FPSComponent & operator= (const FPSComponent &) = delete;
		FPSComponent & operator= (const FPSComponent &&) = delete;

		void Initialize() override;
		void Update() override;
		void Render() override;

	private:
		TextComponent* m_FpsDisplay;
		unsigned int m_FontSize;
		SDL_Color m_Color;
	};
}