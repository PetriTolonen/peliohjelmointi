#pragma once

#include "GameState.h"
#include "Map.h"
using namespace yam2d;

class MainMenuState : public GameState
{
public:
	MainMenuState();
	virtual ~MainMenuState();
	virtual bool update(ESContext* ctx, float deltaTime);
	virtual void draw(ESContext* ctx);
private:
	Ref<Map> m_map;
	Ref<Sprite> start;
	Ref<Texture> startTexture;

	Ref<SpriteBatchGroup> batch;
	
};