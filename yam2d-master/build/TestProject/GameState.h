#pragma once
#include "Object.h"
#include "GameApp.h"

using namespace yam2d;

class GameState : public Object
{
public:
	GameState(GameApp* app) : m_gameApp(app){}
	virtual ~GameState(){}
	GameApp* getApp(){ return m_gameApp; }
private:
	GameApp* m_gameApp;
};