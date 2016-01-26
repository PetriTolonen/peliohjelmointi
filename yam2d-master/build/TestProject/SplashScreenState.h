#pragma once

#include "GameState.h"
#include "Sprite.h"
#include "SpriteBatch.h"
#include "SpriteSheet.h"
#include <Text.h>
#include <Texture.h>

using namespace yam2d;

class SplashScreenState : public GameState
{
public:
	SplashScreenState();
	virtual ~SplashScreenState();
	virtual bool update(ESContext* ctx, float deltaTime);
	virtual void draw(ESContext* ctx);
private:
	Ref<SpriteBatchGroup> batch;
	Ref<Sprite> m_sprite;
	Ref<Texture> texture;
	Ref<SpriteSheet> font;
	Ref<Texture> fontTexture;
	Ref<Text> text;

	float count = 0.0f;
};