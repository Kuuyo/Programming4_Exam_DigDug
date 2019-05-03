#include "pch.h"
#include "Characters.h"

#include "GameObject.h"
#include "TextureComponent.h"

void Prefabs::CreateDigDugCharacter(std::shared_ptr<dae::GameObject> out)
{
	if (out == nullptr)
		out = std::make_shared<dae::GameObject>();

	dae::TextureComponent* pTexture = new dae::TextureComponent("DigDug.gif");
	out->AddComponent(pTexture);
}
