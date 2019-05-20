#pragma once
#include "BaseComponent.h"

namespace dae
{
	struct AnimatedSpriteClip
	{
		AnimatedSpriteClip(unsigned int id, unsigned int nrOfFrames,
			unsigned int startFrame, float secondsPerFrame)
			: m_Id(id)
			, m_NrOfFrames(nrOfFrames)
			, m_StartFrame(startFrame)
			, m_SecondsPerFrame(secondsPerFrame)
		{}

		AnimatedSpriteClip()
			: m_Id(0)
			, m_NrOfFrames(0)
			, m_StartFrame(0)
			, m_SecondsPerFrame(0.f)
		{}

		unsigned int m_Id;
		unsigned int m_NrOfFrames;
		unsigned int m_StartFrame;
		float m_SecondsPerFrame;
		SDL_Rect m_SourceRect;
	};

	class Texture2D;

	class AnimatedSpriteComponent final : public BaseComponent
	{
	public:
		AnimatedSpriteComponent(std::string&& fileName, bool isCentered, const SDL_Rect &sourceRect,
			int columns, int rows, bool isAnimating);

		void Play();
		void Pause();
		void Stop();

		void AddClip(const AnimatedSpriteClip &clip);
		AnimatedSpriteClip GetClip(unsigned int ID) const;

		AnimatedSpriteClip GetActiveClip() const;
		unsigned int GetActiveClipID() const;
		void SetActiveClip(unsigned int ID);

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

		unsigned int m_Columns, m_Rows;
		unsigned int m_CurrentFrame, m_NumberOfFrames;
		float m_Timer;

		std::string m_FileName;

		bool m_IsCentered;
		bool m_IsAnimating;

		std::vector<AnimatedSpriteClip> m_Clips;
		AnimatedSpriteClip m_ActiveClip;
	};

}
