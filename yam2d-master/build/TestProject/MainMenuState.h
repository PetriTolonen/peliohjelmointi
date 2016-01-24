#pragma once

#include "GameState.h"
#include "Map.h"
using namespace yam2d;

class MainMenuState : public GameState
{
public:
	MainMenuState(){}
	virtual ~MainMenuState(){}
	virtual bool update(ESContext*, float deltaTime){}
	virtual void draw(ESContext*){}
private:
	Ref<Map> m_map;
};