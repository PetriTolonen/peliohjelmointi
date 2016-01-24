#pragma once

#include "GameState.h"
#include "Map.h"

class GameRunningState : public GameState
{
	GameRunningState(){}
	virtual ~GameRunningState(){}
	virtual bool update(ESContext*, float deltaTime){}
	virtual void draw(ESContext*){}
private:
	Ref<Map> m_map;
};