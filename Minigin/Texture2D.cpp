#include "MiniginPCH.h"
#include "Texture2D.h"

dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(mTexture);
}

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return mTexture;
}

dae::Texture2D::Texture2D(SDL_Texture* texture)
{
	mTexture = texture;
}
