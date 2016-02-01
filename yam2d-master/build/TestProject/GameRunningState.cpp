#include "GameRunningState.h"
#include "GameApp.h"
#include "MainMenuState.h"

GameRunningState::GameRunningState(GameApp* app) : GameState(app)
{
	esLogMessage(__FUNCTION__);
	int cc = 0;

	//Map Tilesize
	vec2 tileSize(128, 128);

	m_map = new Map(tileSize.x, tileSize.y);

	Layer* backgroundLayer = new Layer(m_map, "Background", 1.0f, true, false);
	m_map->addLayer(Map::BACKGROUND0, backgroundLayer);

	// Create new sprite GameObject from texture (background sprite) size is same than screen size.
	GameObject* backgroundGameObject = createSpriteGameObject("gamebackround_1080p.png", 1280.0f, 720.0f);

	backgroundLayer->addGameObject(backgroundGameObject);
}

bool GameRunningState::update(ESContext* ctx, float deltaTime)
{
	m_map->update(deltaTime);

	if (isKeyPressed(KEY_ESCAPE))
	{
		getApp()->setState(new MainMenuState(getApp()));
		return true;
	}
	return true;
}

void GameRunningState::draw(ESContext* ctx)
{
	// Set screen size to camera.
	m_map->getCamera()->setScreenSize(ctx->width, ctx->height, 720, 1280.0f / 720.0f);

	// Render map and all of its layers containing GameObjects to screen.
	m_map->render();
}