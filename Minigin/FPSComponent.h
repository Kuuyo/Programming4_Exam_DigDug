#pragma once
#include "BaseComponent.h"

namespace dae
{
	class TextComponent;

	class FPSComponent : public BaseComponent
	{
	public:
		FPSComponent();
		virtual ~FPSComponent();

		FPSComponent(const FPSComponent &) = delete;
		FPSComponent(FPSComponent &&) = delete;
		FPSComponent & operator= (const FPSComponent &) = delete;
		FPSComponent & operator= (const FPSComponent &&) = delete;

		void Initialize() override;
		void Update() override;
		void Render() override;

	private:
		TextComponent* m_FpsDisplay;
	};
}