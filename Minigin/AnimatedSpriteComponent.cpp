#include "MiniginPCH.h"
#include "AnimatedSpriteComponent.h"

#include "GameObject.h"
#include "ResourceManager.h"
#include "Time.h"
#include "Texture2D.h"
#include "Scene.h"

namespace dae
{
	AnimatedSpriteComponent::AnimatedSpriteComponent(std::string &&fileName, bool isCentered,
		const SDL_Rect &sourceRect, int columns, int rows, bool isAnimating)
		: m_FileName(std::move(fileName))
		, m_pTexture(nullptr)
		, m_SourceRect(sourceRect)
		, m_IsCentered(isCentered)
		, m_Columns(columns)
		, m_Rows(rows)
		, m_CurrentFrame(0)
		, m_NumberOfFrames(m_Columns * m_Rows)
		, m_IsAnimating(isAnimating)
		, m_Timer(0.f)
		, m_IsInitialized(false)
	{
	}

	AnimatedSpriteComponent::~AnimatedSpriteComponent()
	{
		m_pParent->GetScene()->RemoveTexture(m_pTexture);
		delete m_pTexture;
	}

	void AnimatedSpriteComponent::Initialize(const SceneContext &sceneContext)
	{
		m_pTexture = sceneContext.GameContext->Resources->CreateTexture(m_FileName,
			m_pParent, m_SourceRect, m_IsCentered);

		m_pParent->GetScene()->AddTexture(m_pTexture);

		m_pTexture->SetSourceRect(m_ActiveClip.m_SourceRect);

		m_IsInitialized = true;		
	}

	void AnimatedSpriteComponent::Update(const SceneContext &sceneContext)
	{
		if (m_IsAnimating)
		{
			m_Timer += sceneContext.GameContext->Time->GetDeltaTime();

			if (m_Timer >= m_ActiveClip.m_SecondsPerFrame)
			{
				SDL_Rect src = m_ActiveClip.m_SourceRect;
				src.x = src.w * (m_CurrentFrame % m_Rows);
				src.y = src.h * (m_CurrentFrame / m_Rows);

				m_pTexture->SetSourceRect(src);

				m_CurrentFrame = (m_CurrentFrame + 1) %
					(m_ActiveClip.m_StartFrame + m_ActiveClip.m_NrOfFrames);
				m_CurrentFrame = glm::max(m_CurrentFrame, m_ActiveClip.m_StartFrame);
				m_Timer -= m_ActiveClip.m_SecondsPerFrame;

				if (m_CurrentFrame == m_ActiveClip.m_StartFrame && !m_IsLooping)
					Pause();
			}
		}
	}

	void AnimatedSpriteComponent::Play()
	{
		m_IsAnimating = true;
		m_IsLooping = true;
	}

	void AnimatedSpriteComponent::PlayOnce()
	{
		m_IsAnimating = true;
		m_IsLooping = false;
	}

	void AnimatedSpriteComponent::Pause()
	{
		m_IsAnimating = false;
	}

	void AnimatedSpriteComponent::Stop()
	{
		m_IsAnimating = false;
		m_CurrentFrame = m_ActiveClip.m_StartFrame;
		m_pTexture->SetSourceRect(m_ActiveClip.m_SourceRect);
	}

	bool AnimatedSpriteComponent::IsPlaying() const
	{
		return m_IsAnimating;
	}

	void AnimatedSpriteComponent::AddClip(const AnimatedSpriteClip &clip)
	{
		m_Clips.push_back(clip);

		SDL_Rect src = m_SourceRect;
		src.x = src.w * (clip.m_StartFrame % m_Rows);
		src.y = src.h * (clip.m_StartFrame / m_Rows);
		m_Clips.back().m_SourceRect = src;
	}

	AnimatedSpriteClip AnimatedSpriteComponent::GetClip(unsigned int ID) const
	{
		return *std::find_if(m_Clips.begin(), m_Clips.end(),
			[ID](AnimatedSpriteClip ac) {return ac.m_Id == ID; });
	}

	void AnimatedSpriteComponent::HideTexture()
	{
		m_pTexture->SetSourceRect(SDL_Rect());
	}

	AnimatedSpriteClip AnimatedSpriteComponent::GetActiveClip() const
	{
		return m_ActiveClip;
	}

	unsigned int AnimatedSpriteComponent::GetActiveClipID() const
	{
		return m_ActiveClip.m_Id;
	}

	void AnimatedSpriteComponent::SetActiveClip(unsigned int ID)
	{
		m_ActiveClip = *std::find_if(m_Clips.begin(), m_Clips.end(),
			[ID](AnimatedSpriteClip ac) {return ac.m_Id == ID; });

		m_CurrentFrame = m_ActiveClip.m_StartFrame;

		if(m_IsInitialized)
			m_pTexture->SetSourceRect(m_ActiveClip.m_SourceRect);
	}
}