#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;
	class Font;

	class TextComponent : public BaseComponent
	{
	public:
		TextComponent(const std::string& text = " ", int fontSize = 36, const std::string& font = "Lingua.otf");
		virtual ~TextComponent();

		void SetText(const std::string& text);

		TextComponent(const TextComponent &) = delete;
		TextComponent(TextComponent &&) = delete;
		TextComponent & operator= (const TextComponent &) = delete;
		TextComponent & operator= (const TextComponent &&) = delete;

		void Initialize() override;
		void Update() override;
		void Render() override;

	private:
		void CreateTextTexture();

		Texture2D* m_pTexture;
		std::string m_Text;
		bool m_bNeedsUpdate;
		int m_FontSize;
		std::string m_Font;
		Font* m_pFont;
	};
}