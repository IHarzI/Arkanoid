#pragma once
#include "Framework.h"
#include "BaseEntity.h"
#include "Component.h"
#include "TextureManager.h"


class GraphicsComponent : public Component
{
public:

	bool init(TextureManager* texturemanager, BaseEntity* entity, const char* texturepath);
	GraphicsComponent(){};

	virtual ~GraphicsComponent()
	{
	};

	void draw(BaseEntity* entity);

	void SetTexture(BaseEntity* entity, const char* texturepath);

	virtual void update(BaseEntity* entity, GameWorld* gameworld, double ts) override;

	void DeleteSprite(BaseEntity* entity) { destroySprite(internalTextures_->GetTexture(entity->GetType())); }

	void UpdateTextureSize(BaseEntity* entity);
private:
	TextureManager* internalTextures_;
};
