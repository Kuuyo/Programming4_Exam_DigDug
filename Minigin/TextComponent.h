#pragma once
#include "BaseComponent.h"
#include <SDL_ttf.h>

namespace dae
{
	class Texture2D;
	class Font;

	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent(const std::string& text = " ", bool isCentered = false, unsigned int fontSize = 36, SDL_Color color = { 255,255,255 }, const std::string& font = "Lingua.otf");

		void SetText(const std::string &text);
		void SetColor(const SDL_Color &color);

		TextComponent(const TextComponent &) = delete;
		TextComponent(TextComponent &&) = delete;
		TextComponent & operator= (const TextComponent &) = delete;
		TextComponent & operator= (const TextComponent &&) = delete;

	protected:
		void Initialize(const SceneContext &sceneContext) override;
		void Update(const SceneContext &sceneContext) override;
		void LateUpdate(const SceneContext &) override {}

		virtual ~TextComponent();

	private:
		Texture2D* m_pTexture;
		SDL_Color m_Color;
		std::string m_Text;
		bool m_NeedsUpdate;
		bool m_IsCentered;
		unsigned int m_FontSize;
		std::string m_Font;
		Font* m_pFont;
	};
}