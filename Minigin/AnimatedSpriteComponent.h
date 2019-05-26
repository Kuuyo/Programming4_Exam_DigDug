#pragma once
#include "BaseComponent.h"

#include <SDL.h>

namespace dae
{
	struct AnimatedSpriteClip
	{
		AnimatedSpriteClip(unsigned int id, unsigned int nrOfFrames, float secondsPerFrame,
			unsigned int row, unsigned int column)
			: m_Id(id)
			, m_NrOfFrames(nrOfFrames)
			, m_SecondsPerFrame(secondsPerFrame)
			, m_SourceRect(SDL_Rect())
			, m_Grow(SDL_Rect())
			, m_FrameStart(row * column)
			, m_Rows(0)
		{}

		AnimatedSpriteClip(unsigned int id, unsigned int framePos, unsigned int nrOfFrames,
			float secondsPerFrame)
			: m_Id(id)
			, m_NrOfFrames(nrOfFrames)
			, m_SecondsPerFrame(secondsPerFrame)
			, m_SourceRect(SDL_Rect())
			, m_Grow(SDL_Rect())
			, m_FrameStart(framePos)
			, m_Rows(0)
		{}

		AnimatedSpriteClip(unsigned int id,	unsigned int nrOfFrames, float secondsPerFrame,
			unsigned int rows, const SDL_Rect &sourceRect)
			: m_Id(id)
			, m_NrOfFrames(nrOfFrames)
			, m_SecondsPerFrame(secondsPerFrame)
			, m_SourceRect(sourceRect)
			, m_Grow(SDL_Rect())
			, m_FrameStart(0)
			, m_Rows(rows)
		{}

		AnimatedSpriteClip(unsigned int id, unsigned int nrOfFrames, float secondsPerFrame,
			unsigned int rows, const SDL_Rect &sourceRect, const SDL_Rect &growRect)
			: m_Id(id)
			, m_NrOfFrames(nrOfFrames)
			, m_SecondsPerFrame(secondsPerFrame)
			, m_SourceRect(sourceRect)
			, m_Grow(growRect)
			, m_FrameStart(0)
			, m_Rows(rows)
		{}

		AnimatedSpriteClip()
			: m_Id(0)
			, m_NrOfFrames(0)
			, m_SecondsPerFrame(0.f)
			, m_SourceRect(SDL_Rect())
			, m_Grow(SDL_Rect())
			, m_FrameStart(0)
			, m_Rows(0)
		{}

		unsigned int m_Id;
		unsigned int m_NrOfFrames;
		unsigned int m_FrameStart;
		unsigned int m_Rows;
		float m_SecondsPerFrame;
		SDL_Rect m_SourceRect;
		SDL_Rect m_Grow;
	};

	class Texture2D;

	class AnimatedSpriteComponent final : public BaseComponent
	{
	public:
		AnimatedSpriteComponent(std::string&& fileName, unsigned int sortingLayer,
			bool isCentered, const SDL_Rect &sourceRect,
			int columns, int rows, bool isAnimating);

		void Play();
		void PlayOnce();
		void Pause();
		void Stop();
		void MoveOneFrame();

		bool IsPlaying() const;

		void AddClip(const AnimatedSpriteClip &clip);
		AnimatedSpriteClip GetClip(unsigned int ID) const;

		void HideTexture();

		AnimatedSpriteClip GetActiveClip() const;
		unsigned int GetActiveClipID() const;
		void SetActiveClip(unsigned int ID);

		SDL_Rect GetCurrentActiveSourceRect() const;

		AnimatedSpriteComponent(const AnimatedSpriteComponent&) = delete;
		AnimatedSpriteComponent(AnimatedSpriteComponent&&) = delete;
		AnimatedSpriteComponent& operator= (const AnimatedSpriteComponent&) = delete;
		AnimatedSpriteComponent& operator= (const AnimatedSpriteComponent&&) = delete;

	protected:
		void Initialize(const SceneContext &sceneContext) override;
		void Update(const SceneContext &sceneContext) override;
		void LateUpdate(const SceneContext &) override {}

		virtual ~AnimatedSpriteComponent();

	private:
		Texture2D* m_pTexture;
		SDL_Rect m_SourceRect;

		unsigned int m_Columns, m_Rows;
		unsigned int m_CurrentFrame, m_NumberOfFrames;
		unsigned int m_SortingLayer;
		unsigned int m_GrowedWidth;
		float m_Timer;

		std::string m_FileName;

		bool m_IsCentered;
		bool m_IsAnimating;
		bool m_IsLooping;
		bool m_IsInitialized;
		bool m_HasLoopedOnce;

		std::vector<AnimatedSpriteClip> m_Clips;
		AnimatedSpriteClip m_ActiveClip;
	};

}
