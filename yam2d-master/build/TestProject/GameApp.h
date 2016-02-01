#pragma once

#include "GameState.h"
using namespace yam2d;

class GameApp : public Object
{
public:
	GameApp(){}
	virtual ~GameApp(){}
	bool update(ESContext* ctx, float deltaTime);
	void draw(ESContext * ctx);
	void setState(GameState* newState){ m_currentState = newState; }
private:
	Ref<GameState> m_currentState;
};