#pragma once
#include "Types.h"
#include "Framework.h"

struct TextureManager
{
	~TextureManager()
	{
		for (auto it = textures.begin(); it != textures.end(); it++)
			destroySprite(it->second);
	}
	TextureManager() {}

	void BackgroundInit(int w, int h, const char* path) 
	{ 
		textures[NONE_ENTITY] = createSprite(path); 
		setSpriteSize(textures[NONE_ENTITY], w, h);
	}

	void UpdateTextureSize(BaseEntity* entity)
	{
		auto texture = textures[entity->GetType()];
		if (texture)
		{
			setSpriteSize(texture, entity->GetCoord().width_, entity->GetCoord().height_);
		}
	}

	Sprite* GetTexture(EntityType type) { return textures[type]; }
	bool initTexture(BaseEntity* entity, const char* texturepath)
	{
		if (!textures[entity->GetType()])
		{
			textures[entity->GetType()] = createSprite(texturepath);
			setSpriteSize(textures[entity->GetType()], entity->GetCoord().width_, entity->GetCoord().height_);
		}
		if (textures[entity->GetType()] == nullptr)
			return false;
		return true;
	}

	void changeTexture(BaseEntity* entity, const char* texturepath)
	{
		if (textures[entity->GetType()])
			destroySprite(textures[entity->GetType()]);

		textures[entity->GetType()] = createSprite(texturepath);
		setSpriteSize(textures[entity->GetType()], entity->GetCoord().width_, entity->GetCoord().height_);

	}

	void drawTexture(BaseEntity* entity)
	{
		auto sprite = textures[entity->GetType()];
		drawSprite(sprite, entity->GetCoord().x_, entity->GetCoord().y_);
	}
private:
	Map(EntityType, Sprite*) textures;
};