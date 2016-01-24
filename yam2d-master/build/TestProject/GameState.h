#pragma once
#include "Object.h"
#include "GameApp.h"

using namespace yam2d;

class GameState : public Object
{
public:
	GameState(){}
	virtual ~GameState(){}
	virtual bool update(ESContext* ctx, float deltaTime){}
	virtual void draw(ESContext *esContext){}
	void getApp(){}
private:
	GameApp* m_gameApp;
};