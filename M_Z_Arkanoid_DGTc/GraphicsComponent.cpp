#include "GraphicsComponent.h"

bool GraphicsComponent::init(TextureManager* texturemanager, BaseEntity* entity, const char* texturepath)
{
	internalTextures_ = texturemanager;
	if (internalTextures_)
		return internalTextures_->initTexture(entity, texturepath);
	return false;
}

void GraphicsComponent::draw(BaseEntity* entity)
{
	if(internalTextures_)
	internalTextures_->drawTexture(entity);
}

void GraphicsComponent::SetTexture(BaseEntity* entity, const char* texturepath)
{
	if (internalTextures_)
	internalTextures_->changeTexture(entity, texturepath);
}

void GraphicsComponent::update(BaseEntity* entity, GameWorld* gameworld, double ts)
{
}

void GraphicsComponent::UpdateTextureSize(BaseEntity* entity)
{
	if (internalTextures_)
	internalTextures_->UpdateTextureSize(entity);
}


	