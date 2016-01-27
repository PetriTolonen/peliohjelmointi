#pragma once

#include "GameState.h"
#include "Map.h"

class GameRunningState : public GameState
{
	GameRunningState(GameApp* app) : GameState(app){}
	virtual ~GameRunningState(){}
	virtual bool update(ESContext* ctx, float deltaTime);
	virtual void draw(ESContext* ctx);
private:
	Ref<Map> m_map;
};