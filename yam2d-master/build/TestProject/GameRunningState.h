#pragma once

#include "GameState.h"
#include "MyComponentFactory.h"

class GameRunningState : public GameState
{
public:
	GameRunningState(GameApp* app);
	virtual ~GameRunningState();
	virtual bool update(ESContext* ctx, float deltaTime);
	virtual void draw(ESContext* ctx);
private:
	Ref<TmxMap> m_map;
	MyComponentFactory* componentFactory;
	Ref<GameObject> paddle;
	float speed;	
};