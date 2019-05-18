#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;

	class AnimatedSpriteComponent final : public BaseComponent
	{
	public:
		AnimatedSpriteComponent(std::string&& fileName, bool isCentered, const SDL_Rect &sourceRect,
			int columns, int rows, float secondsPerFrame, bool isAnimating,
			const glm::vec2 &margin = glm::vec2(), const glm::vec2 &padding = glm::vec2());

		void Play();
		void Pause();
		void Stop();

		AnimatedSpriteComponent(const AnimatedSpriteComponent&) = delete;
		AnimatedSpriteComponent(AnimatedSpriteComponent&&) = delete;
		AnimatedSpriteComponent& operator= (const AnimatedSpriteComponent&) = delete;
		AnimatedSpriteComponent& operator= (const AnimatedSpriteComponent&&) = delete;

	protected:
		void Initialize(const GameContext &gameContext) override;
		void Update(const GameContext &) override;
		void LateUpdate(const GameContext &) override {}

		virtual ~AnimatedSpriteComponent();

	private:
		Texture2D* m_pTexture;
		SDL_Rect m_SourceRect;
		glm::vec2 m_Margin;
		glm::vec2 m_Padding;
		int m_Columns, m_Rows;
		unsigned int m_CurrentFrame, m_NumberOfFrames;
		float m_SecondsPerFrame;
		float m_Timer;
		std::string m_FileName;
		bool m_IsCentered;
		bool m_IsAnimating;
	};

}
