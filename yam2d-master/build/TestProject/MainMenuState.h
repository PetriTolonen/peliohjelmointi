#pragma once

#include "GameState.h"
#include <Layer.h>
#include <Map.h>
#include <Camera.h>

using namespace yam2d;

class MainMenuState : public GameState
{
public:
	MainMenuState(GameApp* app);
	virtual ~MainMenuState();
	virtual bool update(ESContext* ctx, float deltaTime);
	virtual void draw(ESContext* ctx);
private:
	Ref<Map> m_map;
	Ref<Sprite> startSprite;
	Ref<Sprite> exitSprite;
	Ref<Sprite> backgroundSprite;
	Ref<Texture> backgroundTexture;
	Ref<Texture> startTexture;
	Ref<Texture> exitTexture;

	Ref<SpriteBatchGroup> batch;
	bool mouseWasPressedAndReleased = false;

	Ref<GameObject> pickedObject;
};