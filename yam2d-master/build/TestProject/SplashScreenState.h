#pragma once

#include "GameState.h"
#include "Sprite.h"
using namespace yam2d;

class SplashScreenState : public GameState
{
public:
	SplashScreenState(){}
	virtual ~SplashScreenState(){}
	virtual bool update(ESContext* ctx, float deltaTime);
	virtual void draw(ESContext* ctx);
private:
	Ref<Sprite> m_sprite;
};