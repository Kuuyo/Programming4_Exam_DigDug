#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;

	class AnimatedSpriteComponent final : public BaseComponent
	{
	public:
		AnimatedSpriteComponent(std::string&& fileName, bool isCentered = true, const SDL_Rect &sourceRect = SDL_Rect());

		AnimatedSpriteComponent(const AnimatedSpriteComponent&) = delete;
		AnimatedSpriteComponent(AnimatedSpriteComponent&&) = delete;
		AnimatedSpriteComponent &operator= (const AnimatedSpriteComponent&) = delete;
		AnimatedSpriteComponent &operator= (const AnimatedSpriteComponent&&) = delete;

	protected:
		void Initialize(const GameContext &) override {}
		void Update(const GameContext &) override {}
		void LateUpdate(const GameContext &) override {}

		virtual ~AnimatedSpriteComponent() = default;

	private:
		Texture2D* m_pTexture;
		std::string m_FileName;
		SDL_Rect m_SourceRect;
		bool m_IsCentered;
	};

}
