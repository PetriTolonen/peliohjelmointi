#pragma once

#include "GameState.h"
#include "Sprite.h"
using namespace yam2d;

class SplashScreenState : public GameState
{
public:
	SplashScreenState(){}
	virtual ~SplashScreenState(){}
	virtual bool update(ESContext*, float deltaTime){}
	virtual void draw(ESContext*){}
private:
	Ref<Sprite> m_sprite;
};