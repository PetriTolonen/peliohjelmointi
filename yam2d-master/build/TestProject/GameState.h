#pragma once
#include "Object.h"
#include "GameApp.h"

using namespace yam2d;

class GameState : public Object
{
public:
	GameState(){}
	virtual ~GameState(){}
private:
	GameApp* m_gameApp;
};