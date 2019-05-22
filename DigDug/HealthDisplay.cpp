#include "pch.h"
#include "HealthDisplay.h"

#include <GameObject.h>
#include <ObserverComponent.h>
#include <TextureComponent.h>
#include <HealthComponent.h>

void HealthDisplay::CreateHealthDisplay(dae::GameObject* &out, const std::string &playerName, bool isPlayerOne)
{
	if (out == nullptr)
		out = new dae::GameObject("HealthDisplay: " + playerName);

	auto pObserver = new dae::ObserverComponent();

	std::function<void(const dae::Subject* entity, int nrArgs, va_list args)> func =
		[out, playerName, isPlayerOne](const dae::Subject* entity, int, va_list args)
		{
			if (entity->GetTag() == playerName)
			{
				dae::HealthStatus info = va_arg(args, dae::HealthStatus);

				switch (info)
				{
				case dae::HealthStatus::LostLife:
				{
					auto pTexture = out->GetComponent<dae::TextureComponent>();
					auto srcRect = pTexture->GetSourceRect();
					if (srcRect.w > 0)
					{
						srcRect.w -= 16;
						pTexture->SetSourceRect(srcRect);
					}
				}
					break;
				default:
					break;
				}
			}
		};

	pObserver->AddFunction(func);

	out->AddComponent(pObserver);

	out->AddComponent(new dae::TextureComponent("DigDugLife.gif", false));
}
