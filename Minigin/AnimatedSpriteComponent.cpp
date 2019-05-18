#include "MiniginPCH.h"
#include "AnimatedSpriteComponent.h"

#include "GameObject.h"
#include "ResourceManager.h"
#include "Time.h"
#include "Texture2D.h"

namespace dae
{
	AnimatedSpriteComponent::AnimatedSpriteComponent(std::string && fileName, bool isCentered,
		const SDL_Rect &sourceRect, int columns, int rows, float secondsPerFrame, bool isAnimating,
		const glm::vec2 &margin, const glm::vec2 &padding)
		: m_FileName(std::move(fileName))
		, m_pTexture(nullptr)
		, m_SourceRect(sourceRect)
		, m_IsCentered(isCentered)
		, m_Columns(columns)
		, m_Rows(rows)
		, m_CurrentFrame(0)
		, m_NumberOfFrames(m_Columns * m_Rows)
		, m_SecondsPerFrame(secondsPerFrame)
		, m_IsAnimating(isAnimating)
		, m_Margin(margin)
		, m_Padding(padding)
		, m_Timer(0.f)
	{
	}

	AnimatedSpriteComponent::~AnimatedSpriteComponent()
	{
		m_pParent->GetScene()->RemoveTexture(m_pTexture);
		delete m_pTexture;
	}

	void AnimatedSpriteComponent::Initialize(const GameContext &gameContext)
	{
		m_pTexture = gameContext.Resources->CreateTexture(m_FileName,
			m_pParent->GetComponent<TransformComponent>(), m_SourceRect, m_IsCentered);
		m_pParent->GetScene()->AddTexture(m_pTexture);
	}

	void AnimatedSpriteComponent::Update(const GameContext &gameContext)
	{
		if (m_IsAnimating)
		{
			m_Timer += gameContext.Time->GetDeltaTime();

			if (m_Timer >= m_SecondsPerFrame)
			{
				SDL_Rect src = m_SourceRect;
				src.x = src.w * (m_CurrentFrame % (m_Columns + 1));
				src.y = src.h * (m_CurrentFrame / m_Rows);

				m_pTexture->SetSourceRect(src);

				m_CurrentFrame = (m_CurrentFrame + 1) % m_NumberOfFrames;
				m_Timer -= m_SecondsPerFrame;
			}
		}
	}

	void AnimatedSpriteComponent::Play()
	{
		m_IsAnimating = true;
	}

	void AnimatedSpriteComponent::Pause()
	{
		m_IsAnimating = false;
	}

	void AnimatedSpriteComponent::Stop()
	{
		m_IsAnimating = false;
		m_CurrentFrame = 0;
		m_pTexture->SetSourceRect(m_SourceRect);
	}
}