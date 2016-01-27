#pragma once

#include "GameState.h"

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
	Ref<Texture> splashTexture;
	Ref<SpriteSheet> font;
	Ref<Texture> fontTexture;
	Ref<Text> text;

	float count = 0.0f;
	float m_timer;

	bool doonce = true;
};