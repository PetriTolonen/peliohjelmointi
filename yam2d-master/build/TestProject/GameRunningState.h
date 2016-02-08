#pragma once

#include "GameState.h"

class GameRunningState : public GameState
{
public:
	GameRunningState(GameApp* app);
	virtual ~GameRunningState();
	virtual bool update(ESContext* ctx, float deltaTime);
	virtual void draw(ESContext* ctx);
private:
	Ref<TmxMap> m_map;
	ComponentFactory* componentFactory;
	Ref<GameObject> paddle;
};