#pragma once

#include "GameState.h"
#include "MyComponentFactory2.h"

class GameRunningState2 : public GameState
{
public:
	GameRunningState2(GameApp* app);
	virtual ~GameRunningState2();
	virtual bool update(ESContext* ctx, float deltaTime);
	virtual void draw(ESContext* ctx);
private:
	Ref<TmxMap> m_map;
	MyComponentFactory2* componentFactory2;
};