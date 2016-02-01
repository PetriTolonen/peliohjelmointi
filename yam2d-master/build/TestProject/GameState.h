#pragma once

#include <Object.h>

#include <Ref.h>

#include <Input.h>
#include <Layer.h>
#include <Map.h>
#include <Camera.h>

#include <es_util.h>
#include <Sprite.h>
#include <SpriteBatch.h>
#include <SpriteSheet.h>
#include <SpriteComponent.h>
#include <Text.h>
#include <Texture.h>

class GameApp;

using namespace yam2d;

class GameState : public Object
{
public:
	virtual bool update(ESContext* ctx, float deltaTime){ return true; }
	virtual void draw(ESContext *ctx){}
	virtual ~GameState(){}

	GameObject* createSpriteGameObject(const std::string& bitmapFileName, float sizeX, float sizeY, bool isWhiteTransparentColor = false)
	{
		// Load texture to be used as texture for sprite.
		Texture* texture = new Texture(bitmapFileName.c_str());

		// If user wants to create texture which white coros is treated as atransparent color.
		if (isWhiteTransparentColor)
		{
			// Set white to transparent. Here color values are from 0 to 255 (RGB)
			texture->setTransparentColor(255, 255, 255);
		}

		// Create new sprite GameObject from texture.
		GameObject* gameObject = new GameObject(0, 0);
		SpriteComponent* sprite = new SpriteComponent(gameObject, texture);

		// Resize the sprite to be correct size
		gameObject->setSize(sizeX, sizeY);

		// Add sprite component to game object
		gameObject->addComponent(sprite);
		return gameObject;
	}

	GameObject* createSpriteGameObject(const std::string& bitmapFileName, float sizeX, float sizeY, int clipStartX, int clipStartY, int clipSizeX, int clipSizeY, bool isWhiteTransparentColor = false)
	{
		// Load texture to be used as texture for sprite.
		Texture* texture = new Texture(bitmapFileName.c_str());

		// If user wants to create texture which white coros is treated as atransparent color.
		if (isWhiteTransparentColor)
		{
			// Set white to transparent. Here color values are from 0 to 255 (RGB)
			texture->setTransparentColor(255, 255, 255);
		}

		// Create new sprite GameObject from texture.
		GameObject* gameObject = new GameObject(0, 0);
		SpriteComponent* sprite = new SpriteComponent(gameObject, texture);

		// Resize the sprite to be correct size
		gameObject->setSize(sizeX, sizeY);

		// Specify clip area by start point and size in pixels
		Sprite::PixelClip clip;
		clip.topLeft.x = clipStartX;
		clip.topLeft.y = clipStartY;
		clip.clipSize.x = clipSizeX;
		clip.clipSize.y = clipSizeY;

		// Set pixel clip for sprite
		sprite->getSprite()->setClip(float(texture->getWidth()), float(texture->getHeight()), clip);

		// Add sprite component to game object
		gameObject->addComponent(sprite);
		return gameObject;
	}
	
protected:
	GameState(GameApp* app): m_gameApp(app){}	
	GameApp* getApp(){ return m_gameApp; }
private:
	GameApp* m_gameApp;
};