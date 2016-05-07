#pragma once

#include "GameState.h"
#include <TextComponent.h>

using namespace yam2d;

class MainMenuState : public GameState
{
public:
	MainMenuState(GameApp* app);
	virtual ~MainMenuState();
	virtual bool update(ESContext* ctx, float deltaTime);
	virtual void draw(ESContext* ctx);

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
private:
	Ref<Map> m_map;
	Ref<Sprite> startSprite;
	Ref<Sprite> exitSprite;
	Ref<Sprite> backgroundSprite;
	Ref<Texture> backgroundTexture;
	Ref<Texture> startTexture;
	Ref<Texture> exitTexture;

	Ref<GameObject> pickedObject;
	void toRunningState();
	void toRunningState2();

	int currentSelection;

	GameObject* createTextGameObject(const std::string& t)
	{
		// Load font texture. Made with font creation tool like bitmap font builder.
		Texture* fontTexture = new Texture("assets/Fixedsys_24_Bold.png");

		// Create font clip areas (sprite sheet), from dat file and texture. Dat-file is made with bitmap font builder.
		SpriteSheet* font = SpriteSheet::autoFindFontFromTexture(fontTexture, "assets/Fixedsys_24_Bold.dat");

		GameObject* gameObject = new GameObject(0, 0);
		TextComponent* textComponent = new TextComponent(gameObject, font);
		gameObject->addComponent(textComponent);
		textComponent->getText()->setText(t);
		textComponent->getText()->setColor(0.0f, 1.0f, 0.5f);

		return gameObject;
	}
};