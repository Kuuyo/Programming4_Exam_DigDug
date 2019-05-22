#pragma once
#include "BaseComponent.h"

#include <SDL.h>

namespace dae
{
	struct AnimatedSpriteClip
	{
		AnimatedSpriteClip(unsigned int id, unsigned int startFrame,
			unsigned int nrOfFrames, float secondsPerFrame)
			: m_Id(id)
			, m_StartFrame(startFrame)
			, m_NrOfFrames(nrOfFrames)
			, m_SecondsPerFrame(secondsPerFrame)
		{}

		AnimatedSpriteClip()
			: m_Id(0)
			, m_NrOfFrames(0)
			, m_StartFrame(0)
			, m_SecondsPerFrame(0.f)
		{}

		unsigned int m_Id;
		unsigned int m_StartFrame;
		unsigned int m_NrOfFrames;
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
		void PlayOnce();
		void Pause();
		void Stop();

		bool IsPlaying() const;

		void AddClip(const AnimatedSpriteClip &clip);
		AnimatedSpriteClip GetClip(unsigned int ID) const;

		void HideTexture();

		AnimatedSpriteClip GetActiveClip() const;
		unsigned int GetActiveClipID() const;
		void SetActiveClip(unsigned int ID);

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
		float m_Timer;

		std::string m_FileName;

		bool m_IsCentered;
		bool m_IsAnimating;
		bool m_IsLooping;
		bool m_IsInitialized;

		std::vector<AnimatedSpriteClip> m_Clips;
		AnimatedSpriteClip m_ActiveClip;
	};

}
