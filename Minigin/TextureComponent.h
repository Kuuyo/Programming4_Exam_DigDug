#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;

	class TextureComponent final : public BaseComponent
	{
	public:
		TextureComponent(const std::string& fileName);
		virtual ~TextureComponent();

		TextureComponent(const TextureComponent &) = delete;
		TextureComponent(TextureComponent &&) = delete;
		TextureComponent & operator= (const TextureComponent &) = delete;
		TextureComponent & operator= (const TextureComponent &&) = delete;

		void Initialize() override;
		void Update() override;
		void Render() override;

	private:
		Texture2D* m_pTexture;
		std::string m_FileName;
	};
}