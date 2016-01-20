#pragma once
// Include OpenGL ES Engine utils
#include <es_util.h>

#include "Object.h"
#include "GameState.h"
#include "Ref.h"

using namespace yam2d;

class GameApp : public Object
{
public:
	GameApp(){}
	virtual ~GameApp(){}
	bool update(ESContext* ctx, float deltaTime){}
	void draw(ESContext *esContext){}
	void setState(GameState* setState){ m_currentState = setState; }
private:
	Ref<GameState> m_currentState;
};