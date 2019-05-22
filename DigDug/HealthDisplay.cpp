#include "pch.h"
#include "HealthDisplay.h"

#include <GameObject.h>
#include <ObserverComponent.h>
#include <TextureComponent.h>

#include "CharacterStates.h"

void HealthDisplay::CreateHealthDisplay(dae::GameObject* &out, const std::string &playerName)
{
	if (out == nullptr)
		out = new dae::GameObject("HealthDisplay: " + playerName);

	auto pObserver = new dae::ObserverComponent();

	std::function<void(const dae::Subject* entity, int nrArgs, va_list args)> func =
		[out, playerName](const dae::Subject* entity, int, va_list args)
		{
			if (entity->GetTag() == playerName)
			{
				Characters::DigDugEx::Information info = va_arg(args, Characters::DigDugEx::Information);

				switch (info)
				{
				case Characters::DigDugEx::Information::LostLife:
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
